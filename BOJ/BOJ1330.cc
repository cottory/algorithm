#include <iostream>

int main(void) {
    int A,B;
    std::cin >> A >> B;
    if (A == B) std::cout << "==";
    else if (A > B) std::cout << ">";
    else std::cout << "<";
}