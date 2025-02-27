#include <iostream>
#include "../../include/MixedGraph.hpp"

int main()
{
    using namespace Appledore;

    // Create a graph with string vertices and integer edge weights
    MixedGraphMatrix<std::string, int> graph;

    // Add vertices to the graph
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addVertex("D");

    // Demonstrate all overloads of addEdge

    // Case 1: Add a directed, weighted edge (General case with optional value)
    graph.addEdge("A", "B", std::optional<int>(5), true);
    std::cout << "Added directed edge A -> B with weight 5\n";

    // Case 2: Add an undirected, weighted edge (General case with optional value)
    graph.addEdge("B", "C", std::optional<int>(10), false);
    std::cout << "Added undirected edge B <-> C with weight 10\n";

    // Case 3: Add a directed, non-weighted edge
    graph.addEdge("C", "D", true);
    std::cout << "Added directed edge C -> D (no weight)\n";

    // Case 4: Add an undirected, non-weighted edge
    graph.addEdge("A", "D", false);
    std::cout << "Added undirected edge A <-> D (no weight)\n";

    // Case 5: Add an undirected, weighted edge (simplified overload)
    graph.addEdge("D", "B", 15);
    std::cout << "Added undirected edge D <-> B with weight 15\n";

    // Case 6: Add a directed, weighted edge
    graph.addEdge("B", "A", 20, true);
    std::cout << "Added directed edge B -> A with weight 20\n";

    // Display the vertices
    std::cout << "\nVertices in the graph:\n";
    for (const auto &vertex : graph.getVertices())
    {
        std::cout << vertex << " ";
    }
    std::cout << "\n";

    // Display edges
    std::cout << "\nEdges in the graph:\n";
    for (const auto &edge : graph.getEdges())
    {
        std::cout << edge << " ";
    }
    std::cout << "\n";

    // Check for edges
    std::cout << "\nChecking for edges:\n";
    std::cout << "Edge A -> B exists? " << (graph.hasEdge("A", "B") ? "Yes" : "No") << "\n";
    std::cout << "Edge A -> C exists? " << (graph.hasEdge("A", "C") ? "Yes" : "No") << "\n";

    // Update an edge value
    std::cout << "\nUpdating edge weight of A -> B to 50\n";
    graph.updateEdge("A", "B", 50);

    // Remove an edge
    std::cout << "\nRemoving edge B <-> C\n";
    graph.removeEdge("B", "C");

    // Display updated edges
    std::cout << "\nUpdated edges in the graph:\n";
    for (const auto &edge : graph.getEdges())
    {
        std::cout << edge << " ";
    }
    std::cout << "\n";

    return 0;
}



