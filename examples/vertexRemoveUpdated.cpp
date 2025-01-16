// # Example of GraphMatrix Usage

// This file demonstrates the use of the GraphMatrix class with various graph configurations, including weighted directed graphs, unweighted undirected graphs, and vertex/edge management.

// cpp
#include <iostream>
#include "../include/GraphMatrix.h"

using namespace Appledore;

// TestVertex class for custom vertex representation
struct TestVertex
{
    std::string name;

    TestVertex(const std::string &name) : name(name) {}

    bool operator<(const TestVertex &other) const { return name < other.name; }
    bool operator==(const TestVertex &other) const { return name == other.name; }

    friend std::ostream &operator<<(std::ostream &os, const TestVertex &vertex)
    {
        return os << vertex.name;
    }
};

// Weight class for custom edge representation
struct Weight
{
    int value;

    Weight(int value = 0) : value(value) {}

    friend std::ostream &operator<<(std::ostream &os, const Weight &weight)
    {
        return os << weight.value;
    }
};

int main()
{
    // Undirected Weighted Graph
    GraphMatrix<TestVertex, Weight, UndirectedG> undirectedWeightedGraph;
    TestVertex A("A"), B("B"), C("C"), D("D"), E("E");

    undirectedWeightedGraph.addVertex(A, B, C, D, E);

    undirectedWeightedGraph.addEdge(A, B, Weight(10));
    undirectedWeightedGraph.addEdge(A, C, Weight(15));
    undirectedWeightedGraph.addEdge(B, D, Weight(20));
    undirectedWeightedGraph.addEdge(D, E, Weight(25));
    undirectedWeightedGraph.addEdge(C, E, Weight(30));

    std::cout << "\nUndirected Weighted Graph - Edges before removing vertex:\n";
    for (const auto &[src, dest, edge] : undirectedWeightedGraph.getAllEdges())
    {
        std::cout << src << " <-> " << dest << " : " << edge << "\n";
    }

    undirectedWeightedGraph.removeVertex(C);

    std::cout << "\nUndirected Weighted Graph - Edges after removing vertex C:\n";
    for (const auto &[src, dest, edge] : undirectedWeightedGraph.getAllEdges())
    {
        std::cout << src << " <-> " << dest << " : " << edge << "\n";
    }

    // Directed Weighted Graph
    GraphMatrix<TestVertex, Weight, DirectedG> directedWeightedGraph;
    directedWeightedGraph.addVertex(A, B, C, D, E);

    directedWeightedGraph.addEdge(A, B, Weight(5));
    directedWeightedGraph.addEdge(B, C, Weight(10));
    directedWeightedGraph.addEdge(C, D, Weight(15));
    directedWeightedGraph.addEdge(D, E, Weight(20));

    std::cout << "\nDirected Weighted Graph - Edges:\n";
    for (const auto &[src, dest, edge] : directedWeightedGraph.getAllEdges())
    {
        std::cout << src << " -> " << dest << " : " << edge << "\n";
    }

    directedWeightedGraph.removeVertex(C);

    std::cout << "\nUndirected Weighted Graph - Edges after removing vertex C:\n";
    for (const auto &[src, dest, edge] : directedWeightedGraph.getAllEdges())
    {
        std::cout << src << " <-> " << dest << " : " << edge << "\n";
    }
    // Unweighted Undirected Graph
    GraphMatrix<TestVertex, UnweightedG, UndirectedG> unweightedUndirectedGraph;
    unweightedUndirectedGraph.addVertex(A, B, C, D, E);

    unweightedUndirectedGraph.addEdge(A, B);
    unweightedUndirectedGraph.addEdge(A, C);
    unweightedUndirectedGraph.addEdge(B, D);
    unweightedUndirectedGraph.addEdge(D, E);

    std::cout << "\nUnweighted Undirected Graph - Edges:\n";
    for (const auto &[src, dest, edge] : unweightedUndirectedGraph.getAllEdges())
    {
        std::cout << src << " <-> " << dest << "\n";
    }

    unweightedUndirectedGraph.removeVertex(C);

    std::cout << "\nUndirected Weighted Graph - Edges after removing vertex C:\n";
    for (const auto &[src, dest, edge] : unweightedUndirectedGraph.getAllEdges())
    {
        std::cout << src << " <-> " << dest << "\n";
    }
    return 0;
}
// 