#include <iostream>
#include <random>
#include <vector>
#include "../include/GraphMatrix.hpp"
#include "graph_types.hpp"
using namespace Appledore;

namespace Appledore
{
    // testing class with custom vertex and edge types.
    class C_TestGraphMatrix
    {
        std::set<custom_vertex_1<std::string>> true_value_getNeighbors_v8;
        size_t true_value_totalDegree_v8;

    public:
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
            : v1("vertex_1"), v2("vertex_2"), v3("vertex_3"), v4("vertex_4"),
              v5("vertex_5"), v6("vertex_6"), v7("vertex_7"), v8("vertex_8") {}

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
        bool test_totalDegree()
        {
            size_t observed_value = ggraph.totalDegree(v8);
            if (observed_value == true_value_totalDegree_v8)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        bool test_getNeighbors()
        {
            auto observed_value = ggraph.getNeighbors(v8);
            if (observed_value == true_value_getNeighbors_v8)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        bool test_isConnected(){
            
        }
        void init_tests()
        {
            // testing totalDegree()
            if (!test_totalDegree())
            {
                std::cout << "test_totalDegree() -->    ";
                printColoredText("FAILED\n", ANSI_COLOR_RED);
            }
            else
            {
                std::cout << "test_totalDegree -->      ";
                printColoredText("PASSED\n", ANSI_COLOR_GREEN);
            }
            // testing getNeighbors
            if (!test_getNeighbors())
            {
                std::cout << "test_getNeighbors() -->   ";
                printColoredText("FAILED\n", ANSI_COLOR_RED);
            }
            else
            {
                std::cout << "test_getNeighbors() --> ";
                printColoredText("PASSED\n", ANSI_COLOR_GREEN);
            }
        }
    };
}