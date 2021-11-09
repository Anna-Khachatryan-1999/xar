#ifndef PHONE_BOOK_H
#define PHONE_BOOK_H

#include <fstream>
#include <string>
#include <vector>

class OpenFile
{
public:
    OpenFile(std::string fileName);
    void rightFile();
    ~OpenFile();
private:
    std::ifstream m_file;
};

class ChangeFile
{
public:
    ChangeFile(std::string);
    ~ChangeFile();

public:
    void addContact(std::string str);
    void deleteContact(int number);
    void changeContact(int number);
    void cinContact(std::string&);

private:
    std::fstream m_file;
    std::vector<std::string> m_vec;
};

#endif // PHONEBOOK_H
