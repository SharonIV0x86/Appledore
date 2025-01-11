#include <iostream>
#include "../include/GraphMatrix.h"

using namespace Appledore;

class TestVertex : public GraphVertex
{
public:
    std::string name;

    TestVertex(std::string n = "") : name(std::move(n)) {}

    friend std::ostream& operator<<(std::ostream& os, const TestVertex& v) {
        os << "Vertex " << v.name;
        return os;
    }
};

class Weight
{
public:
    int value;
    Weight(int v = 1) : value(v) {}  // Default constructor with value 1

    friend std::ostream& operator<<(std::ostream& os, const Weight& w) {
        os << w.value;
        return os;
    }
};

void printGraphConnectivity(const auto& graph, const std::string& description) {
    std::cout << "\nTesting " << description << "\n";
    std::cout << "Is the graph connected? "
              << (graph.isConnected() ? "Yes" : "No") << "\n";
}

int main() {
    GraphMatrix<TestVertex, Weight, UndirectedG> connectedGraph;

    TestVertex v1("A"), v2("B"), v3("C"), v4("D");
    connectedGraph.addVertex(v1, v2, v3, v4);

    connectedGraph.addEdge(v1, v2, Weight());
    connectedGraph.addEdge(v2, v3, Weight());
    connectedGraph.addEdge(v3, v4, Weight());

    printGraphConnectivity(connectedGraph, "Graph 1");

    GraphMatrix<TestVertex, Weight, UndirectedG> disconnectedGraph;

    TestVertex v5("E"), v6("F"), v7("G"), v8("H");
    disconnectedGraph.addVertex(v5, v6, v7, v8);

    disconnectedGraph.addEdge(v5, v6, Weight());
    disconnectedGraph.addEdge(v7, v8, Weight());

    printGraphConnectivity(disconnectedGraph, "Graph 2");

    GraphMatrix<TestVertex, Weight, DirectedG> directedGraph;

    TestVertex v9("I"), v10("J"), v11("K");
    directedGraph.addVertex(v9, v10, v11);

    directedGraph.addEdge(v9, v10, Weight());
    directedGraph.addEdge(v10, v11, Weight());

    printGraphConnectivity(directedGraph, "Graph 3");

    return 0;
}