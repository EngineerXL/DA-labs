#include "suffix_tree.hpp"
#include <iostream>

const char SENTINEL = 'z' + 1;

int main() {
    std::string s;
    std::cin >> s;
    std::string t = s + s + SENTINEL;
    TSuffixTree st(t);
    std::cout << st.LexMinString(s.size()) << '\n';
    return 0;
}
