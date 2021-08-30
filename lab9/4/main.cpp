#include <iostream>
#include <queue>
#include <vector>

struct item_t {
    int64_t weight;
    int id;

    friend bool operator < (const item_t & lhs, const item_t & rhs) {
        if (lhs.weight != rhs.weight) {
            return lhs.weight > rhs.weight;
        } else {
            return lhs.id < rhs.id;
        }
    }
};

int main() {
    int n, m, start, finish;
    std::cin >> n >> m >> start >> finish;
    std::vector< std::vector< std::pair<int, int64_t> > > g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        int64_t w;
        std::cin >> u >> v >> w;
        g[u - 1].push_back(std::make_pair(v - 1, w));
        g[v - 1].push_back(std::make_pair(u - 1, w));
    }
    std::vector<int64_t> d(n, 1e18);
    std::priority_queue<item_t> pq;
    std::vector<bool> visited(n);
    d[start - 1] = 0;
    pq.push({0, start - 1});
    while (!pq.empty()) {
        item_t cur = pq.top();
        pq.pop();
        int u = cur.id;
        if (u == finish - 1) {
            break;
        }
        if (!visited[u]) {
            for (size_t i = 0; i < g[u].size(); ++i) {
                int v = g[u][i].first;
                int64_t w = g[u][i].second;
                if (d[u] + w < d[v]) {
                    d[v] = d[u] + w;
                    pq.push({d[v], v});
                }
            }
            visited[u] = true;
        }
    }
    if (d[finish - 1] == 1e18) {
        std::cout << "No solution\n";
    } else {
        std::cout << d[finish - 1] << '\n';
    }
}
