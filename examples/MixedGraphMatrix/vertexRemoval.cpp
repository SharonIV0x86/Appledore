#include <iostream>
#include "../../include/MixedGraph.hpp"  

using namespace Appledore;


class City
{
public:
    std::string name;

    City(const std::string &name) : name(name) {}

    // Overload to format output, optional
    friend std::ostream &operator<<(std::ostream &os, const City &city)
    {
        os << city.name;
        return os;
    }
    friend bool operator<(const City& l, const City& r){
        return l.name < r.name;
    }
};


class Road
{
public:
    int distance;

    Road(int dist) : distance(dist) {}

    // Overload to format output, optional
    friend std::ostream &operator<<(std::ostream &os, const Road &road)
    {
        os << road.distance << " miles";
        return os;
    }
};

int main()
{
    try
    {
        MixedGraphMatrix<City, int> cityGraph;

        // Define some cities
        City nyc("New York");
        City la("Los Angeles");
        City chi("Chicago");
        City sf("San Francisco");

        // Add vertices
        cityGraph.addVertex(nyc);
        cityGraph.addVertex(la);
        cityGraph.addVertex(chi);
        cityGraph.addVertex(sf);

        // Add edges (if using MixedGraphMatrix with int as EdgeType, pass integers)
        // For demonstration, assume all roads are undirected and set distances
        cityGraph.addEdge(nyc, la, 2800 /* miles */, false);
        cityGraph.addEdge(nyc, chi, 790, false);
        cityGraph.addEdge(la, sf, 383, false);
        cityGraph.addEdge(chi, sf, 2130, false);

        // Display current vertices
        std::cout << "Cities in the graph:\n";
        for (auto &vertex : cityGraph.getVertices())
        {
            std::cout << "- " << vertex.name << "\n";
        }

        // Display current edges (if using MixedGraphMatrix<int>)
        // We'll just show they exist by checking them
        std::cout << "\nRoad distances in the graph:\n";
        for (auto &src : cityGraph.getVertices())
        {
            for (auto &dest : cityGraph.getVertices())
            {
                if (cityGraph.hasEdge(src, dest))
                {
                    std::cout << src.name << " <-> " << dest.name
                              << " : " << cityGraph.getEdgeValue(src, dest) << " miles\n";
                }
            }
        }

        // Remove a vertex
        std::cout << "\nRemoving the city: " << chi.name << "...\n";
        cityGraph.removeVertex(chi);

        // Display vertices after removal
        std::cout << "\nCities in the graph after removal:\n";
        for (auto &vertex : cityGraph.getVertices())
        {
            std::cout << "- " << vertex.name << "\n";
        }

        // Display edges after removal
        std::cout << "\nRoad distances in the graph after removing " << chi.name << ":\n";
        for (auto &src : cityGraph.getVertices())
        {
            for (auto &dest : cityGraph.getVertices())
            {
                if (cityGraph.hasEdge(src, dest))
                {
                    std::cout << src.name << " <-> " << dest.name
                              << " : " << cityGraph.getEdgeValue(src, dest) << " miles\n";
                }
            }
        }
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}