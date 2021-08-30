#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using graph = std::vector< std::vector<int64_t> >;

const int64_t INF = 1e18;

void bfs(int u, const graph & g, const graph & f, std::vector<int> & prev) {
    std::queue<int> q;
    q.push(u);
    prev[u] = u;
    while (!q.empty()) {
        u = q.front();
        q.pop();
        for (size_t i = 0; i < g[u].size(); ++i) {
            int v = i;
            if (prev[v] == -1 and f[u][v] < g[u][v]) {
                prev[v] = u;
                q.push(v);
            }
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    int start = 1, finish = n;
    graph g(n, std::vector<int64_t>(n));
    graph f(n, std::vector<int64_t>(n));
    for (int i = 0; i < m; ++i) {
        int u, v;
        int64_t w;
        std::cin >> u >> v >> w;
        g[u - 1][v - 1] = g[u - 1][v - 1] + w;
    }
    int64_t ans = 0;
    while (1) {
        std::vector<int> prev(n, -1);
        bfs(start - 1, g, f, prev);
        if (prev[finish - 1] == -1) {
            break;
        }
        std::vector<int> path;
        int v = finish - 1;
        while (prev[v] != v) {
            path.push_back(v);
            v = prev[v];
        }
        path.push_back(v);
        std::reverse(path.begin(), path.end());
        int64_t min_path_flow = 1e18;
        for (size_t i = 1; i < path.size(); ++i) {
            int u = path[i - 1];
            int v = path[i];
            min_path_flow = std::min(g[u][v] - f[u][v], min_path_flow);
        }
        for (size_t i = 1; i < path.size(); ++i) {
            int u = path[i - 1];
            int v = path[i];
            f[u][v] = f[u][v] + min_path_flow;
            f[v][u] = f[v][u] - min_path_flow;
        }
        ans = ans + min_path_flow;
    }
    std::cout << ans << std::endl;
}
