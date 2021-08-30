#include <iostream>
#include <queue>
#include <vector>

const int64_t INF = 1e18;

struct edge_t {
    int from, to;
    int64_t weight;
};

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
    int n, m;
    std::cin >> n >> m;
    // Для Форда-Беллмана
    std::vector<edge_t> edges(m);
    // Для Дейкстры
    std::vector< std::vector< std::pair<int, int64_t> > > g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        int64_t w;
        std::cin >> u >> v >> w;
        edges[i] = {u - 1, v - 1, w};
        g[u - 1].push_back(std::make_pair(v - 1, w));
    }
    for (int i = 0; i < n; ++i) {
        edges.push_back({n, i, 0});
    }
    // Форд-Беллман
    std::vector<int64_t> h(n + 1, INF);
    h[n] = 0;
    bool changed = true;
    for (int i = 0; changed and i < n + 1; ++i) {
        changed = false;
        for (size_t j = 0; j < edges.size(); ++j) {
            int a = edges[j].from;
            int b = edges[j].to;
            int64_t w = edges[j].weight;
            if (h[a] + w < h[b]) {
                changed = true;
                h[b] = h[a] + w;
            }
        }
    }
    if (changed) {
        std::cout << "Negative cycle\n";
        return 0;
    }
    // Изменение весов рёбер
    for (int i = 0; i < n; ++i) {
        for (size_t j = 0; j < g[i].size(); ++j) {
            int u = i;
            int v = g[u][j].first;
            g[u][j].second = g[u][j].second + h[u] - h[v];
        }
    }
    // Дейкстра
    for (int i = 0; i < n; ++i) {
        std::vector<int64_t> d(n, INF);
        std::priority_queue<item_t> pq;
        std::vector<bool> visited(n);
        d[i] = 0;
        pq.push({0, i});
        while (!pq.empty()) {
            item_t cur = pq.top();
            pq.pop();
            int u = cur.id;
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
        for (int j = 0; j < n; ++j) {
            if (d[j] == INF) {
                std::cout << "inf ";
            } else {
                std::cout << d[j] + h[j] - h[i] << " ";
            }
        }
        std::cout << "\n";
    }
}
