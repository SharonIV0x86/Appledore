#include "../include/GraphMatrix.h"
#include <iostream>

int main() {
    try {
        // Create a weighted graph with 4 vertices
        GraphMatrix graph(4, true);

        // Add some edges
        graph.addEdge(0, 1, 10);
        graph.addEdge(1, 2, 20);
        graph.addEdge(2, 3, 30);

        std::cout << "Original graph:\n";
        graph.display();

        // Update an edge
        std::cout << "\nUpdating edge (1, 2) to weight 50.\n";
        graph.updateEdge(1, 2, 50);

        std::cout << "Updated graph:\n";
        graph.display();

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
    }

    return 0;
}
