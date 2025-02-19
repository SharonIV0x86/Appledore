#include "../include/GraphMatrix.hpp"
#include <iostream>

using namespace Appledore;

class TestVertex : public GraphVertex {
public:
  std::string name;

  TestVertex(std::string n = "") : name(std::move(n)) {}

  friend std::ostream &operator<<(std::ostream &os, const TestVertex &v) {
    os << "Vertex " << v.name;
    return os;
  }
};

class Weight : public GraphEdge {
public:
  int value;
  Weight(int v = 1) : value(v) {}

  friend std::ostream &operator<<(std::ostream &os, const Weight &w) {
    os << w.value;
    return os;
  }
};

void printGraphConnectivity(const auto &graph, const std::string &description) {
  std::cout << "\nTesting " << description << "\n";
  std::cout << "Is the graph connected? "
            << (graph.isConnected() ? "Yes" : "No") << "\n";
}

int main() {
  GraphMatrix<TestVertex, Weight, UndirectedG> graph1;

  TestVertex v1("A"), v2("B"), v3("C"), v4("D"), v5("E");
  graph1.addVertex(v1, v2, v3, v4, v5);

  graph1.addEdge(v1, v2, Weight(5));
  graph1.addEdge(v2, v3, Weight(3));
  graph1.addEdge(v3, v4, Weight(4));
  graph1.addEdge(v4, v5, Weight(2));
  graph1.addEdge(v5, v1, Weight(6));

  printGraphConnectivity(graph1, "Graph 1: Connected");

  graph1.removeEdge(v1, v5);
  printGraphConnectivity(graph1, "Graph 1: After removing edge A-E");

  graph1.removeVertex(v5);
  printGraphConnectivity(graph1, "Graph 1: After removing vertex E");

  GraphMatrix<TestVertex, Weight, UndirectedG> graph2;

  TestVertex v6("F"), v7("G"), v8("H"), v9("I"), v10("J");
  graph2.addVertex(v6, v7, v8, v9, v10);

  graph2.addEdge(v6, v7, Weight(1));
  graph2.addEdge(v8, v9, Weight(2));

  printGraphConnectivity(graph2, "Graph 2: Disconnected");

  graph2.addEdge(v7, v8, Weight(3));
  printGraphConnectivity(graph2, "Graph 2: After connecting components");

  GraphMatrix<TestVertex, Weight, DirectedG> graph3;

  TestVertex v11("K"), v12("L"), v13("M"), v14("N");
  graph3.addVertex(v11, v12, v13, v14);

  graph3.addEdge(v11, v12, Weight(1));
  graph3.addEdge(v12, v13, Weight(2));

  printGraphConnectivity(graph3, "Graph 3: Directed");

  graph3.addEdge(v13, v11, Weight(3));
  printGraphConnectivity(graph3, "Graph 3: After adding reverse edge M-K");

  return 0;
}
