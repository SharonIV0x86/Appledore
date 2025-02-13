#include <iostream>
#include "../include/MixedGraph.hpp"

// Helper function to print adjacency matrix
template <typename VertexType, typename EdgeType>
void printAdjacencyMatrix(const Appledore::MixedGraphMatrix<VertexType, EdgeType> &graph)
{
    size_t numVertices = graph.getNumVertices();
    const auto &vertices = graph.getVertices(); // Get vertices directly from the graph

    for (size_t i = 0; i < numVertices; ++i)
    {
        for (size_t j = 0; j < numVertices; ++j)
        {
            std::cout << (graph.hasEdge(vertices[i], vertices[j])
                              ? std::to_string(graph.getEdgeValue(vertices[i], vertices[j]))
                              : "0")
                      << " ";
        }
        std::cout << "\n";
    }
}

// Function to test the graph functionality
template <typename VertexType, typename EdgeType>
void testGraph(Appledore::MixedGraphMatrix<VertexType, EdgeType> &graph,
               const std::vector<VertexType> &vertices)
{
    std::cout << "Before adding vertices:\n";
    printAdjacencyMatrix(graph);
    std::cout << "Number of vertices: " << graph.getNumVertices() << "\n";

    // Add vertices
    for (const auto &vertex : vertices)
    {
        graph.addVertex(vertex);
    }

    std::cout << "After adding vertices:\n";
    printAdjacencyMatrix(graph);
    std::cout << "Number of vertices: " << graph.getNumVertices() << "\n";
}

int main()
{
    // Test cases for different graph types
    std::vector<int> directedVertices = {1, 2, 3};
    Appledore::MixedGraphMatrix<int, bool> directedGraph;
    testGraph(directedGraph, directedVertices);

    std::vector<int> weightedDirectedVertices = {4, 5, 6};
    Appledore::MixedGraphMatrix<int, double> weightedDirectedGraph;
    testGraph(weightedDirectedGraph, weightedDirectedVertices);

    std::vector<int> undirectedVertices = {7, 8, 9};
    Appledore::MixedGraphMatrix<int, bool> undirectedGraph;
    testGraph(undirectedGraph, undirectedVertices);

    std::vector<int> weightedUndirectedVertices = {10, 11, 12};
    Appledore::MixedGraphMatrix<int, double> weightedUndirectedGraph;
    testGraph(weightedUndirectedGraph, weightedUndirectedVertices);

    return 0;
}
