#include <iostream>
#include "../include/MixedGraph.h"

using namespace Appledore;

int main() {
    MixedGraphMatrix<std::string, int> graph;

    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");

    graph.addEdge("A", "B", true); 
    graph.addEdge("B", "C");     

    std::cout << "In-degree of B: " << graph.indegree("B") << std::endl;
    std::cout << "Out-degree of B: " << graph.outdegree("B") << std::endl;
    std::cout << "Total degree of B: " << graph.totalDegree("B") << std::endl;

    return 0;
}
