#include <iostream>
#include "../include/GraphMatrix.h"

class ExtendedGraphMatrix : public GraphMatrix {
public:
    // Constructor that calls the base class constructor
    ExtendedGraphMatrix(int vertices, bool weighted) 
        : GraphMatrix(vertices, weighted) {}

    // Wrapper method for updateEdge to include additional logging
    void updateEdgeWithLogging(int fromVertex, int toVertex, int weight) {
        try {
            updateEdge(fromVertex, toVertex, weight);
            std::cout << "Edge updated: (" << fromVertex << ", " << toVertex << ") -> " << weight << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error updating edge: " << e.what() << std::endl;
        }
    }

    // Additional functionality, e.g., removing an edge
    void removeEdge(int fromVertex, int toVertex) {
        try {
            updateEdge(fromVertex, toVertex, 0); // Set weight to 0 to remove the edge
            std::cout << "Edge removed: (" << fromVertex << ", " << toVertex << ")" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error removing edge: " << e.what() << std::endl;
        }
    }
};

int main() {
    try {
        // Create an ExtendedGraphMatrix instance
        ExtendedGraphMatrix graph(5, true); // 5 vertices, weighted graph

        // Update edges using the derived class
        graph.updateEdgeWithLogging(0, 1, 15); // Add edge (0, 1) with weight 15
        graph.updateEdgeWithLogging(1, 3, 25); // Add edge (1, 3) with weight 25
        graph.updateEdgeWithLogging(3, 4, 35); // Add edge (3, 4) with weight 35

        // Display the adjacency matrix
        std::cout << "Adjacency Matrix after updates:" << std::endl;
        graph.display();

        // Remove an edge
        graph.removeEdge(1, 3); // Remove edge between vertices 1 and 3

        // Display the adjacency matrix again
        std::cout << "Adjacency Matrix after removing an edge:" << std::endl;
        graph.display();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
