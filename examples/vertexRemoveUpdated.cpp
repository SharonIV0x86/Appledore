#include <iostream>
#include "../include/GraphMatrix.h"

using namespace Appledore;

// TestVertex class for custom vertex representation
struct TestVertex : public GraphVertex
{
    std::string name;

    TestVertex(const std::string &name) : name(name) {}

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
    // Bidirectional Weighted Graph (Custom Example)
    GraphMatrix<TestVertex, Weight, UndirectedG> bidirectionalWeightedGraph;
    TestVertex X("X"), Y("Y"), Z("Z"), W("W"), V("V"), S("S"), U("U");

    bidirectionalWeightedGraph.addVertex(X, Y, Z, W, V, S, U);

    bidirectionalWeightedGraph.addEdge(X, Y, Weight(12));
    bidirectionalWeightedGraph.addEdge(X, V, Weight(40));
    bidirectionalWeightedGraph.addEdge(Y, Z, Weight(18));
    bidirectionalWeightedGraph.addEdge(Z, W, Weight(25));
    bidirectionalWeightedGraph.addEdge(W, V, Weight(30));
    bidirectionalWeightedGraph.addEdge(W, S, Weight(29));
    bidirectionalWeightedGraph.addEdge(U, X, Weight(20));
    bidirectionalWeightedGraph.addEdge(U, S, Weight(12));
    bidirectionalWeightedGraph.addEdge(V, U, Weight(15));
    bidirectionalWeightedGraph.addEdge(V, Y, Weight(20));

    // Remove edge V-Y
   

  

    std::cout << "\nBidirectional Weighted Graph - Edges before removing edge V-Y:\n";
    for (const auto &[src, dest, edge] : bidirectionalWeightedGraph.getAllEdges())
    {
        std::cout << src << " <-> " << dest << " : " << edge << "\n";
    }
  bidirectionalWeightedGraph.removeVertex(V);
 std::cout << "\nBidirectional Weighted Graph - Edges after removing edge V-Y:\n";
    for (const auto &[src, dest, edge] : bidirectionalWeightedGraph.getAllEdges())
    {
        std::cout << src << " <-> " << dest << " : " << edge << "\n";
    }
  
    return 0;
}
