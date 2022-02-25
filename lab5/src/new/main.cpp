#include <bits/stdc++.h>

#ifndef SUFFIX_TREE_HPP
#define SUFFIX_TREE_HPP

#include <iostream>
#include <map>
#include <vector>

class suffix_tree_t {
private:
    const static int INF = 1e9;
    const static int TAB_SIZE = 4;

    struct node_t {
        std::map<char, int> go;
        int l, len;
        int link = 0;

        node_t(int _l, int _len) : l(_l), len(_len) {}
    };

    using item_t = std::pair<char, int>;

    bool can_go(int u, char c) {
        return data[u].go.count(c);
    }

    int go(int u, char c) {
        return data[u].go[c];
    }

    std::string s;
    std::vector<node_t> data;

    int size;
    int nodes;

    int u = 0;
    int rem = 0;

    void go_edge() {
        do {
            char c = s[size - rem];
            if (!can_go(u, c)) {
                return;
            }
            int v = go(u, c);
            if (rem > data[v].len) {
                rem -= data[v].len;
                u = v;
            } else {
                return;
            }
        } while (1);
    }

    int create_node(int l = 0, int len = INF) {
        data.push_back(node_t(l, len));
        return ++nodes;
    }

    void build() {
        size = 0;
        nodes = 0;
        for (size_t i = 0; i < s.size(); ++i) {
            extend(s[i]);
        }
    }

    void extend(char c) {
        ++size;
        ++rem;
        int last = 0;
        while (rem) {
            go_edge();
            char a = s[size - rem];
            if (!can_go(u, a)) {
                /* Case 1: creating a leaf */
                data[u].go[a] = create_node(size - rem);
                data[last].link = u;
                last = u;
            } else {
                int v = go(u, a);
                int good_len = rem - 1;
                char t = s[data[v].l + good_len];
                if (t != c) {
                    /* Case 2: splitting an edge */
                    int split = create_node(data[v].l, good_len);
                    int new_v = create_node(size - 1, INF);
                    data[v].len -= good_len;
                    data[v].l += good_len;
                    data[u].go[a] = split;
                    data[split].go[t] = v;
                    data[split].go[c] = new_v;
                    data[last].link = split;
                    last = split;
                } else {
                    /* Case 3: end of phase */
                    data[last].link = u;
                    return;
                }
            }
            if (u == 0) {
                --rem;
            } else {
                u = data[u].link;
            }
        }
    }

    void print_edge(int v, std::ostream & out) {
        int edge_len = std::min(size - data[v].l, data[v].len);
        for (int i = 0; i < edge_len; ++i) {
            out << s[data[v].l + i];
        }
    }

    void print(int id, std::ostream & out, int h) {
        for (item_t elem : data[id].go) {
            for (int i = 0; i < TAB_SIZE * (h - 1); ++i) {
                out << ' ';
            }
            int v = elem.second;
            out << "|-> {id = " << v << ", ";
            print_edge(v, out);
            out << ", link = " << data[v].link << "}\n";
            print(v, out, h + 1);
        }
    }
public:
    suffix_tree_t(const std::string & _s) : s(_s) {
        create_node(0, INF);
        build();
    }

    friend std::ostream & operator << (std::ostream & out, suffix_tree_t & st) {
        out << "root\n";
        st.print(0, out, 1);
        return out;
    }

    std::string lex_min(int k) {
        int v = data[0].go.begin()->second;
        int pos = 0;
        std::string res;
        while (k) {
            if (pos == data[v].len) {
                v = data[v].go.begin()->second;
                pos = 0;
            } else {
                res.push_back(s[data[v].l + pos]);
                ++pos;
                --k;
            }
        }
        return res;
    }
};

#endif /* SUFFIX_TREE_HPP */

using namespace std;

using pii = pair<int, int>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s;
    cin >> s;
    std::string t = s + s;
    t.push_back('z' + 1);
    suffix_tree_t st(t);
    cout << st.lex_min(s.size()) << endl;
}
