
#include "../include/GraphMatrix.hpp"
#include <iostream>
int main() {
  // Here, we assume you are using:
  // GraphMatrix<VertexType, EdgeType, Direction>
  // Let's pick: GraphMatrix<std::string, int, UndirectedG> for this demo.
  Appledore::GraphMatrix<std::string, int, Appledore::UndirectedG> graph;

  graph.addVertex("A", "B", "C", "D");

  // 2. Add edges
  // (For an undirected graph, an edge from A to B also implies an edge from B
  // to A.)
  graph.addEdge("A", "B", 1);
  graph.addEdge("B", "C", 2);
  graph.addEdge("C", "D", 3);
  graph.addEdge("A", "D", 4);

  // 3. Display the initial vertices
  std::cout << "Initial Vertices:\n";
  for (const auto &v : graph.getVertices()) {
    std::cout << v << " ";
  }
  std::cout << "\n\n";

  // 4. Display the initial edges
  std::cout << "Initial Edges (Undirected):\n";
  auto edges = graph.getAllEdges();
  for (const auto &edge : edges) {
    auto &[src, dest, val] = edge;
    std::cout << src << " --(" << val << ")--> " << dest << "\n";
  }
  std::cout << "\n";

  // 5. Remove a vertex (say "C")
  std::cout << "Removing vertex: C\n\n";
  try {
    graph.removeVertex("C");
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
  }

  // 6. Display the updated vertices
  std::cout << "Updated Vertices:\n";
  for (const auto &v : graph.getVertices()) {
    std::cout << v << " ";
  }
  std::cout << "\n\n";

  // 7. Display the updated edges
  std::cout << "Updated Edges (Undirected):\n";
  edges = graph.getAllEdges();
  for (const auto &edge : edges) {
    auto &[src, dest, val] = edge;
    std::cout << src << " --(" << val << ")--> " << dest << "\n";
  }
  std::cout << "\n";

  // 8. Try checking edges involving removed vertex "C"
  std::cout << "Attempting to check edge from removed vertex C:\n";
  try {
    // Should throw an exception since "C" no longer exists
    bool edgeExists = graph.hasEdge("C", "D");
    std::cout << "Unexpected: 'C' to 'D' edge found? "
              << (edgeExists ? "Yes" : "No") << "\n";
  } catch (const std::exception &e) {
    std::cerr << "Expected error: " << e.what() << "\n";
  }

  return 0;
}
