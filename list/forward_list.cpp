#include <iostream>

template <typename T>
class List
{
public:
    List<T>();
    List<T>(T elem);
    void push_back(T elem);
    void push_front(T elem);
    void pop_front();
    void pop_back();
    void insert(int index, T elem);
    void erase(int index);
    void print();

private:
    struct Node
    {
        T value;
        Node* next = nullptr;
    };
private:
    Node* head = nullptr;
};

template <typename T>
List<T>::List(){}

template <typename T>
List<T>::List(T elem) {
    Node* node = new Node();
    node->value = elem;
    head = node;
}

template <typename T>
void List<T>::push_back(T elem)
{
    Node* node = head;
    if (node == nullptr) {
        Node* node1 = new Node();
        node1->value = elem;
        head = node1;
        return;
    }
    while(node->next != nullptr) {
        node = node->next;
    }
    Node* node1 = new Node();
    node1->value = elem;
    node->next = node1;
}


template <typename T>
void List<T>::push_front(T elem)
{
    Node* node = new Node();
    node->value = elem;
    node->next = head;
    head = node;
}

template <typename T>
void List<T>::pop_front()
{
    if(head == nullptr) {
        std::cout << "don't have element" << std::endl;
        abort;
    }
    if(head->next == nullptr) {
        head = nullptr;
        return;
    }
    Node* tmp = head;
    head = head->next;
    tmp->next = nullptr;
}

template <typename T>
void List<T>::pop_back()
{
    if(head == nullptr) {
        std::cout << "don't have element" << std::endl;
        abort;
    }
    if(head->next == nullptr) {
        head = nullptr;
        return;
    }
    Node* tmp = head;
    while(tmp->next->next != nullptr)
    {
        tmp = tmp->next;
    }
    tmp->next = nullptr;
}

template <typename T>
void List<T>::insert(int index, T elem)
{
    if(head == nullptr) {
        if (index == 0) {
            Node* node = new Node();
            node->value = elem;
            head = node;
            return;
        }
        std::cout << "error: wrong index" << std::endl;
        abort();
    }
    if (index == 0) {
        Node* node = new Node();
        node->value = elem;
        node->next = head;
        head = node;
        return;
    }
    Node* node = head;
    for (int i = 0; i < index - 1; ++i) {
        if (node->next != nullptr) {
            node = node->next;
        } else {
            std::cout << "error: wrong index" << std::endl;
            abort();
        }
    }
    Node* tmp = new Node();
    tmp->value = elem;
    tmp->next = node->next;
    node->next = tmp;
}

template <typename T>
void List<T>::erase(int index)
{
    if(head == nullptr) {
        std::cout << "error: don't have element" << std::endl;
        abort();
    }
    if (index == 0) {
        Node* tmp = head->next;
        head = head->next;
        tmp = nullptr;
        return;
    }
    Node* node = head;
    for (int i = 0; i < index - 1; ++i) {
        if (node->next != nullptr) {
            node = node->next;
        } else {
            std::cout << "error: wrong index" << std::endl;
            abort();
        }
    }
    if(node -> next == nullptr) {
        std::cout << "error: wrong index" << std::endl;
        abort();
    }
    Node* tmp = node->next;
    node->next = tmp->next;
    tmp->next = nullptr;

}

template <typename T>
void List<T>::print()
{
    Node* node = head;
    while(node != nullptr) {
        std::cout << node->value << " -> ";
        node = node->next;
    }
    std::cout << std::endl;
}


int main()
{
    List<int> l1;
    l1.push_back(5);
    l1.push_back(1);
    l1.push_back(7);
    l1.push_back(6);
    l1.push_back(4);
    l1.pop_back();
    l1.pop_front();
    l1.print();
    l1.insert(2, 9);
    l1.print();
    l1.insert(0, 19);
    l1.print();
    l1.erase(3);
    l1.print();
    return 0;
}
