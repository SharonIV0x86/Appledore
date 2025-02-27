#include <iostream>
#include <string>
#include "../../include/MixedGraph.hpp"

// Custom edge type for flight details
class FlightRoute
{
public:
    int duration;
    std::string airline;

    FlightRoute(int duration = 0, const std::string &airline = "") : duration(duration), airline(airline) {}

    bool operator==(const FlightRoute &other) const
    {
        return duration == other.duration && airline == other.airline;
    }

    friend std::ostream &operator<<(std::ostream &os, const FlightRoute &route)
    {
        os << "{ Duration: " << route.duration << " mins, Airline: \"" << route.airline << "\" }";
        return os;
    }
};

int main()
{
    // Create a graph to represent flight routes
    Appledore::MixedGraphMatrix<std::string, FlightRoute> flightGraph;

    // Add cities as vertices
    flightGraph.addVertex("New York");
    flightGraph.addVertex("London");
    flightGraph.addVertex("Paris");
    flightGraph.addVertex("Tokyo");

    FlightRoute route1{415, "British Airways"};
    FlightRoute route2{90, "Air France"};
    FlightRoute route3{720, "ANA"};

    // Add flight routes (edges) with details
    flightGraph.addEdge("New York", "London", route1, true); // Directed route
    flightGraph.addEdge("London", "Paris", route2, false);   // Undirected route
    flightGraph.addEdge("Paris", "Tokyo", route3, true);     // Directed route

    std::cout << "Cities in the flight graph: ";
    for (const auto &city : flightGraph.getVertices())
    {
        std::cout << city << ", ";
    }
    std::cout << "\n";

    std::cout << "Is there a direct flight from New York to London? ";
    if (flightGraph("New York", "London"))
    {
        std::cout << "Yes\n";
    }
    std::cout << "Is there a direct flight from London to New York? ";
    if (flightGraph("London", "New York"))
    {
        std::cout << "Yes\n";
    }
    FlightRoute route = flightGraph.getEdgeValue("London", "Paris");
    std::cout << "Flight route from London to Paris: " << route << "\n";

    // Check for a non-existent route
    // flightGraph.getEdgeValue("Paris", "New York"); //throws error, handle carefully

    return 0;
}
