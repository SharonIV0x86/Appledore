#include <iostream>
#include <random>
#include <vector>
#include "../include/GraphMatrix.hpp"
#include "graph_types.hpp"
#include <format>
using namespace Appledore;

namespace Appledore
{
    // testing class with custom vertex and edge types.
    class C_TestGraphMatrix
    {

    public:
        size_t true_value_totalDegree_v8;
        std::set<custom_vertex_1<std::string>> true_value_getNeighbors_v8;
        GraphMatrix<custom_vertex_1<std::string>, int, UndirectedG> ggraph;
        custom_vertex_1<std::string> v1;
        custom_vertex_1<std::string> v2;
        custom_vertex_1<std::string> v3;
        custom_vertex_1<std::string> v4;
        custom_vertex_1<std::string> v5;
        custom_vertex_1<std::string> v6;
        custom_vertex_1<std::string> v7;
        custom_vertex_1<std::string> v8;

        // Constructor to initialize the vertices and the graph
        C_TestGraphMatrix()
            : v1("vertex_1", true), v2("vertex_2", true), v3("vertex_3", true), v4("vertex_4", true),
              v5("vertex_5", true), v6("vertex_6", true), v7("vertex_7", true), v8("vertex_8", true) {}

        std::vector<std::pair<custom_vertex_1<std::string>, custom_vertex_1<std::string>>> true_edges = {
                        {v1, v2}, {v1, v4}, {v1, v8}, 
                        {v2, v3}, 
                        {v3, v7}, {v3, v8}, 
                        {v8, v5}, {v8, v6}, 
                        {v6, v7}};
        std::vector<custom_vertex_1<std::string>> true_vertex_vector = {v1,v2,v3,v4,v5,v6,v7,v8};
        GraphMatrix<custom_vertex_1<std::string>, int, UndirectedG> create_graph()
        {
            ggraph.addVertex(v1, v2, v3, v4, v5, v6, v7, v8);

            ggraph.addEdge(v1, v2, 6);
            ggraph.addEdge(v1, v4, 19);
            ggraph.addEdge(v1, v8, 31);

            ggraph.addEdge(v2, v3, 12);

            ggraph.addEdge(v3, v7, 46);
            ggraph.addEdge(v3, v8, 48);

            ggraph.addEdge(v8, v5, 27);
            ggraph.addEdge(v8, v6, 92);

            ggraph.addEdge(v6, v7, 38);

            // populating true_value_vert_neighbors set.
            true_value_getNeighbors_v8.insert(v1);
            true_value_getNeighbors_v8.insert(v3);
            true_value_getNeighbors_v8.insert(v5);
            true_value_getNeighbors_v8.insert(v6);

            // setting known true value of total degree for one vertex v8.
            true_value_totalDegree_v8 = 4;

            return ggraph;
        }
        void test_totalDegree()
        {
            size_t observed_value = ggraph.totalDegree(v8);
            if (observed_value == true_value_totalDegree_v8)
                printColoredText("✔ test_totalDegree() PASSED!", ANSI_COLOR_GREEN);
            else
                printColoredText(std::format("✘ test_totalDegree() FAILED! \n\t Expected: {}, Got: {}", observed_value, true_value_totalDegree_v8), ANSI_COLOR_RED);
        }
        void test_getNeighbors()
        {
            auto observed_value = ggraph.getNeighbors(v8);
            if (observed_value == true_value_getNeighbors_v8)
                printColoredText("✔ test_getNeighbors() PASSED!", ANSI_COLOR_GREEN);
            else
                printColoredText("✘ test_getNeighbors() FAILED!", ANSI_COLOR_RED);
        }
        void test_hasEdge()
        {
            bool all_passed = true;

            for (const auto &edge : true_edges)
            {
                if (!ggraph.hasEdge(edge.first, edge.second))
                {
                    printColoredText(std::format("✘ test_hasEdge() FAILED! \n\tIncorrect edge: {} -> {}", edge.first.get_vertex_name(), edge.second.get_vertex_name()), ANSI_COLOR_RED);
                    return;
                }
            }

            if (all_passed)
            {
                printColoredText("✔ test_hasEdge() PASSED!", ANSI_COLOR_GREEN);
            }
        }

        void test_getVertices()
        {
            std::vector<custom_vertex_1<std::string>> vertices = ggraph.getVertices();
            bool all_passed = true;
            std::vector<custom_vertex_1<std::string>> true_vertices = {v1, v2, v3, v4, v5, v6, v7, v8};
            for (const auto &v : true_vertices)
            {
                if (std::find(vertices.begin(), vertices.end(), v) == vertices.end())
                {
                    printColoredText(std::format("✘ test_getVertices() FAILED! \n\tGot: {} ", v.get_vertex_name()), ANSI_COLOR_RED);
                    return;
                }
            }
            printColoredText("✔ test_getVertices() PASSED!", ANSI_COLOR_GREEN);
        }
        void init_tests()
        {
            test_totalDegree();
            test_getNeighbors();
            test_hasEdge();
            test_getVertices();
        }
        void show_vertex_data()
        {
            printColoredText("\nShowing Vertex data \n", ANSI_COLOR_YELLOW);
            for(const auto& vert: true_vertex_vector){
                // std::cout << "\t";
                vert.show_random_data();
                std::cout << "\n";
            }
        }
    };
}