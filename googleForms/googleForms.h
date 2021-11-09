#include <string>
#include <fstream>

class CreateFile
{
public:
    CreateFile(std::string fileName);
    void writeToTheFile(int count0fQuestions);
    void addFileNameToData();
    ~CreateFile();
private:
    std::ofstream m_file;
    std::string m_fileName;
};

class OpenFile
{
public:
    OpenFile(std::string fileName);
    void rightFile();
    ~OpenFile();
private:
    char helpAnswer(std::string currentLine) const;
    std::ifstream m_file;
};


