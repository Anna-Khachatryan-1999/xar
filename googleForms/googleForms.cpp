#include <iostream>
#include "googleForms.h"

CreateFile::CreateFile(std::string filename) : m_file{filename}
{
    m_fileName = filename;
}

void CreateFile::writeToTheFile(int count0fQuestions)
{
    int countCurrentNumber;
    std::string str;
    std::cout << "enter the questions" << std::endl;
    for (int i = 1; i < count0fQuestions + 1; ++i) {
        std::cout << std::endl << i << ". ";
        std::string currentNumber = std::to_string(i);
        std::cin.ignore(1);
        std::getline(std::cin, str);
        m_file << currentNumber << ". " << str << "\n";
        std::cout << "Please enter the number of replies" << std::endl;
        std::cin >> countCurrentNumber;
        std::cout << std::endl;
        str.clear();
        char option = 'a';
        std::cin.ignore(1);
        int count = countCurrentNumber;
        while (countCurrentNumber) {
            std::cout << option << ": ";
            str += option;
            m_file << "  " << str << ": ";
            std::getline(std::cin, str);
            m_file << str << "\n";
            option += 1;
            --countCurrentNumber;
            str.clear();
        }
       std::cout << "enter the correct answer" << std::endl;
       std::cin >> option;
       while(true) {
        if ((option - 'a') >= count || (option - 'a') < 0) {
              std::cout << "error: There is no such option, try again" << std::endl;
              std::cin >> option;
        } else {
            break;
        }
       }
       str += option;
       m_file << "Answer: " << str << "\n\n";
    }
    addFileNameToData();
}

void CreateFile::addFileNameToData()
{
    std::fstream myData ("data.txt", std::fstream::out | std::fstream::app);
    myData << m_fileName << "\n";
    myData.close();
}

CreateFile::~CreateFile()
{
    m_file.close();
}

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
    while (std::getline(m_file, str)) {
        if (str.find("Answer: ") == 0) {
            char answer;
            std::cout << "\nenter the answer -> ";
            std::cin >> answer;
            if (helpAnswer(str) != answer) {
                std::cout << "no: wrong answer" << std::endl;
                std::cout << "The correct answer is ֊ " << helpAnswer(str) << std::endl;
            } else {
                std::cout << "good: right answer ^_^" << std::endl;
            }
        }
        else {
            std::cout << str << std::endl;
        }
    }
}

char OpenFile::helpAnswer(std::string currentLine) const
{
    size_t size = currentLine.find("Answer: ");
    while (true) {
        if (currentLine[size + 8] != ' ') {
            return currentLine[size + 8];
        }
        ++size;
    }
}

OpenFile::~OpenFile()
{
    m_file.close();
}

void showAllFileName()
{
    std::fstream myData ("data.txt", std::fstream::in);
    std::string str;
    while(std::getline(myData, str)) {
        std::cout << str << " ";
    }
    std::cout << std::endl;
    myData.close();
}


bool isAdministrator()
{
    std::cout << "user - ";
    std::string userName, userPasswod;
    std::cin >> userName;
    if (userName == "USER") {
        std::cout << "password - ";
        std::cin >> userPasswod;
        if (userPasswod == "USER2021") {
            return true;
        }
    }
    return false;
}

int main()
{
    std::cout << "\nPlease select your position\n" << std::endl;
    std::cout << "1. Student" << std::endl;
    std::cout << "2. Administrator\n" << std::endl;
    std::string fileName;
    int currentInput;
    std::cin >> currentInput;
    if (currentInput == 1) {
        showAllFileName();
        std::string fileName;
        std::cout << "\nPlease enter a filename\n" << std::endl;
        std::cin >> fileName;
        OpenFile op(fileName);
        op.rightFile();
    } else if (currentInput == 2) {
        if (isAdministrator()) {
        std::cout << "\nPlease enter a filename\n" << std::endl;
        std::cin >> fileName;
        CreateFile file(fileName);
        int count;
        std::cout << "\nPlease enter the number of questions selected\n";
        std::cin >> count;
        file.writeToTheFile(count);
        } else {
            std::cout << "error: Wrong user or password" << std::endl;
        }
    } else {
        std::cout << "error: wrong entry" << std::endl;
        return -1;
    }
    return 0;
}
