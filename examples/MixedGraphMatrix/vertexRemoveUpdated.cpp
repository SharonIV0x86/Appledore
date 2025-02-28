#include <iostream>
#include "../../include/MixedGraph.hpp"

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

// Latency class for custom edge representation
struct Latency
{
    int milliseconds;

    Latency(int ms = 0) : milliseconds(ms) {}

    friend std::ostream &operator<<(std::ostream &os, const Latency &latency)
    {
        return os << latency.milliseconds << " ms";
    }
};

int main()
{
    // Mixed Graph Example (Data Center and Internet Routing)
    MixedGraphMatrix<TestVertex, Latency> mixedGraph;
    TestVertex DC1("Data Center 1"), DC2("Data Center 2"), DC3("Data Center 3"), R1("Router 1"), R2("Router 2"), R3("Router 3"), R4("Router 4");

    mixedGraph.addVertex(DC1);
    mixedGraph.addVertex(DC2);
    mixedGraph.addVertex(DC3);
    mixedGraph.addVertex(R1);
    mixedGraph.addVertex(R2);
    mixedGraph.addVertex(R3);
    mixedGraph.addVertex(R4);

    mixedGraph.addEdge(DC1, DC2, Latency(10), false);  // Undirected
    mixedGraph.addEdge(DC2, DC3, Latency(15), false);  // Undirected
    mixedGraph.addEdge(DC3, R1, Latency(20), true);    // Directed
    mixedGraph.addEdge(R1, R2, Latency(25), true);     // Directed
    mixedGraph.addEdge(R2, R3, Latency(30), true);     // Directed
    mixedGraph.addEdge(R3, R4, Latency(35), true);     // Directed
    mixedGraph.addEdge(R4, DC1, Latency(40), true);    // Directed

    std::cout << "\nMixed Graph - Latencies before removing Data Center 3:\n";
    for (const auto &vertex : mixedGraph.getVertices())
    {
        for (const auto &dest : mixedGraph.getVertices())
        {
            if (mixedGraph.hasEdge(vertex, dest))
            {
                std::cout << vertex << " -> " << dest << " : " << mixedGraph.getEdgeValue(vertex, dest) << "\n";
            }
        }
    }

    mixedGraph.removeVertex(DC3);

    std::cout << "\nMixed Graph - Latencies after removing Data Center 3:\n";
    for (const auto &vertex : mixedGraph.getVertices())
    {
        for (const auto &dest : mixedGraph.getVertices())
        {
            if (mixedGraph.hasEdge(vertex, dest))
            {
                std::cout << vertex << " -> " << dest << " : " << mixedGraph.getEdgeValue(vertex, dest) << "\n";
            }
        }
    }

    return 0;
}
