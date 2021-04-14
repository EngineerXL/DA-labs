#include <bitset>
#include <iostream>
#include <vector>

const size_t MAX_N = 100;

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> w(n);
    std::vector<long long> c(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> w[i] >> c[i];
    }
    /*
     * Размеры массивов на один больше, чтобы не делать лишних проверок индексов
     * std::bitset<MAX_N> можно заменить на std::vector<bool>
     */
    std::vector< std::vector< long long > > dpPrev(n + 1, std::vector<long long>(m + 1));
    std::vector< std::vector< long long > > dpCur(n + 1, std::vector<long long>(m + 1));
    std::vector< std::vector< std::bitset<MAX_N> > > setPrev(n + 1, std::vector< std::bitset<MAX_N> >(m + 1));
    std::vector< std::vector< std::bitset<MAX_N> > > setCur(n + 1, std::vector< std::bitset<MAX_N> >(m + 1));
    long long ans = 0;
    std::bitset<MAX_N> res;
    /* Берём ровно по одному предмету */
    for (int j = 1; j < n + 1; ++j) {
        for (int k = 1; k < m + 1; ++k) {
            dpPrev[j][k] = dpPrev[j - 1][k];
            setPrev[j][k] = setPrev[j - 1][k];
            if (c[j - 1] > dpPrev[j][k] and k - w[j - 1] == 0) {
                dpPrev[j][k] = c[j - 1];
                setPrev[j][k] = 0;
                setPrev[j][k][j - 1] = 1;
            }
            if (dpPrev[j][k] > ans) {
                ans = dpPrev[j][k];
                res = setPrev[j][k];
            }
        }
    }
    /* Берём два и более предметов */
    for (long long i = 2; i < n + 1; ++i) {
        for (int j = 1; j < n + 1; ++j) {
            for (int k = 1; k < m + 1; ++k) {
                dpCur[j][k] = dpCur[j - 1][k];
                setCur[j][k] = setCur[j - 1][k];
                if (k - w[j - 1] > 0 and dpPrev[j - 1][k - w[j - 1]] > 0) {
                    if (i * (c[j - 1] + dpPrev[j - 1][k - w[j - 1]] / (i - 1)) > dpCur[j][k]) {
                        dpCur[j][k] = i * (c[j - 1] + dpPrev[j - 1][k - w[j - 1]] / (i - 1));
                        setCur[j][k] = setPrev[j - 1][k - w[j - 1]];
                        setCur[j][k][j - 1] = 1;
                    }
                }
                if (dpCur[j][k] > ans) {
                    ans = dpCur[j][k];
                    res = setCur[j][k];
                }
            }
        }
        std::swap(dpCur, dpPrev);
        std::swap(setCur, setPrev);
    }
    std::cout << ans << '\n';
    for (int i = 0; i < n; ++i) {
        if (res[i]) {
            std::cout << i + 1 << ' ';
        }
    }
    std::cout << '\n';
}
