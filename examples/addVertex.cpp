#include "../include/MixedGraph.hpp" // Ensure this is the correct path to the MixedGraphMatrix header
#include <iostream>
#include <string>
#include <exception>

// Example vertex type
struct Vertex {
    std::string name;

    bool operator<(const Vertex &other) const { return name < other.name; }
    bool operator==(const Vertex &other) const { return name == other.name; }
    friend std::ostream &operator<<(std::ostream &os, const Vertex &v) {
        return os << v.name;
    }
};

int main() {
    try {
        // Directed and unweighted graph
        Appledore::MixedGraphMatrix<Vertex> directedUnweightedGraph;

        Vertex A{"A"}, B{"B"}, C{"C"};

        // Test: Adding multiple vertices
        std::cout << "Adding vertices A, B, C to directed unweighted graph." << std::endl;
        directedUnweightedGraph.addVertex(A, B, C);

        // Test: Adding duplicate vertex
        std::cout << "Attempting to add duplicate vertex A." << std::endl;
        directedUnweightedGraph.addVertex(A);

        // Print vertices
        std::cout << "Vertices in directed unweighted graph: ";
        for (const auto &v : directedUnweightedGraph.getVertices()) {
            std::cout << v << " ";
        }
        std::cout << "\n";

        // Undirected and weighted graph
        Appledore::MixedGraphMatrix<Vertex, int> undirectedWeightedGraph;

        Vertex D{"D"}, E{"E"}, InvalidVertex{""};

        // Test: Adding valid and invalid vertices
        std::cout << "Adding vertices D, E, and InvalidVertex to undirected weighted graph." << std::endl;
        try {
            undirectedWeightedGraph.addVertex(D, E, InvalidVertex);
        } catch (const std::invalid_argument &e) {
            std::cout << "Caught exception: " << e.what() << "\n";
        }

        // Print vertices
        std::cout << "Vertices in undirected weighted graph: ";
        for (const auto &v : undirectedWeightedGraph.getVertices()) {
            std::cout << v << " ";
        }
        std::cout << "\n";

        // Test: Adjacency matrix resizing and integrity
        std::cout << "Adding vertex F to undirected weighted graph." << std::endl;
        Vertex F{"F"};
        undirectedWeightedGraph.addVertex(F);

        // Verify adjacency matrix size indirectly by adding an edge
        std::cout << "Adding edge between D and E with weight 5." << std::endl;
        undirectedWeightedGraph.addEdge(D, E, 5);
        std::cout << "Edge value between D and E: "
                  << undirectedWeightedGraph.getEdgeValue(D, E) << "\n";
    } catch (const std::exception &ex) {
        std::cerr << "Exception caught: " << ex.what() << std::endl;
    }

    return 0;
}