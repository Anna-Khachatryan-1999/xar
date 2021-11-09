#include <iostream>
#include "phoneBook.h"


OpenFile::OpenFile(std::string fileName) : m_file(fileName)
{
    if (!m_file.is_open()) {
        std::cout << "There is no file named " << fileName << std::endl;
        abort();
    }
}

void OpenFile::rightFile()
{
    std::string str;
    int i = 1;
    while (std::getline(m_file, str)) {
        std::cout << i << ": " <<  str << std::endl;
        ++i;
    }
}

OpenFile::~OpenFile()
{
    m_file.close();
}

ChangeFile::ChangeFile(std::string str) :  m_file(str) {};

void ChangeFile::addContact(std::string str)
{
    m_file.close();
    m_file.open("phoneBook.txt", std::fstream::out | std::fstream::app);
    m_file << str << "\n";
    m_file.close();

}

void ChangeFile::changeContact(int number) {
    std::string str;
    int i = 1;
    std::string str1;
    cinContact(str1);
    std::cin.ignore(1);
    while (std::getline(m_file, str)) {
        if (i == number) {
            ++i;
            m_vec.push_back(str1);
            continue;
        }
        m_vec.push_back(str);
        ++i;
    }
    m_file.close();
    m_file.open("phoneBook.txt", std::fstream::out);
    for (int i = 0; i < m_vec.size(); ++i)
        m_file << m_vec[i] << "\n";
    m_vec.clear();
}

void ChangeFile::deleteContact(int number) {
    std::string str;
    int i = 1;
    while (std::getline(m_file, str)) {
        if (i == number) {
            ++i;
            continue;
        }
        m_vec.push_back(str);
        ++i;
    }
    m_file.close();
    m_file.open("phoneBook.txt", std::fstream::out);
    for (int i = 0; i < m_vec.size(); ++i)
        m_file << m_vec[i] << "\n";
    m_vec.clear();
}

void ChangeFile::cinContact(std::string& str)
{
    std::string current;
    std::cout << "name: ";
    str += "|name-";
    std::cin >> current;
    str += current;
    str += "  ";
    std::cout << "last name: ";
    str += "|last name-";
    std::cin >> current;
    str += current;
    str += "  ";
    std::cout << "phone number: ";
    str += "|phone number-";
    std::cin >> current;
    str += current;
    str += "  ";
    std::cout << "address: ";
    str += "|address-";
    std::cin >> current;
    str += current;
}

ChangeFile::~ChangeFile()
{
    m_file.close();
}

int main()
{
    std::string fileName = "phoneBook.txt";
    while(true) {
        std::cout << "contacts in the book" << std::endl << std::endl;
        OpenFile op(fileName);
        op.rightFile();
        std::cout << "Please enter a number of operation selected\n";
        std::cout << "1: add contact" << std::endl;
        std::cout << "2: change a contact" << std::endl;
        std::cout << "3: delete a contact" << std::endl;
        std::cout << "4: exit" << std::endl;
        int currentInput;
        std::cin >> currentInput;
        if (currentInput == 1) {
            std::string str;
            ChangeFile ch(fileName);
            ch.cinContact(str);
            ch.addContact(str);
        } else if(currentInput == 2) {
            int index;
            std::cin >> index;
            ChangeFile ch(fileName);
            ch.changeContact(index);
        } else if(currentInput == 3) {
            int index;
            std::cin >> index;
            ChangeFile ch(fileName);
            ch.deleteContact(index);
        } else if(currentInput == 4) {
            return 0;
        } else {
            std::cout << "error: wrong entry" << std::endl;
            return -1;
        }
    }
    return 0;
}
