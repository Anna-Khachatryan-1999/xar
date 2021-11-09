#include <iostream>

template <typename T>
struct node
{
    T elem;
    node<T>* next = nullptr;
    node<T>* prev = nullptr;
    node<T>* asc = nullptr;
    node<T>* desc = nullptr;
};


template <typename T>
class FrankensteinsList
{
public:
    FrankensteinsList();
    ~FrankensteinsList();

public:
    bool isEmpty() const;
    std::size_t size() const;
    void push_front(T elem);
    void push_back(T elem);
    void insert(int pos, T elem);
    void pop_back();
    void pop_front();
    void remove(int pos);
    T maxElem() const;
    T minElem() const;
    void print() const;
    void print_sort_show() const;

private:
    void put_sorted(node<T>* n);
    void pop_sorted(node<T>* n);

private:
    std::size_t m_size;
    node<T>* m_head = nullptr;
    node<T>* m_tail = nullptr;
    node<T>* m_asc = nullptr;
    node<T>* m_dsec = nullptr;
};

template <typename T>
FrankensteinsList<T>::FrankensteinsList() : m_size{0} {}

template <typename T>
FrankensteinsList<T>::~FrankensteinsList()
{
    while (m_head->next) {
        pop_front();
    }
}


template <typename T>
std::size_t FrankensteinsList<T>::size() const
{
    return m_size;
}

template <typename T>
T FrankensteinsList<T>::maxElem() const
{
    return m_dsec->elem;
}

template <typename T>
T FrankensteinsList<T>::minElem() const
{
    return m_asc->elem;
}

template <typename T>
bool FrankensteinsList<T>::isEmpty() const
{
    if (!m_head) return true;
    return false;
}


template <typename T>
void FrankensteinsList<T>::put_sorted(node<T>* n)
{
    if (m_asc->elem >= n->elem) {
        m_asc->desc = n;
        n->asc = m_asc;
        m_asc = n;
        return;
    }
    node<T>* tmp = m_asc;
    while (tmp->asc != nullptr) {
        if (tmp->asc->elem >= n->elem) {
            tmp->asc->desc = n;
            n->asc = tmp->asc;
            n->desc = tmp;
            tmp->asc = n;
            return;
        }
        tmp = tmp->asc;
    }
    n->desc = tmp;
    tmp->asc = n;
    m_dsec = n;
}

template <typename T>
void FrankensteinsList<T>::pop_sorted(node<T>* n)
{
        if (m_size == 2) {
            m_asc->asc = nullptr;
            m_dsec->desc = nullptr;
            m_asc = m_dsec;
            return;
        }
    if (n == m_dsec) {
            node<T>* tmp = m_dsec->desc;
            tmp->asc = nullptr;
            m_dsec->desc = nullptr;
            m_dsec = tmp;
    } else if (n == m_asc) {
            node<T>* tmp = m_dsec->asc;
            tmp->desc = nullptr;
            m_asc->asc = nullptr;;
            m_asc = tmp;
    } else {
        node<T>* tmp = m_dsec->asc;
        n->desc->asc = n->asc;
        n->asc->desc = n->desc;
        n->asc = nullptr;
        n->desc = nullptr;
    }

}

template <typename T>
void FrankensteinsList<T>::push_front(T elem)
{
    node<T>* n = new node<T>{};
    n->elem = elem;
    if (m_head == nullptr) {
        m_head = n;
        m_tail = n;
        m_asc = n;
        m_dsec = n;
        ++m_size;
        return;
    }
    m_head->prev = n;
    n->next = m_head;
    m_head = n;
    ++m_size;
    put_sorted(n);
}


template <typename T>
void FrankensteinsList<T>::push_back(T elem)
{
    node<T>* n = new node<T>{};
    n->elem = elem;
    if (m_head == nullptr) {
        m_head = n;
        m_tail = n;
        m_asc = n;
        m_dsec = n;
        ++m_size;
        return;
    }
    m_tail->next = n;
    n->prev = m_tail;
    m_tail = n;
    ++m_size;
    put_sorted(n);
}


template <typename T>
void FrankensteinsList<T>::insert(int pos, T elem)
{
    if (pos < 0 || pos > m_size) {
        throw std::invalid_argument("Invalid index");
    }
    if (pos == 0) {
        push_front(elem);
    } else if (pos == m_size) {
        push_back(elem);
    } else {
        node<T>* tmp = m_head;
        while (pos != 1) {
            tmp = tmp->next;
            --pos;
        }
        node<T>* n = new node<T>{};
        n->elem = elem;
        tmp->next->prev = n;
        n->next = tmp->next;
        n->prev = tmp;
        tmp->next = n;
        put_sorted(n);
        ++m_size;
    }
}

