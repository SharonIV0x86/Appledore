#include <iostream>
#include "../include/GraphMatrix.h"

using namespace Appledore;

int main()
{
    try
    {
        // Directed unweighted graph
        using VertexType = int; 
        using EdgeType = bool; 
        using Direction = DirectedG; 
        GraphMatrix<VertexType, EdgeType, Direction> directedUnweightedGraph;

        directedUnweightedGraph.addVertex(1, 2, 3, 4, 5);
        directedUnweightedGraph.addEdge(1, 2, true);
        directedUnweightedGraph.addEdge(3, 4, true);
        // directedUnweightedGraph.addEdge(3, 5, true);

        std::cout << "Directed unweighted graph - Isolated vertices: ";
        for (const auto &vertex : directedUnweightedGraph.getIsolated())
        {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;

        // Undirected unweighted graph
        using UndirectedEdgeType = bool; 
        using UndirectedDirection = UndirectedG; 
        GraphMatrix<VertexType, UndirectedEdgeType, UndirectedDirection> undirectedUnweightedGraph;

        undirectedUnweightedGraph.addVertex(6, 7, 8, 9);
        undirectedUnweightedGraph.addEdge(6, 7, true);

        std::cout << "Undirected unweighted graph - Isolated vertices: ";
        for (const auto &vertex : undirectedUnweightedGraph.getIsolated())
        {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;

        // Directed weighted graph
        using WeightedEdgeType = int; 
        using WeightedDirection = DirectedG; 
        GraphMatrix<VertexType, WeightedEdgeType, WeightedDirection> directedWeightedGraph;

        directedWeightedGraph.addVertex(10, 11, 12);
        directedWeightedGraph.addEdge(10, 11, 50);

        std::cout << "Directed weighted graph - Isolated vertices: ";
        for (const auto &vertex : directedWeightedGraph.getIsolated())
        {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;

        // Undirected weighted graph
        using UndirectedWeightedEdgeType = int; 
        using UndirectedWeightedDirection = UndirectedG; 
        GraphMatrix<VertexType, UndirectedWeightedEdgeType, UndirectedWeightedDirection> undirectedWeightedGraph;

        undirectedWeightedGraph.addVertex(13, 14, 15);
        undirectedWeightedGraph.addEdge(13, 14, 75);

        std::cout << "Undirected weighted graph - Isolated vertices: ";
        for (const auto &vertex : undirectedWeightedGraph.getIsolated())
        {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;

    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
