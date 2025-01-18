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
    // Undirected Weighted Graph (Data Center Connection Example)
    GraphMatrix<TestVertex, Latency, UndirectedG> dataCenterGraph;
    TestVertex DC1("Data Center 1"), DC2("Data Center 2"), DC3("Data Center 3"), DC4("Data Center 4"), DC5("Data Center 5"), DC6("Data Center 6"), DC7("Data Center 7");

    dataCenterGraph.addVertex(DC1, DC2, DC3, DC4, DC5, DC6, DC7);

    dataCenterGraph.addEdge(DC1, DC2, Latency(10));
    dataCenterGraph.addEdge(DC1, DC3, Latency(15));
    dataCenterGraph.addEdge(DC2, DC4, Latency(20));
    dataCenterGraph.addEdge(DC3, DC5, Latency(25));
    dataCenterGraph.addEdge(DC4, DC6, Latency(30));
    dataCenterGraph.addEdge(DC5, DC7, Latency(35));
    dataCenterGraph.addEdge(DC6, DC7, Latency(40));

    std::cout << "\nData Center Graph - Latencies before removing Data Center 3:\n";
    for (const auto &[src, dest, edge] : dataCenterGraph.getAllEdges())
    {
        std::cout << src << " <-> " << dest << " : " << edge << "\n";
    }

    dataCenterGraph.removeVertex(DC3);

    std::cout << "\nData Center Graph - Latencies after removing Data Center 3:\n";
    for (const auto &[src, dest, edge] : dataCenterGraph.getAllEdges())
    {
        std::cout << src << " <-> " << dest << " : " << edge << "\n";
    }

    // Directed Weighted Graph (Internet Routing Example)
    GraphMatrix<TestVertex, Latency, DirectedG> internetRoutingGraph;
    TestVertex R1("Router 1"), R2("Router 2"), R3("Router 3"), R4("Router 4"), R5("Router 5"), R6("Router 6"), R7("Router 7");

    internetRoutingGraph.addVertex(R1, R2, R3, R4, R5, R6, R7);

    internetRoutingGraph.addEdge(R1, R2, Latency(5));
    internetRoutingGraph.addEdge(R2, R3, Latency(10));
    internetRoutingGraph.addEdge(R3, R4, Latency(15));
    internetRoutingGraph.addEdge(R4, R5, Latency(20));
    internetRoutingGraph.addEdge(R5, R6, Latency(25));
    internetRoutingGraph.addEdge(R6, R7, Latency(30));
    internetRoutingGraph.addEdge(R7, R1, Latency(35));

    std::cout << "\nInternet Routing Graph - Latencies before removing Router 3:\n";
    for (const auto &[src, dest, edge] : internetRoutingGraph.getAllEdges())
    {
        std::cout << src << " -> " << dest << " : " << edge << "\n";
    }

    internetRoutingGraph.removeVertex(R3);

    std::cout << "\nInternet Routing Graph - Latencies after removing Router 3:\n";
    for (const auto &[src, dest, edge] : internetRoutingGraph.getAllEdges())
    {
        std::cout << src << " -> " << dest << " : " << edge << "\n";
    }

    return 0;
}