template <typename T>
void FrankensteinsList<T>::pop_back()
{
    if (m_head == nullptr) {
        throw std::invalid_argument("list is empty");
    }
    if (m_size == 1) {
        m_head = nullptr;
        m_tail = nullptr;
        m_asc = nullptr;
        m_dsec = nullptr;
        --m_size;
    } else {
        pop_sorted(m_tail);
        node<T>* tmp = m_tail->prev;
        tmp->next = nullptr;
        m_tail->prev = nullptr;
        delete[] m_tail;
        m_tail = tmp;
        --m_size;
    }
}

template <typename T>
void FrankensteinsList<T>::pop_front()
{
    if (m_head == nullptr) {
        throw std::invalid_argument("list is empty");
    }
    if (m_size == 1) {
        m_head = nullptr;
        m_tail = nullptr;
        m_asc = nullptr;
        m_dsec = nullptr;
        --m_size;
    } else {
        pop_sorted(m_head);
        node<T>* tmp = m_head->next;
        tmp->prev = nullptr;
        m_head->next = nullptr;
        delete[] m_head;
        m_head = tmp;
        --m_size;
    }
}

template <typename T>
void FrankensteinsList<T>::remove(int pos)
{
    if (pos < 0 || pos > m_size) {
        throw std::invalid_argument("Invalid index");
    }
    if (pos == 0) {
        pop_front();
    } else if (pos == m_size) {
        pop_back();
    } else {
        node<T>* tmp = m_head;
        while (pos) {
            tmp = tmp->next;
            --pos;
        }
        pop_sorted(tmp);
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        tmp->prev = nullptr;
        tmp->next = nullptr;
        delete[] tmp;
        tmp = nullptr;
        --m_size;
    }
}


template <typename T>
void FrankensteinsList<T>::print_sort_show() const
{
    node<T>* tmp = m_head;
    while (tmp) {
        if (tmp->desc) {
            std::cout << tmp->desc->elem << "  <-  ";
        } else {
            std::cout << "      ";
        }
       std::cout << tmp->elem;
        if (tmp->asc) {
            std::cout << "  ->  " << tmp->asc->elem ;
        }        tmp = tmp->next;
    std::cout << std::endl;
    }
    std::cout << std::endl;
}

template <typename T>
void FrankensteinsList<T>::print() const
{
    node<T>* tmp = m_head;
    while (tmp) {
       std::cout << tmp->elem << " ";
       tmp = tmp->next;
    }
    std::cout << std::endl;
}
int main()
{
    FrankensteinsList<int> f;
    f.push_front(0);
    f.push_front(5);
    f.push_front(1);
    f.push_front(7);
    std::cout << std::endl;
    f.print();
    std::cout << "max - " << f.maxElem() << std::endl;
    std::cout << "min - " << f.minElem() << std::endl;
    std::cout << "size - " << f.size() << std::endl;
    std::cout << std::endl;
    f.push_back(9);
    f.push_back(17);
    f.print();
    std::cout << "max - " << f.maxElem() << std::endl;
    std::cout << "min - " << f.minElem() << std::endl;
    std::cout << "size - " << f.size() << std::endl;
    std::cout << std::endl;
    f.insert(2, 11);
    f.insert(2, 15);
    f.print();
    std::cout << "max - " << f.maxElem() << std::endl;
    std::cout << "min - " << f.minElem() << std::endl;
    std::cout << "size - " << f.size() << std::endl;
    std::cout << std::endl;
    f.pop_back();
    f.print();
    std::cout << "max - " << f.maxElem() << std::endl;
    std::cout << "min - " << f.minElem() << std::endl;
    std::cout << "size - " << f.size() << std::endl;
    std::cout << std::endl;
    f.pop_front();
    f.print();
    std::cout << "max - " << f.maxElem() << std::endl;
    std::cout << "min - " << f.minElem() << std::endl;
    std::cout << "size - " << f.size() << std::endl;
    std::cout << std::endl;
    f.remove(1);
    f.print();
    std::cout << "max - " << f.maxElem() << std::endl;
    std::cout << "min - " << f.minElem() << std::endl;
    std::cout << "size - " << f.size() << std::endl;
    std::cout << std::endl;
    //f.insert(-1, 11);
    return 0;
}


