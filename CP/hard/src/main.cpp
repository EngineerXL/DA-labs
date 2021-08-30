#include <cstring>
#include <iostream>

#include "graph.hpp"
#include "search.hpp"

const int MIN_NUMBER_OF_PARAMETERS = 8;
const int MAX_NUMBER_OF_PARAMETERS = 9;

int main(int argc, char** argv) {
    if (argc < MIN_NUMBER_OF_PARAMETERS or argc > MAX_NUMBER_OF_PARAMETERS) {
        std::cout << "Wrong number of parameters" << std::endl;
        return 1;
    }
    if (strcmp(argv[1], "preprocess") == 0) {
        char* nodes_file = nullptr;
        char* edges_file = nullptr;
        char* output_file = nullptr;
        for (int i = 2; i < argc; ++i) {
            if (strcmp(argv[i], "--nodes") == 0) {
                nodes_file = argv[i + 1];
            } else if (strcmp(argv[i], "--edges") == 0) {
                edges_file = argv[i + 1];
            } else if (strcmp(argv[i], "--output") == 0) {
                output_file = argv[i + 1];
            }
        }
        if (nodes_file == nullptr) {
            std::cout << "Missing nodes file in programm arguments" << std::endl;
            return 1;
        }
        if (edges_file == nullptr) {
            std::cout << "Missing edges file in programm arguments" << std::endl;
            return 1;
        }
        if (output_file == nullptr) {
            std::cout << "Missing output file in programm arguments" << std::endl;
            return 1;
        }
        try {
            preprocess_graph(nodes_file, edges_file, output_file);
        } catch (std::exception & ex) {
            std::cout << ex.what() << std::endl;
            return 1;
        }
        return 0;
    }
    if (strcmp(argv[1], "search") == 0) {
        char* graph_file = nullptr;
        char* input_file = nullptr;
        char* output_file = nullptr;
        bool full_output = false;
        for (int i = 2; i < argc; ++i) {
            if (strcmp(argv[i], "--graph") == 0) {
                graph_file = argv[i + 1];
            } else if (strcmp(argv[i], "--input") == 0) {
                input_file = argv[i + 1];
            } else if (strcmp(argv[i], "--output") == 0) {
                output_file = argv[i + 1];
            } else if (strcmp(argv[i], "--full-output") == 0) {
                full_output = true;
            }
        }
        if (graph_file == nullptr) {
            std::cout << "Missing preprocessed graph file in programm arguments" << std::endl;
            return 1;
        }
        if (input_file == nullptr) {
            std::cout << "Missing input file in programm arguments" << std::endl;
            return 1;
        }
        if (output_file == nullptr) {
            std::cout << "Missing output file in programm arguments" << std::endl;
            return 1;
        }
        try {
            // long long start = clock();
            search_graph(graph_file, input_file, output_file, full_output);
            // long long end = clock();
            // long long time = end - start;
            // printf("A* time is %lli.%.3lli ms\n", time / 1000, time % 1000);
        } catch (std::exception & ex) {
            std::cout << ex.what() << std::endl;
            return 1;
        }
        return 0;
    }
    std::cout << "Invalid parameters!" << std::endl;
    return 2;
}
