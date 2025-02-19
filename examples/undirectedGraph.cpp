#include "../include/GraphMatrix.hpp"
#include <iostream>

using namespace Appledore;

class Airport : public GraphVertex {
public:
  std::string name;

  Airport(const std::string &name) : name(name) {}

  // overloads to format the output, optional
  friend std::ostream &operator<<(std::ostream &os, const Airport &airport) {
    os << airport.name;
    return os;
  }
};

class Flight : public GraphEdge {
public:
  int distance;

  Flight(int dis) : distance(dis) {}

  // overloads to format the output, optional
  friend std::ostream &operator<<(std::ostream &os, const Flight &flight) {
    os << flight.distance << " miles";
    return os;
  }
};

int main() {
  // Create an undirected graph
  GraphMatrix<Airport, Flight, UndirectedG> GraphAirports;

  // Define airports
  Airport LAX("Los Angeles Intl.");
  Airport JFK("John F. Kennedy");
  Airport DEN("Denver Intl.");
  Airport ATL("Atlanta Intl.");

  // Define flights
  Flight flight1(862);
  Flight flight2(1945);
  Flight flight3(1199);
  Flight flight4(1631);

  // Add vertices to the graph
  GraphAirports.addVertex(LAX, JFK, DEN, ATL);

  // Add edges (flights) between airports
  GraphAirports.addEdge(LAX, DEN, flight1);
  GraphAirports.addEdge(LAX, ATL, flight2);
  GraphAirports.addEdge(ATL, DEN, flight3);
  GraphAirports.addEdge(DEN, JFK, flight4);

  // Display all vertices
  std::cout << "Airports in the graph:\n";
  for (const auto &vertex : GraphAirports.getVertices()) {
    std::cout << "- " << vertex << "\n";
  }

  // Display all edges
  std::cout << "\nFlights in the graph:\n";
  for (const auto &[src, dest, edge] : GraphAirports.getAllEdges()) {
    std::cout << src << " <-> " << dest << " : " << edge << "\n";
  }

  // Check and display specific flights
  std::cout << "\nChecking flights:\n";

  std::cout << "- From " << LAX << " to " << DEN << ": ";
  if (GraphAirports(LAX, DEN)) {
    const Flight edge = GraphAirports.getEdge(LAX, DEN);
    std::cout << "Yes, distance: " << edge << "\n";
  } else {
    std::cout << "No direct flight available.\n";
  }

  std::cout << "- From " << ATL << " to " << LAX << ": ";
  if (GraphAirports(ATL, LAX)) {
    const Flight edge = GraphAirports.getEdge(ATL, LAX);
    std::cout << "Yes, distance: " << edge << "\n";
  } else {
    std::cout << "No direct flight available.\n";
  }

  std::cout << "- From " << JFK << " to " << LAX << ": ";
  if (GraphAirports(JFK, LAX)) {
    const Flight edge = GraphAirports.getEdge(JFK, LAX);
    std::cout << "Yes, distance: " << edge << "\n";
  } else {
    std::cout << "No direct flight available.\n";
  }

  // Remove a flight and check again
  std::cout << "\nRemoving flight from " << ATL << " to " << LAX << "...\n";
  GraphAirports.removeEdge(ATL, LAX);

  std::cout << "After removal, checking flight from " << ATL << " to " << LAX
            << ": ";
  if (!GraphAirports(ATL, LAX)) {
    std::cout << "No direct flight available.\n";
  }

  std::cout << "NO. of flights starting from " << LAX << " : "
            << GraphAirports.outdegree(LAX)
            << "\n"; // Will give out error warnings as Undirected Graphs don't
                     // have Indegree or Outdegree.
  std::cout << "NO. of flights ending at " << LAX << " : "
            << GraphAirports.indegree(LAX)
            << "\n"; // Gives out total degree instead

  return 0;
}
