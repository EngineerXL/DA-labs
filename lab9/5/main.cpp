#include <iostream>
#include <vector>

struct edge_t {
    int from, to;
    int64_t weight;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int n, m, start, finish;
    std::cin >> n >> m >> start >> finish;
    // Лучше хранить сами рёбра, а не граф
    std::vector<edge_t> edges(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> edges[i].from >> edges[i].to >> edges[i].weight;
    }
    std::vector<int64_t> d(n, 1e18);
    d[start - 1] = 0;
    bool changed = true;
    for (int i = 0; changed and i < n; ++i) {
        changed = false;
        for (int j = 0; j < m; ++j) {
            int a = edges[j].from - 1;
            int b = edges[j].to - 1;
            int64_t w = edges[j].weight;
            if (d[a] + w < d[b]) {
                changed = true;
                d[b] = d[a] + w;
            }
        }
    }
    if (d[finish - 1] == 1e18) {
        std::cout << "No solution\n";
    } else {
        std::cout << d[finish - 1] << '\n';
    }
}
