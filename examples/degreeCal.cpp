#include "../include/MixedGraph.hpp"
#include <iostream>
#include <string>

int main() {
  Appledore::MixedGraphMatrix<std::string> graph;

  graph.addVertex("A");
  graph.addVertex("B");
  graph.addVertex("C");

  graph.addEdge("A", "B", std::nullopt, true); // Directed edge A -> B
  graph.addEdge("B", "C", std::nullopt);       // Undirected edge B <-> C

  std::cout << "Vertices: ";
  for (const auto &vertex : graph.getVertices()) {
    std::cout << vertex << " ";
  }
  std::cout << std::endl;

  std::cout << "In-degree of B: " << graph.indegree("B")
            << std::endl; // Should be 1
  std::cout << "Out-degree of B: " << graph.outdegree("B")
            << std::endl; // Should be 2
  std::cout << "Total degree of B: " << graph.totalDegree("B")
            << std::endl; // Should be 3

  return 0;
}
