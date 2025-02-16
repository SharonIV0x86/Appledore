#include <iostream>
#include <set>
#include <vector>
#include <cassert>
#include "../include/GraphMatrix.hpp"
#include "graph_types.hpp"

using namespace Appledore;


namespace Appledore {
    class C_TestGraphMatrix {
        std::set<custom_vertex_1<std::string>> expected_neighbors_v8;
        size_t expected_degree_v8;

    public:
        GraphMatrix<custom_vertex_1<std::string>, int, UndirectedG> ggraph;
        std::vector<custom_vertex_1<std::string>> vertices;

        C_TestGraphMatrix()
            : vertices{
                  custom_vertex_1<std::string>("vertex_1", true),
                  custom_vertex_1<std::string>("vertex_2", true),
                  custom_vertex_1<std::string>("vertex_3", true),
                  custom_vertex_1<std::string>("vertex_4", true),
                  custom_vertex_1<std::string>("vertex_5", true),
                  custom_vertex_1<std::string>("vertex_6", true),
                  custom_vertex_1<std::string>("vertex_7", true),
                  custom_vertex_1<std::string>("vertex_8", true)} {}

        void create_graph() {
            for (auto &v : vertices) ggraph.addVertex(v);

            std::vector<std::tuple<int, int, int>> edges = {
                {0, 1, 6}, {0, 3, 19}, {0, 7, 31},
                {1, 2, 12}, {2, 6, 46}, {2, 7, 48},
                {7, 4, 27}, {7, 5, 92}, {5, 6, 38}};

            for (auto &[i, j, weight] : edges)
                ggraph.addEdge(vertices[i], vertices[j], weight);

            expected_neighbors_v8 = {vertices[0], vertices[2], vertices[4], vertices[5]};
            expected_degree_v8 = expected_neighbors_v8.size();
        }

        void test_totalDegree() {
            size_t observed = ggraph.totalDegree(vertices[7]);
            if (observed == expected_degree_v8) {
                printColoredText("✔ totalDegree() passed!", ANSI_COLOR_GREEN);
            } else {
                printColoredText("✘ totalDegree() failed! Expected: " + std::to_string(expected_degree_v8) + ", Got: " + std::to_string(observed), ANSI_COLOR_RED);
            }
        }

        void test_getNeighbors() {
            auto observed = ggraph.getNeighbors(vertices[7]);
            if (observed == expected_neighbors_v8) {
                printColoredText("✔ getNeighbors() passed!", ANSI_COLOR_GREEN);
            } else {
                std::string msg = "✘ getNeighbors() failed! Expected: { ";
                for (const auto &v : expected_neighbors_v8) msg += v.get_vertex_name() + " ";
                msg += "}, Got: { ";
                for (const auto &v : observed) msg += v.get_vertex_name() + " ";
                msg += "}";
                printColoredText(msg, ANSI_COLOR_RED);
            }
        }

        void test_hasEdge() {
            bool all_passed = true;
            std::vector<std::tuple<int, int>> expected_edges = {
                {0, 1}, {0, 3}, {0, 7}, {1, 2}, {2, 6}, {2, 7}, {7, 4}, {7, 5}, {5, 6}};

            for (auto &[i, j] : expected_edges) {
                if (!ggraph.hasEdge(vertices[i], vertices[j])) {
                    printColoredText("✘ hasEdge() failed for edge (" + vertices[i].get_vertex_name() + ", " + vertices[j].get_vertex_name() + ")", ANSI_COLOR_RED);
                    all_passed = false;
                }
            }

            if (all_passed) {
                printColoredText("✔ hasEdge() passed for all edges!", ANSI_COLOR_GREEN);
            }
        }
        void show_vertex_data(){
            for(const auto& v: vertices){
                v.show_random_data();
            }
        }
        void test_getVertices() {
            auto observed = ggraph.getVertices();
            std::set<custom_vertex_1<std::string>> observed_set(observed.begin(), observed.end());
            std::set<custom_vertex_1<std::string>> expected_set(vertices.begin(), vertices.end());

            if (observed_set == expected_set) {
                printColoredText("✔ getVertices() passed!", ANSI_COLOR_GREEN);
            } else {
                std::string msg = "✘ getVertices() failed! Expected: { ";
                for (const auto &v : expected_set) msg += v.get_vertex_name() + " ";
                msg += "}, Got: { ";
                for (const auto &v : observed_set) msg += v.get_vertex_name() + " ";
                msg += "}";
                printColoredText(msg, ANSI_COLOR_RED);
            }
        }

        void run_tests() {
            test_totalDegree();
            test_getNeighbors();
            test_hasEdge();
            test_getVertices();
            printColoredText("✅ All tests completed!", ANSI_COLOR_GREEN);
        }
    };
}
