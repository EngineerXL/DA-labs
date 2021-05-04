#include <algorithm>
#include <ctime>
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
    long long start = clock();
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
    long long end = clock();
    long long time = end - start;
    std::cout << "DFS time is " << time / 1000 << '.' << time % 1000 << " ms\n";
}
