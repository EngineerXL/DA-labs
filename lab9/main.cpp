#include <algorithm>
#include <iostream>
#include <vector>

using TVecVecInt = std::vector< std::vector<int> >;

bool DFS(int u, const TVecVecInt & g, std::vector<bool> & visited, TVecVecInt & res) {
    if (visited[u]) {
        return false;
    }
    visited[u] = true;
    res.back().push_back(u);
    for (size_t i = 0; i < g[u].size(); ++i) {
        int v = g[u][i];
        DFS(v, g, visited, res);
    }
    return true;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    TVecVecInt g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    std::vector<bool> visited(n);
    TVecVecInt res;
    bool flagNewConnectivity = true;
    for (int i = 0; i < n; ++i) {
        if (flagNewConnectivity) {
            res.push_back(std::vector<int>());
        }
        flagNewConnectivity = DFS(i, g, visited, res);
    }
    if (!flagNewConnectivity) {
        res.pop_back();
    }
    for (size_t i = 0; i < res.size(); ++i) {
        std::sort(res[i].begin(), res[i].end());
    }
    for (size_t i = 0; i < res.size(); ++i) {
        for (size_t j = 0; j < res[i].size(); ++j) {
            std::cout << res[i][j] + 1 << ' ';
        }
        std::cout << '\n';
    }
}
