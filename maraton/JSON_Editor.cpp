#include <iostream>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <string>
#include <sstream>

void object(auto& obj, std::string& str, std::string txt) {
    std::string str1;
    std::size_t pos = str.find(".");
    if (pos != std::string::npos) {
        str1 = str.substr(0, pos);
        auto& obj1 = obj[str1];
        str1 = str.substr(pos + 1);
        object(obj1, str1, txt);
    } else {
        pos = str.find("[");
        if (pos != std::string::npos) {
            if (pos == 0) {
                std::size_t pos1 = str.find("]");
                if (pos1 != std::string::npos) {
                    str1 = str.substr(pos + 1, pos1 - pos - 1);
                    obj[std::stoi(str1)] = txt;
                } else {
                    std::cout << "wrong enter" << std::endl;
                    abort();
                }
            } else {
                str1 = str.substr(0, pos);
                auto& obj1 = obj[str1];
                str1 = str.substr(pos);
                object(obj1, str1, txt);
            }
        } else {
            obj[str] = txt;
        }
    }
}

void read(std::string& text, std::string file_name)
{
    Json::Reader reader;
    Json::Value root;
    Json::StyledStreamWriter writer;
    std::ofstream outFile;
    if(!reader.parse(text, root)) {
        std::cout << reader.getFormattedErrorMessages();
        exit(1);
    } else {
        std::string current;
        while(true) {
            std::cout << "input instruction\n" << std::endl;
            std::getline(std::cin, current);
            if (current == "exit") {
                outFile.open(file_name);
                writer.write(outFile, root);
                outFile.close();
                return;
            }
            std::size_t pos = current.find("=");
            std::string value = "";
            if (pos != std::string::npos) {
                value = current.substr(pos);
                std::size_t pos1 = value.find(" ");
                if (pos1 != std::string::npos) {
                    value = value.substr(pos1 + 1);
                }
            } else {
                std::cout << "Wrong enter" << std::endl;
                abort();
            }
            current = current.substr(0, pos);
            std::size_t pos1 = current.find(" ");
            if (pos1 != std::string::npos) {
                current = current.substr(0, pos1);
            }
            object(root, current, value);
        }
    }
}

int main(int argc, char** argv)
{
    if (argc <= 1) {
        std::cout << "don't give file" << std::endl;
        return 0;
    }
    std::ifstream myFile(argv[1]);
    std::ostringstream tmp;
    tmp << myFile.rdbuf();
    std::string text = tmp.str();
    std::cout << text << std::endl;
    read(text, argv[1]);
    return 0;
}
