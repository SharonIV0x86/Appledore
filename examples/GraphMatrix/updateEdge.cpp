#include <iostream>
#include "../../include/GraphMatrix.hpp"

using namespace Appledore;


int main()
{
    try
    {
        // Test 1: Directed Weighted Graph
        GraphMatrix<int, int, DirectedG> directedWeightedGraph;
        directedWeightedGraph.addVertex(1);
        directedWeightedGraph.addVertex(2);
        directedWeightedGraph.addEdge(1, 2, 10);

        std::cout << "Directed Weighted Graph - Before Update:\n";
        for (const auto &[src, dest, weight] : directedWeightedGraph.getAllEdges())
        {
            std::cout << src << " -> " << dest << " [" << weight << "]\n";
        }

        // Updating an edge
        directedWeightedGraph.updateEdge(1, 2, 50);

        std::cout << "Directed Weighted Graph - After Update:\n";
        for (const auto &[src, dest, weight] : directedWeightedGraph.getAllEdges())
        {
            std::cout << src << " -> " << dest << " [" << weight << "]\n";
        }

        // Test 2: Undirected Weighted Graph
        GraphMatrix<int, int, UndirectedG> undirectedWeightedGraph;
        undirectedWeightedGraph.addVertex(3);
        undirectedWeightedGraph.addVertex(4);
        undirectedWeightedGraph.addEdge(3, 4, 20);

        std::cout << "\nUndirected Weighted Graph - Before Update:\n";
        for (const auto &[src, dest, weight] : undirectedWeightedGraph.getAllEdges())
        {
            std::cout << src << " <-> " << dest << " [" << weight << "]\n";
        }

        // Updating an edge
        undirectedWeightedGraph.updateEdge(3, 4, 100);

        std::cout << "Undirected Weighted Graph - After Update:\n";
        for (const auto &[src, dest, weight] : undirectedWeightedGraph.getAllEdges())
        {
            std::cout << src << " <-> " << dest << " [" << weight << "]\n";
        }

    }
    catch (const std::logic_error &e)
    {
        std::cerr << "Caught logic_error: " << e.what() << "\n";
    }

    try
    {
        // Test 4: Attempt to update a non-existent edge (Should throw an error)
        GraphMatrix<int, int, DirectedG> directedWeightedGraph2;
        directedWeightedGraph2.addVertex(7);
        directedWeightedGraph2.addVertex(8);

        std::cout << "\nAttempting to update a non-existent edge...\n";
        directedWeightedGraph2.updateEdge(7, 8, 30); // Should throw a runtime_error
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Caught runtime_error: " << e.what() << "\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Caught exception: " << e.what() << "\n";
    }

    return 0;
}
