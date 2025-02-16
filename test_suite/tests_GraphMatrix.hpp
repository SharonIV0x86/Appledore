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
            : v1("vertex_1", true), v2("vertex_2", true), v3("vertex_3", true), v4("vertex_4", true),
              v5("vertex_5", true), v6("vertex_6", true), v7("vertex_7", true), v8("vertex_8", true) {}

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
        bool test_hasEdge()
        {
            if (!ggraph.hasEdge(v1, v2) || !ggraph.hasEdge(v1, v4) ||
                !ggraph.hasEdge(v1, v8))
            {
                return false;
            }

            if (!ggraph.hasEdge(v2, v3))
            {
                return false;
            }
            if (!ggraph.hasEdge(v3, v7) || !ggraph.hasEdge(v3, v8))
            {
                return false;
            }
            if (!ggraph.hasEdge(v8, v5) || !ggraph.hasEdge(v8, v6))
            {
                return false;
            }
            if (!ggraph.hasEdge(v6, v7))
            {
                return false;
            }
            return true;
        }
        bool test_getVertices()
        {
            std::vector<custom_vertex_1<std::string>> vertices = ggraph.getVertices();

            if (std::find(vertices.begin(), vertices.end(), v1) == vertices.end())
            {
                return false;
            }

            if (std::find(vertices.begin(), vertices.end(), v2) == vertices.end())
            {
                return false;
            }

            if (std::find(vertices.begin(), vertices.end(), v3) == vertices.end())
            {
                return false;
            }

            if (std::find(vertices.begin(), vertices.end(), v4) == vertices.end())
            {
                return false;
            }

            if (std::find(vertices.begin(), vertices.end(), v5) == vertices.end())
            {
                return false;
            }

            if (std::find(vertices.begin(), vertices.end(), v6) == vertices.end())
            {
                return false;
            }

            if (std::find(vertices.begin(), vertices.end(), v7) == vertices.end())
            {
                return false;
            }

            if (std::find(vertices.begin(), vertices.end(), v8) == vertices.end())
            {
                return false;
            }
            return true;
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
                std::cout << "test_totalDegree() -->      ";
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
            if (!test_hasEdge())
            {
                std::cout << "test_hasEdge() ";
                printColoredText("FAILED\n", ANSI_COLOR_RED);
            }
            else
            {
                std::cout << "test_hasEdge() --> ";
                printColoredText("PASSED\n", ANSI_COLOR_GREEN);
            }
            if(!test_getVertices()){
                std::cout << "test_getVertices() --> ";
                printColoredText("FAILED\n", ANSI_COLOR_RED);
            }else{
                std::cout << "test_getVertices() --> ";
                printColoredText("PASSED\n", ANSI_COLOR_GREEN);

            }
        }
        void show_vertex_data()
        {
            std::cout << "\nVertex 1 data: ";
            v1.show_random_data();

            std::cout << "\nVertex 2 data: ";
            v2.show_random_data();

            std::cout << "\nVertex 3 data: ";
            v3.show_random_data();

            std::cout << "\nVertex 4 data: ";
            v4.show_random_data();

            std::cout << "\nVertex 5 data: ";
            v5.show_random_data();

            std::cout << "\nVertex 6 data: ";
            v6.show_random_data();

            std::cout << "\nVertex 7 data: ";
            v7.show_random_data();

            std::cout << "\nVertex 8 data: ";
            v8.show_random_data();
        }
    };
}