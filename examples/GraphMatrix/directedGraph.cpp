#include <iostream>
#include "../../include/GraphMatrix.hpp"

using namespace Appledore;

class Airport : public GraphVertex
{
public:
    std::string name;

    Airport(std::string name) : name(name) {};

    friend std::ostream &operator<<(std::ostream &os, const Airport &airport)
    {
        os << airport.name;
        return os;
    }
};

class Flight : public GraphEdge
{
public:
    int distance;
    Flight(int dis) : distance(dis) {};

    friend std::ostream &operator<<(std::ostream &os, const Flight &flight)
    {
        os << flight.distance << " miles";
        return os;
    }
};

int main()
{
    GraphMatrix<Airport, Flight, DirectedG> AirportsGraph;

    // Define airports
    Airport LAX("Los Angeles Intl.");
    Airport JFK("John F. Kennedy");
    Airport DEN("Denver Intl.");
    Airport ATL("Atlanta Intl.");

    // Define flights
    Flight flight1(761);
    Flight flight2(1945);
    Flight flight3(1199);
    Flight flight4(1631);
    Flight flight5(2475);

    // Add vertices (airports)
    AirportsGraph.addVertex(LAX, JFK, DEN, ATL);

    // Add edges (flights)
    AirportsGraph.addEdge(LAX, ATL, flight2);
    AirportsGraph.addEdge(LAX, JFK, flight5);
    AirportsGraph.addEdge(JFK, ATL, flight1);
    AirportsGraph.addEdge(JFK, DEN, flight4);
    AirportsGraph.addEdge(DEN, ATL, flight3);

    // Display all vertices
    std::cout << "Airports in the graph:\n";
    for (const auto &vertex : AirportsGraph.getVertices())
    {
        std::cout << vertex << "\n";
    }

    std::cout << "\nEdges in the graph:\n";

    // Display all edges
    for (const auto &[src, dest, edge] : AirportsGraph.getAllEdges())
    {
        std::cout << src << " -> " << dest << " : " << edge << "\n";
    }

    // Check if specific edges exist
    std::cout << "\nChecking specific edges:\n";
    std::cout << "LAX to ATL: " << (AirportsGraph(LAX, ATL) ? "Exists" : "Does not exist") << "\n";
    std::cout << "JFK to DEN: " << (AirportsGraph(JFK, DEN) ? "Exists" : "Does not exist") << "\n";
    std::cout << "ATL to LAX: " << (AirportsGraph(ATL, LAX) ? "Exists" : "Does not exist") << "\n";

    // Remove an edge 
    std::cout << "\nRemoving edge JFK -> DEN...\n";
    AirportsGraph.removeEdge(JFK, DEN);

    std::cout << "\nUpdated edges in the graph:\n";
    for (const auto &[src, dest, edge] : AirportsGraph.getAllEdges())
    {
        std::cout << src << " -> " << dest << " : " << edge << "\n";
    }
    std::cout << "NO. of flights starting from " << LAX <<" : " << AirportsGraph.outdegree(LAX) << "\n";
    std::cout << "NO. of flights ending at " << LAX <<" : " << AirportsGraph.indegree(LAX) << "\n";
    std::cout << "Total flights to and from " << LAX <<" : " << AirportsGraph.totalDegree(LAX) << "\n";

    return 0;
}
