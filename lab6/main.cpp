#include "big_num_lib.hpp"

const TBigNum BIG_ZERO = TBigNum(1);

int main() {
    TBigNum num1, num2;
    char action;
    while (std::cin >> num1 >> num2 >> action) {
        if (action == '+') {
            std::cout << num1 + num2 << '\n';
        }
        if (action == '-') {
            if (num1 < num2) {
                std::cout << "Error\n";
            } else {
                std::cout << num1 - num2 << '\n';
            }
        }
        if (action == '*') {
            std::cout << num1 * num2 << '\n';
        }
        if (action == '^') {
            if (num1 == BIG_ZERO and num2 == BIG_ZERO) {
                std::cout << "Error\n";
            } else {
                std::cout << (num1 ^ num2) << '\n';
            }
        }
        if (action == '/') {
            if (num2 == BIG_ZERO) {
                std::cout << "Error\n";
            } else {
                std::cout << num1 / num2 << '\n';
            }
        }
        if (action == '<') {
            if (num1 < num2) {
                std::cout << "true\n";
            } else {
                std::cout << "false\n";
            }
        }
        if (action == '>') {
            if (num1 > num2) {
                std::cout << "true\n";
            } else {
                std::cout << "false\n";
            }
        }
        if (action == '=') {
            if (num1 == num2) {
                std::cout << "true\n";
            } else {
                std::cout << "false\n";
            }
        }
    }
}
