#include <iostream>
#include <map>

int sub(int a, int b) {
    return a - b;
}

int sum(int a, int b) {
    return a + b;
}

int mul(int a, int b) {
    return a * b;
}

int dive(int a, int b) {
    if (b == 0) {
        std::cout << "error" << std::endl;
        return 0;
    }
    return a / b;
}

int main()
{
    std::map<char, int (*)(int, int)> m { {'-', &sub}, {'+', &sum}, {'*', mul}, {'/', dive} };

    char simbol;
    int a, b;
    std::cin >> simbol;
    std::cin >> a >> b;
    std::cout << m[simbol](a, b);
    return 0;
}
