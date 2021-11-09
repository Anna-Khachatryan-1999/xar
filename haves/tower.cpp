#include <iostream>
#include <string>

void tower (int n) {
    std::string str{};
    for (int i = 0; i < 2*n + 2; ++i) {
        str += ' ';
    }
    for (int i = 0; i < n; ++i) {
        str[n-1-i] = '#';
        str[n+1+i] = '#';
        std::cout << str << std::endl;
    }
}

int main()
{
    int n;
    std::cin >> n;
    tower (n);
    return 0;
}
