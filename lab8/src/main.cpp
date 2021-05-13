#include <algorithm>
#include <iostream>
#include <vector>

using TGraph = std::vector< std::vector<int> >;

const int COLOUR_WHITE = 0;
const int COLOUR_GRAY = 1;
const int COLOUR_BLACK = 2;

bool DFSCycle(int u, const TGraph & g, std::vector<int> & colour) {
    if (colour[u] == COLOUR_GRAY) {
        return true;
    } else if (colour[u] == COLOUR_BLACK) {
        return false;
    }
    colour[u] = COLOUR_GRAY;
    for (size_t i = 0; i < g[u].size(); ++i) {
        int v = g[u][i];
        if (DFSCycle(v, g, colour)) {
            return true;
        }
    }
    colour[u] = COLOUR_BLACK;
    return false;
}

void DFS(int u, const TGraph & g, std::vector<int> & visited, std::vector<int> & res) {
    if (visited[u]) {
        return;
    }
    visited[u] = true;
    for (size_t i = 0; i < g[u].size(); ++i) {
        int v = g[u][i];
        DFS(v, g, visited, res);
    }
    res.push_back(u);
}

int main() {
    int n, m;
    std::cin >> n >> m;
    /* Граф может быть несвязным, добавим виртуальную вершину */
    TGraph g(n + 1);
    for (int i = 0; i < n; ++i) {
        g.back().push_back(i);
    }
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u - 1].push_back(v - 1);
    }
    /* Проверяем граф на наличие циклов */
    std::vector<int> colour(n + 1, COLOUR_WHITE);
    if (DFSCycle(n, g, colour)) {
        std::cout << "-1\n";
        return 0;
    }
    /*
     * Выполняем обход полученного графа и
     * запоминаем вершины в порядке обхода
     */
    std::vector<int> res;
    std::vector<int> visited(n + 1);
    DFS(n, g, visited, res);
    /*
     * Сперва идут самые глубокие вершины,
     * поэтому нужен реверс
     */
    std::reverse(res.begin(), res.end());
    for (size_t i = 1; i < res.size() - 1; ++i) {
        std::cout << res[i] + 1 << ' ' << res[i + 1] + 1 << '\n';
    }
}
