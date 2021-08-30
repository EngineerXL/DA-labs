#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <algorithm>
#include <exception>

#include "misc.hpp"

uint32_t find_node(const std::vector<node_t> & nodes_data, const uint32_t & node_id) {
    int64_t l = -1;
    int64_t r = nodes_data.size();
    while (l + 1 < r) {
        int64_t m = (l + r) / 2;
        if (nodes_data[m].id < node_id) {
            l = m;
        } else {
            r = m;
        }
    }
    return r;
}

void read_nodes(FILE* nodes, std::vector<node_t> & nodes_data) {
    uint32_t cur_vertex = 0;
    double cur_vertex_lat = 0;
    double cur_vertex_lon = 0;
    while (fscanf(nodes, "%u%lf%lf", &cur_vertex, &cur_vertex_lat, &cur_vertex_lon) > 0) {
        nodes_data.push_back({cur_vertex, cur_vertex_lat, cur_vertex_lon});
    }
    std::sort(nodes_data.begin(), nodes_data.end());
}

void read_edges(FILE* edges, std::vector<edge_t> & edges_data) {
    uint32_t road_size = 0;
    while (fscanf(edges, "%u", &road_size) > 0) {
        uint32_t u = 0;
        fscanf(edges, "%u", &u);
        uint32_t v = 0;
        for (uint32_t i = 1; i < road_size; ++i) {
            fscanf(edges, "%u", &v);
            edges_data.push_back({u, v});
            edges_data.push_back({v, u});
            u = v;
        }
    }
    std::sort(edges_data.begin(), edges_data.end());
}

void write_geo_data(FILE* output, const std::vector<node_t> & nodes_data) {
    for (size_t i = 0; i < nodes_data.size(); ++i) {
        fwrite(&nodes_data[i].id, sizeof(uint32_t), 1, output);
        fwrite(&nodes_data[i].lon, sizeof(double), 1, output);
        fwrite(&nodes_data[i].lat, sizeof(double), 1, output);
    }
    fwrite(&nodes_data.back().id, sizeof(uint32_t), 1, output);
    fwrite(&STOP_DATA, sizeof(double), 1, output);
    fwrite(&STOP_DATA, sizeof(double), 1, output);
}

void write_edges(FILE* output, const std::vector<edge_t> & edges_data) {
    for (size_t i = 0; i < edges_data.size(); ++i) {
        uint32_t u = edges_data[i].id_from;
        uint32_t v = edges_data[i].id_to;
        fwrite(&v, sizeof(uint32_t), 1, output);
        size_t j = i + 1;
        while (j < edges_data.size() and edges_data[j].id_from == u) {
            v = edges_data[j].id_to;
            fwrite(&v, sizeof(uint32_t), 1, output);
            ++j;
        }
        i = j - 1;
    }
    uint32_t stop_index = 0;
    fwrite(&stop_index, sizeof(uint32_t), 1, output);
}

void write_offsets(FILE* output, const std::vector<node_t> & nodes_data, const std::vector<edge_t> & edges_data) {
    uint32_t j = 0;
    for (size_t i = 0; i < nodes_data.size(); ++i) {
        while (j < edges_data.size() and find_node(nodes_data, edges_data[j].id_from) < i) {
            ++j;
        }
        fwrite(&j, sizeof(uint32_t), 1, output);
    }
}

void preprocess_graph(char* nodes_file, char* edges_file, char* output_file) {
    FILE* nodes = fopen(nodes_file, "r");
    if (nodes == NULL) {
        throw std::runtime_error("Can't open nodes file");
    }
    FILE* edges = fopen(edges_file, "r");
    if (edges == NULL) {
        throw std::runtime_error("Can't open edges file");
    }
    FILE* output = fopen(output_file, "wb");
    if (output == NULL) {
        throw std::runtime_error("Can't open output file");
    }
    std::vector<node_t> nodes_data;
    std::vector<edge_t> edges_data;
    read_nodes(nodes, nodes_data);
    read_edges(edges, edges_data);
    write_geo_data(output, nodes_data);
    write_edges(output, edges_data);
    write_offsets(output, nodes_data, edges_data);
    fclose(nodes);
    fclose(edges);
    fclose(output);
}

#endif /* GRAPH_HPP */
