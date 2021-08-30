#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using graph_t = std::vector< std::vector<int> >;

bool dfs_kunh(int u, const graph_t & g, std::vector<bool> & used, std::vector<int> & matching) {
    if (used[u]) {
        return false;
    }
    used[u] = 1;
    for (size_t i = 0; i < g[u].size(); ++i) {
        int v = g[u][i];
        if (matching[v] == -1 or dfs_kunh(matching[v], g, used, matching)) {
            matching[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    graph_t g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    for (int i = 0; i < n; ++i) {
        std::sort(g[i].begin(), g[i].end());
    }
    // Проверка на двудольность
    bool bipartite = true;
    std::queue<int> q;
    std::vector<int> levels(n, -1);
    for (int i = 0; i < n; ++i) {
        if (levels[i] != -1) {
            continue;
        }
        q.push(i);
        levels[i] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (size_t i = 0; i < g[u].size(); ++i) {
                int v = g[u][i];
                if (levels[v] == -1) {
                    levels[v] = (levels[u] + 1) % 2;
                    q.push(v);
                }
            }
        }
    }
    for (int u = 0; u < n; ++u) {
        for (size_t j = 0; j < g[u].size(); ++j) {
            int v = g[u][j];
            if (levels[v] == levels[u]) {
                bipartite = false;
            }
        }
    }
    if (!bipartite) {
        std::cout << "-1\n";
        return 0;
    }
    // Поиск максимального паросочетания
    int ans = 0;
    std::vector<int> matching(n, -1);
    for (int i = 0; i < n; ++i) {
        if (levels[i]) {
            continue;
        }
        std::vector<bool> used(n);
        dfs_kunh(i, g, used, matching);
    }
    for (int i = 0; i < n; ++i) {
        if (matching[i] != -1) {
            ++ans;
        }
    }
    std::vector< std::pair<int, int> > res;
    for (int i = 0; i < n; ++i) {
        if (matching[i] != -1) {
            if (matching[i] < i) {
                res.push_back(std::make_pair(matching[i] + 1, i + 1));
            } else {
                res.push_back(std::make_pair(i + 1, matching[i] + 1));
            }
        }
    }
    std::sort(res.begin(), res.end());
    std::cout << ans << '\n';
    for (int i = 0; i < ans; ++i) {
        std::cout << res[i].first << ' ' << res[i].second << '\n';
    }
}
