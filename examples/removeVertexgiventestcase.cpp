#include <iostream>
#include <string>
#include "../include/GraphMatrix.h"

using namespace Appledore;

// TestVertex class implementation
class TestVertex
{
public:
    std::string name;

    TestVertex(const std::string &name) : name(name) {}

    bool operator<(const TestVertex &other) const
    {
        return name < other.name;
    }

    bool operator==(const TestVertex &other) const
    {
        return name == other.name;
    }

    friend std::ostream &operator<<(std::ostream &os, const TestVertex &vertex)
    {
        os << vertex.name;
        return os;
    }
};

// Weight class implementation
class Weight
{
public:
    int value;

    Weight(int value = 0) : value(value) {}

    friend std::ostream &operator<<(std::ostream &os, const Weight &weight)
    {
        os << weight.value;
        return os;
    }
};

int main()
{
    try
    {
        GraphMatrix<TestVertex, Weight, UndirectedG> graph;
        TestVertex A("A"), B("B"), C("C"), D("D"), E("E");

        // Add vertices to the graph
        graph.addVertex(A);
        graph.addVertex(B);
        graph.addVertex(C);
        graph.addVertex(D);
        graph.addVertex(E);

        // Add edges to the graph
        graph.addEdge(A, B, Weight(10));
        graph.addEdge(A, C, Weight(20));
        graph.addEdge(B, D, Weight(30));
        graph.addEdge(D, E, Weight(40));
        graph.addEdge(C, E, Weight(50));

        // Display edges before removing a vertex
        std::cout << "Edges before: \n";
        for (const auto &[src, dest, edge] : graph.getAllEdges())
        {
            std::cout << src << " <-> " << dest << " : " << edge << "\n";
        }

        // Remove a vertex
        graph.removeVertex(C);

        // Display edges after removing a vertex
        std::cout << "Edges after: \n";
        for (const auto &[src, dest, edge] : graph.getAllEdges())
        {
            std::cout << src << " <-> " << dest << " : " << edge << "\n";
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}