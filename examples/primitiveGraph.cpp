#include <iostream>
#include <string>
#include "../include/MixedGraph.hpp"
using namespace Appledore;

int main()
{
    // Create a graph with 4 vertices (0, 1, 2, 3)
    MixedGraphMatrix<int, std::string> Graph;

    Graph.addVertex(0);
    Graph.addVertex(1);
    Graph.addVertex(2);
    Graph.addVertex(3);

    // passting raw literal wont work with std::optional so if for a literal edge type
    // you need to pass it casted as a string.
    Graph.addEdge(0, 1, std::string("Edge 0 - 1")); 
    Graph.addEdge(0, 2, std::string("Edge 0 - 2"), true);
    Graph.addEdge(1, 2, std::string("Edge 1 - 2"));
    Graph.addEdge(1, 3, std::string("Edge 1 - 3"), true);

    std::vector<std::string> edges = Graph.getEdges();
    std::cout << "Edges in the graph:" << std::endl;
    for (const auto &edge : edges)
    {
        std::cout << edge << std::endl;
    }

    // removing an edge.
    Graph.removeEdge(1, 2);
    edges = Graph.getEdges();
    std::cout << "Edges in the graph after removing an edge:" << std::endl;
    for (const auto &edge : edges)
    {
        std::cout << edge << std::endl;
    }

    return 0;
}
