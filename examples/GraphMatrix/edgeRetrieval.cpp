#include <iostream>
#include "../../include/GraphMatrix.hpp"

using namespace Appledore;

class TestVertex : public GraphVertex
{
public:
    int id;

    explicit TestVertex(const int id = 0) : id(id) {}

    friend std::ostream &operator<<(std::ostream &os, const TestVertex &v)
    {
        os << "Vertex " << v.id;
        return os;
    }
};

void printEdges(const auto &edges, const std::string &description)
{
    std::cout << description << "\n";
    for (const auto &edge : edges)
    {
        std::cout << "Edge from " << std::get<0>(edge)
                  << " to " << std::get<1>(edge)
                  << " with weight " << std::get<2>(edge) << "\n";
    }
    std::cout << '\n';
}

int main()
{
    try
    {
        // Case 1: Default behavior (no sorting for arithmetic types)
        GraphMatrix<TestVertex, int, UndirectedG> graph1;
        TestVertex v1(1), v2(2), v3(3);
        graph1.addVertex(v1, v2, v3);

        graph1.addEdge(v1, v2, 10);
        graph1.addEdge(v2, v3, 20);
        graph1.addEdge(v3, v1, 30);

        std::vector<std::tuple<TestVertex, TestVertex, int>> edges1 = graph1.getAllEdges();
        printEdges(edges1, "Case 1: Default Behavior (No Sorting)");

        // Case 2: Automatically sort edges in ascending order
        std::vector<std::tuple<TestVertex, TestVertex, int>> edges2 = graph1.getAllEdges(true);
        printEdges(edges2, "Case 2: Automatically Sorted (Ascending Order)");

        // Case 3: Automatically sort edges in descending order
        std::vector<std::tuple<TestVertex, TestVertex, int>> edges3 = graph1.getAllEdges(false);
        printEdges(edges3, "Case 3: Automatically Sorted (Descending Order)");

        // Case 4: Custom sorting logic
        GraphMatrix<TestVertex, float, UndirectedG> graph2;
        TestVertex v4(4), v5(5), v6(6);
        graph2.addVertex(v4, v5, v6);

        graph2.addEdge(v4, v5, 0.123f);
        graph2.addEdge(v5, v6, 0.1f);
        graph2.addEdge(v6, v4, 0.21f);

        std::vector<std::tuple<TestVertex, TestVertex, float>> edges4 = graph2.getAllEdges(
            std::nullopt,
            [](const auto &a, const auto &b)
            {
                return std::get<2>(a) > std::get<2>(b); // Custom: Sort by weight in descending order
            });

        printEdges(edges4, "Case 4: Custom Sorting Logic");
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}
