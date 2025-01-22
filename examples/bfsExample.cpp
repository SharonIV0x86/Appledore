#include <iostream>
#include "../include/GraphMatrix.hpp"

class Vertex : public Appledore::GraphVertex {
    public:
        int data;
        Vertex(int d): data(d) {};
};

int main() {

    // In order to use bfs, EdgeType must support the operator+ and must have
    // infinity.
    Appledore::GraphMatrix<Vertex, double, Appledore::UndirectedG> undirected;

    Vertex v1(4);
    Vertex v2(10);
    Vertex v3(12);
    Vertex v4(2);

    undirected.addVertex(v1);
    undirected.addVertex(v2);
    undirected.addVertex(v3);
    undirected.addVertex(v4);

    undirected.addEdge(v1,v2,1);
    undirected.addEdge(v2,v3,1);
    undirected.addEdge(v1,v4,1);

    std::vector<double> dist = undirected.bfs(2, 10);

    for (int item : dist) {
        std::cout << item << " ";
    }
    std::cout << "\n";
    return 0;
}