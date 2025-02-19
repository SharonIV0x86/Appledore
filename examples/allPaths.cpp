#include "../include/GraphMatrix.hpp"
#include <iostream>
#include <stack>

using namespace Appledore;

class Airport : public GraphVertex {
public:
  std::string name;

  Airport(std::string name) : name(std::move(name)) {}

  friend std::ostream &operator<<(std::ostream &os, const Airport &airport) {
    os << airport.name;
    return os;
  }
};

class Flight : public GraphEdge {
public:
  int distance;

  Flight(int dis) : distance(dis) {}

  friend std::ostream &operator<<(std::ostream &os, const Flight &flight) {
    os << flight.distance << " miles";
    return os;
  }
};

int main() {
  GraphMatrix<Airport, Flight, DirectedG> AirportsGraph;

  Airport LAX("Los Angeles Intl.");
  Airport JFK("John F. Kennedy");
  Airport DEN("Denver Intl.");
  Airport ATL("Atlanta Intl.");
  Airport ORD("Chicago O'Hare");
  Airport SFO("San Francisco Intl.");
  Airport MIA("Miami Intl.");
  Airport SEA("Seattle Tacoma Intl.");

  Flight flight1(761);
  Flight flight2(1945);
  Flight flight3(1199);
  Flight flight4(1631);
  Flight flight5(2475);
  Flight flight6(1843);
  Flight flight7(2333);
  Flight flight8(1723);
  Flight flight9(2149);
  Flight flight10(2171);

  // Add vertices (airports)
  AirportsGraph.addVertex(LAX, JFK, DEN, ATL, ORD, SFO, MIA, SEA);

  // Add edges (flights)
  AirportsGraph.addEdge(LAX, ATL, flight2);
  AirportsGraph.addEdge(LAX, JFK, flight5);
  AirportsGraph.addEdge(JFK, ATL, flight1);
  AirportsGraph.addEdge(JFK, DEN, flight4);
  AirportsGraph.addEdge(DEN, ATL, flight3);
  AirportsGraph.addEdge(LAX, SFO, flight6);
  AirportsGraph.addEdge(SFO, SEA, flight7);
  AirportsGraph.addEdge(SEA, ORD, flight8);
  AirportsGraph.addEdge(ORD, MIA, flight9);
  AirportsGraph.addEdge(MIA, ATL, flight10);

  // Display vertices
  std::cout << "Airports in the graph:\n";
  for (const auto &vertex : AirportsGraph.getVertices()) {
    std::cout << vertex << "\n";
  }

  std::cout << "\nEdges in the graph:\n";

  // Display all edges
  for (const auto &[src, dest, edge] : AirportsGraph.getAllEdges()) {
    std::cout << src << " -> " << dest << " : " << edge << "\n";
  }

  // Example usage of findAllPaths
  std::cout << "\nFinding all paths from LAX to ATL without any Path Limit:\n";
  auto paths = AirportsGraph.findAllPaths(LAX, ATL);
  for (const auto &path : paths) {
    for (const auto &vertex : path) {
      std::cout << vertex << " -> ";
    }
    std::cout << "END\n";
  }

  // ---------------------------------------------------------
  // NEW BLOCK
  // Example usage of findAllPaths with a path limit
  // ---------------------------------------------------------
  size_t pathLimit = 2; // Example of a path limit
  std::cout << "\nFinding at most " << pathLimit << " paths from LAX to ATL:\n";
  try {
    auto limitedPaths = AirportsGraph.findAllPaths(LAX, ATL, pathLimit);
    for (const auto &path : limitedPaths) {
      for (const auto &vertex : path) {
        std::cout << vertex << " -> ";
      }
      std::cout << "END\n";
    }
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
  }

  // Example of exceeding path limit
  size_t excessiveLimit = 10; // Example of exceeding path limit
  std::cout << "\nAttempting to find " << excessiveLimit
            << " paths from LAX to ATL:\n";
  try {
    auto excessivePaths = AirportsGraph.findAllPaths(LAX, ATL, excessiveLimit);
    for (const auto &path : excessivePaths) {
      for (const auto &vertex : path) {
        std::cout << vertex << " -> ";
      }
      std::cout << "END\n";
    }
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
  }

  return 0;
}
