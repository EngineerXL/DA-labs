#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

struct cord_t {
    double x;
    double y;
};

double dist(const cord_t & lhs, const cord_t & rhs) {
    return std::sqrt((lhs.x - rhs.x) * (lhs.x - rhs.x) + (lhs.y - rhs.y) * (lhs.y - rhs.y));
}

struct euristic_t {
    int id;
    double distance;
    double path;

    euristic_t(const int & u_id, const cord_t & u, const cord_t & v, const double & path_to) {
        id = u_id;
        distance = dist(u, v);
        path = path_to;
    }

    friend bool operator < (const euristic_t & lhs, const euristic_t & rhs) {
        if (lhs.path + lhs.distance != rhs.path + rhs.distance) {
            return lhs.path + lhs.distance > rhs.path + rhs.distance;
        } else {
            return lhs.id < rhs.id;
        }
    }
};

double find(const int u, const int v, int n, const std::vector<cord_t> & verticies, const std::vector< std::vector<int> > & g) {
    std::priority_queue<euristic_t> q;
    std::vector<double> d(n, -1);
    d[u] = 0;
    q.push(euristic_t(u, verticies[u], verticies[v], 0));
    while (!q.empty()) {
        euristic_t cur = q.top();
        q.pop();
        if (cur.id == v) {
            break;
        }
        if (cur.path > d[cur.id]) {
            continue;
        }
        for (size_t i = 0; i < g[cur.id].size(); ++i) {
            int next = g[cur.id][i];
            if (d[next] < 0 or d[cur.id] + dist(verticies[cur.id], verticies[next]) < d[next]) {
                d[next] = d[cur.id] + dist(verticies[cur.id], verticies[next]);
                q.push(euristic_t(next, verticies[next], verticies[v], d[next]));
            }
        }

    }
    return d[v];
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<cord_t> verticies(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> verticies[i].x >> verticies[i].y;
    }
    std::vector< std::vector<int> > g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int q;
    std::cin >> q;
    while (q--) {
        int u, v;
        std::cin >> u >> v;
        --u;
        --v;
        double ans = find(u, v, n, verticies, g);
        if (ans > 0) {
            printf("%.6lf\n", ans);
        } else {
            printf("-1\n");
        }
    }
}
