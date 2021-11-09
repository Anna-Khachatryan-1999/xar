#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void changeText(std::string& str)
{
   std::string str1;
   std::string cur;
   bool b = true;
    for(int i = 0; i < str.size(); ++i) {
        while (i < str.size() && str[i] >= 'a' && str[i] <= 'z') {
            cur += str[i];
            ++i;
            b = false;
        }
        if (!b) {
            cur[0] -= 32;
            cur[cur.size()-1] -= 32;
            str1 += cur;
            cur.clear();
            b = true;
        }
        if (i < str.size()) {
            str1 += str[i];
        }
    }
    str = str1;
}

void textFileCapitalizer(std::string str1) {
    std::fstream m_file (str1);
    std::vector<std::string> m_vec;
    std::string str;
    while (std::getline(m_file, str)) {
        changeText(str);
        m_vec.push_back(str);
    }
    m_file.close();
    m_file.open(str1, std::fstream::out);
    for (int i = 0; i < m_vec.size(); ++i)
        m_file << m_vec[i] << "\n";
    m_vec.clear();
}

int main(int argc, char** argv)
{
    if (argc <= 1) {
        std::cout << "don't give file" << std::endl;
        return 0;
    }
    textFileCapitalizer(argv[1]);
    return 0;
}
