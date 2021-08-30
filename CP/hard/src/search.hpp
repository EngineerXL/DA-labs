#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <queue>

#include "misc.hpp"

void read_geo(FILE* graph, uint32_t & id, double & lon, double & lat) {
    fread(&id, sizeof(uint32_t), 1, graph);
    fread(&lon, sizeof(double), 1, graph);
    fread(&lat, sizeof(double), 1, graph);
}

void read_geo_data(FILE* graph, std::vector<uint32_t> & ids) {
    uint32_t id;
    double lon = 0;
    double lat = 0;
    while (lon < STOP_DATA) {
        read_geo(graph, id, lon, lat);
        ids.push_back(id);
    }
    ids.pop_back();
}

size_t count_edges(FILE* graph) {
    size_t m = 0;
    uint32_t id = 1;
    while (id > 0) {
        fread(&id, sizeof(uint32_t), 1, graph);
        ++m;
    }
    return m - 1;
}

void read_offsets(FILE* graph, std::vector<uint32_t> & offsets) {
    for (size_t i = 0; i < offsets.size() - 1; ++i) {
        fread(&offsets[i], sizeof(uint32_t), 1, graph);
    }
}

uint32_t find_node_index(const std::vector<uint32_t> & ids, const uint32_t node_id) {
    int64_t l = -1;
    int64_t r = ids.size();
    while (l + 1 < r) {
        int64_t m = (l + r) / 2;
        if (ids[m] < node_id) {
            l = m;
        } else {
            r = m;
        }
    }
    return r;
}

node_t get_node_file(FILE* graph, const uint32_t node_index) {
    fseek(graph, GEODATA_SIZE * node_index, 0);
    node_t res;
    read_geo(graph, res.id, res.lon, res.lat);
    return res;
}

void prolong(FILE* graph, node_t finish, uint32_t cur_index, const std::vector<uint32_t> & ids, const std::vector<uint32_t> & offsets, std::vector<uint32_t> & prev, std::vector<double> & d, std::priority_queue<euristic_t> & q) {
    node_t cur_node = get_node_file(graph, cur_index);
    uint32_t cur_offset = offsets[cur_index];
    std::vector<uint32_t> adjanced_nodes;
    fseek(graph, GEODATA_SIZE * (ids.size() + 1) + cur_offset * sizeof(uint32_t), 0);
    for (uint32_t i = cur_offset; i < offsets[cur_index + 1]; ++i) {
        uint32_t next = 0;
        fread(&next, sizeof(uint32_t), 1, graph);
        adjanced_nodes.push_back(next);
    }
    for (size_t i = 0; i < adjanced_nodes.size(); ++i) {
        uint32_t next = adjanced_nodes[i];
        uint32_t next_index = find_node_index(ids, next);
        node_t next_node = get_node_file(graph, next_index);
        double cur_next_dist = geo_dist(cur_node, next_node);
        if (d[next_index] < 0 or (std::abs(d[next_index] - (d[cur_index] + cur_next_dist)) > EPS and d[next_index] > d[cur_index] + cur_next_dist)) {
            d[next_index] = d[cur_index] + cur_next_dist;
            prev[next_index] = cur_index;
            q.push(euristic_t(next, next_node, finish, d[next_index]));
        }
    }
}

double euristic_find(FILE* graph, const std::vector<uint32_t> & ids, const std::vector<uint32_t> & offsets, const uint32_t u, const uint32_t v, std::vector<uint32_t> & prev, std::vector<double> & d) {
    uint32_t v_index = find_node_index(ids, v);
    node_t v_node = get_node_file(graph, v_index);
    uint32_t u_index = find_node_index(ids, u);
    node_t u_node = get_node_file(graph, u_index);
    d[u_index] = 0;
    prev[u_index] = u_index;
    std::priority_queue<euristic_t> q;
    q.push(euristic_t(u, u_node, v_node, 0));
    while (!q.empty()) {
        euristic_t cur = q.top();
        q.pop();
        uint32_t cur_index = find_node_index(ids, cur.id);
        if (cur.path > d[cur_index]) {
            continue;
        }
        if (cur.id == v) {
            break;
        }
        prolong(graph, v_node, cur_index, ids, offsets, prev, d, q);
    }
    return d[v_index];
}

void get_path(FILE* graph, uint32_t node_id, const std::vector<uint32_t> prev, std::vector<uint32_t> & res) {
    while (prev[node_id] != node_id) {
        node_t cur_node = get_node_file(graph, node_id);
        res.push_back(cur_node.id);
        node_id = prev[node_id];
    }
    node_t cur_node = get_node_file(graph, node_id);
    res.push_back(cur_node.id);
}

void execute_search(FILE* input, FILE* output, FILE* graph, const std::vector<uint32_t> & ids, const std::vector<uint32_t> & offsets, bool full_output) {
    size_t n = ids.size();
    std::vector<uint32_t> prev(n);
    std::vector<double> d(n);
    uint32_t u = 0;
    uint32_t v = 0;
    while (fscanf(input, "%u%u", &u, &v) > 0) {
        prev.assign(n, 0);
        d.assign(n, -1);
        double ans = euristic_find(graph, ids, offsets, u, v, prev, d);
        uint32_t v_index = find_node_index(ids, v);
        if (full_output) {
            if (d[v_index] < 0) {
                fprintf(output, "-1 0\n");
            } else {
                fprintf(output, "%.6lf ", ans);
                std::vector<uint32_t> path;
                get_path(graph, v_index, prev, path);
                fprintf(output, "%li ", path.size());
                for (size_t i = path.size() - 1; i > 0; --i) {
                    fprintf(output, "%u ", path[i]);
                }
                fprintf(output, "%u\n", path[0]);
            }
        } else {
            if (d[v_index] < 0) {
                fprintf(output, "-1\n");
            } else {
                fprintf(output, "%.6lf\n", ans);
            }
        }
    }
}

void search_graph(char* graph_file, char* input_file, char* output_file, bool full_output) {
    FILE* graph = fopen(graph_file, "rb");
    if (graph == NULL) {
        throw std::runtime_error("Can't open preprocessed graph file");
    }
    FILE* input = fopen(input_file, "r");
    if (input == NULL) {
        throw std::runtime_error("Can't open input file");
    }
    FILE* output = fopen(output_file, "w");
    if (output == NULL) {
        throw std::runtime_error("Can't open output file");
    }
    std::vector<uint32_t> ids;
    read_geo_data(graph, ids);
    size_t m = count_edges(graph);
    std::vector<uint32_t> offsets(ids.size() + 1);
    offsets.back() = m;
    read_offsets(graph, offsets);
    execute_search(input, output, graph, ids, offsets, full_output);
    fclose(graph);
    fclose(input);
    fclose(output);
}

#endif /* SEARCH_HPP */
