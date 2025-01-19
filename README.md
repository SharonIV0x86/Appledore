# Appledore
A simple and efficient graph library in modern C++ Supports directed/undirected graphs with customizable edge type and vertices, designed for performance and ease of use.

## Features
- Adjacency matrix-based representation.
- Adjacency list-based representation
- Supports custom vertex and edge types
- Efficient management of vertices and edges
- Easy querying of graph structure and properties
- Upcoming features: support for graph degrees, advanced graph algorithms (e.g., Dijkstra, BFS, DFS), and additional utilities for graph analysis.

## Installation
1. Clone the repository
```
 git clone https://github.com/SharonIV0X86/Appledore
```
2. Include the ``GraphMatrix`` header in your project
## Example Diragram 1
Code below implements the Graph relationship between Airports and Distances.
[Directed Graph Example](https://github.com/SharonIV0x86/Appledore/blob/main/examples/directedGraph.cpp)
![graph3](https://github.com/user-attachments/assets/8044b80a-c43a-4b92-856d-737ad4b9af20)
## Directed Weighted graph using Custom Structures/Classes
```cpp
#include <iostream>
#include "../include/GraphMatrix.hpp"

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

class Flight
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

    return 0;
}


```
## Example Diagram 2
Code below implements the Graph relationship between Airports and Distances.
[Undirected Graph Example](https://github.com/SharonIV0x86/Appledore/blob/main/examples/undirectedGraph.cpp)
![graph2](https://github.com/user-attachments/assets/ff6a64d1-47fe-4589-a4bd-2f6a1a15de2c)
## Undirected Weighted graph using Custom Structures/Classes
```cpp
#include <iostream>
#include "../include/GraphMatrix.hpp"
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

class Flight
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

    GraphMatrix<Airport, Flight, UndirectedG> AirportGraph;
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

    // // Add vertices to the graph
    AirportGraph.addVertex(LAX);
    AirportGraph.addVertex(JFK, DEN, ATL);

    // Add edges between airports
    AirportGraph.addEdge(LAX, DEN, flight1);
    AirportGraph.addEdge(LAX, ATL, flight2);
    AirportGraph.addEdge(ATL, DEN, flight3);
    AirportGraph.addEdge(DEN, JFK, flight4);

    std::cout << "\nCheck if there is a flight from " << LAX << " --> " << DEN << ":\n";
    if (AirportGraph(LAX, DEN))
    {
        const Flight edge = AirportGraph.getEdge(LAX, DEN);
        std::cout << "Yes, flight distance: " << edge << "\n";
    }
    else
    {
        std::cout << "No direct flight available.\n";
    }

    std::cout << "\nCheck if there is a flight from " << ATL << " --> " << LAX << ":\n";
    if (AirportGraph(ATL, LAX))
    {
        const Flight edge = AirportGraph.getEdge(ATL, LAX);
        std::cout << "Yes, flight distance: " << edge << "\n";
    }
    else
    {
        std::cout << "No direct flight available.\n";
    }

    std::cout << "\nCheck if there is a flight from " << JFK << " --> " << LAX << ":\n";
    if (AirportGraph(JFK, LAX))
    {
        const Flight edge = AirportGraph.getEdge(JFK, LAX);
        std::cout << "Yes, flight distance: " << edge << "\n";
    }
    else
    {
        try
        {
            const Flight edge = AirportGraph.getEdge(JFK, LAX);
            std::cout << "Yes, flight distance: " << edge << "\n";
        }
        catch (std::exception &e)
        {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    AirportGraph.removeEdge(ATL, LAX);
    if (!AirportGraph(ATL, LAX))
    {
        std::cout << "\nFlight Route from: " << ATL.name << " to " << LAX.name << " doesnt exist\n";
    }
    AirportGraph.iss();
    return 0;
}


```


## Example Diagram 3
Code below implements this Graph relationship between USA States and transport medium.
[Flight Routes Example](https://github.com/SharonIV0x86/Appledore/blob/main/examples/flightRoutes.cpp)
![Screenshot_20241205_124620-1](https://github.com/user-attachments/assets/1db263c6-1538-4b14-8b33-725bb68ebc06)
## MixedGraph Example using Custom Structures/Classes
Below is an example of how to use the library with custom vertex and edge types.

```cpp
#include <iostream>
#include <string>
#include "./include/MixedGraph.hpp"

// Vertex class representing a state in the USA
class State
{
public:
    std::string stateName;
    std::string capitalCity;
    int population;

    State(const std::string &name, const std::string &capital, int pop)
        : stateName(name), capitalCity(capital), population(pop) {}

    bool operator<(const State &other) const
    {
        return stateName < other.stateName;
    }
};

class Connection
{
public:
    int distance;
    std::string transportMode;

    Connection(){}
    Connection(int dist, const std::string &mode)
        : distance(dist), transportMode(mode) {}
};

int main()
{
    Appledore::MixedGraphMatrix<State, Connection> americaNetwork;

    // American States
    State california("California", "Sacramento", 39538223);
    State texas("Texas", "Austin", 29145505);
    State florida("Florida", "Tallahassee", 21538187);
    State newYork("New York", "Albany", 20201249);

    americaNetwork.addVertex(california);
    americaNetwork.addVertex(texas);
    americaNetwork.addVertex(florida);
    americaNetwork.addVertex(newYork);

    Connection roadConnection(1500, "Road");   // Distance: 1500 miles, Mode: Road
    Connection trainConnection(1300, "Train"); // Distance: 1300 miles, Mode: Train
    Connection airConnection(1000, "Air");     // Distance: 1000 miles, Mode: Air
    Connection waterConnection(400, "Water");  // Distance: 400 miles,  Mode: Water
    // Add edges (connections) between states
    americaNetwork.addEdge(california, texas, roadConnection, false);   // California <-> Texas (Road)
    americaNetwork.addEdge(florida, newYork, trainConnection, false);  // Florida <-> New York (Train)
    americaNetwork.addEdge(texas, florida, airConnection, true);       // Texas <-> Florida (Air)
    americaNetwork.addEdge(california, florida, waterConnection, true); // California -> Florida (water)
    // Print details of the states and connections
    std::cout << "American States and Connections:" << std::endl;
    std::vector<State> states = americaNetwork.getVertices();
    for (const State &st : states)
    {
        for (const State &st2 : states)
        {
            if (americaNetwork(st, st2))
            {
                Connection edgeValue = americaNetwork.getEdgeValue(st, st2);
                std::cout << "Edge Connection between " << st.stateName << " and " << st2.stateName << "\n";
                std::cout << "Distance: " << edgeValue.distance << "\n";
                std::cout << "Transport: " << edgeValue.transportMode << "\n";
            }
        }
    }

    return 0;
}

```
# Contributions
If you'd like to contribute anything, any new feature, work on required features or submit a bug fix make sure to read the [contributing](https://github.com/SharonIV0x86/Appledore/blob/main/CONTRIBUTING.md)
