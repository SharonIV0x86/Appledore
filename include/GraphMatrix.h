#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>
#include <optional>
#include <map>
#include <stack>
#include <algorithm>
#include <set>

namespace Appledore
{
    // Tag structures
    struct DirectedG
    {
    };
    struct UndirectedG
    {
    };
    struct UnweightedG
    {
    };
    class GraphVertex
    {
    public:
        size_t id;

        static size_t nextId;

        GraphVertex()
        {
            id = nextId++;
        }
        bool operator<(const GraphVertex &other) const
        {
            return id < other.id;
        }
    };
    size_t Appledore::GraphVertex::nextId = 1;
    template <typename EdgeType>
    struct EdgeInfo
    {
        EdgeType value;

        EdgeInfo(const EdgeType &value) : value(value) {}
    };

    // GraphMatrix class template
    template <typename VertexType, typename EdgeType, typename Direction>
    class GraphMatrix
    {
    public:
        GraphMatrix()
            : isDirected(std::is_same_v<Direction, DirectedG>),
              isWeighted(!std::is_same_v<EdgeType, UnweightedG>) {}

        template <typename... Vertices>
        void addVertex(Vertices &&...vertices)
        {
            auto add_single_vertex = [this](const VertexType &vertex)
            {
                if (vertexToIndex.count(vertex))
                    return;
                size_t newIndex = numVertices++;
                vertexToIndex[vertex] = newIndex;
                indexToVertex.push_back(vertex);
            };

            (add_single_vertex(std::forward<Vertices>(vertices)), ...);

            adjacencyMatrix.resize(numVertices * numVertices, std::nullopt);
        }

        bool operator()(const VertexType src, const VertexType &dest)
        {
            if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
            {
                return false;
            }

            size_t srcIndex = vertexToIndex[src];
            size_t destIndex = vertexToIndex[dest];

            if (adjacencyMatrix[getIndex(srcIndex, destIndex)].has_value())
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        // for weighted.
        void addEdge(const VertexType &src, const VertexType &dest, const EdgeType &edge)
        {
            if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
                throw std::invalid_argument("One or both vertices do not exist");

            size_t srcIndex = vertexToIndex.at(src);
            size_t destIndex = vertexToIndex.at(dest);

            adjacencyMatrix[getIndex(srcIndex, destIndex)] = EdgeInfo<EdgeType>(edge);

            if (!isDirected)
            {
                adjacencyMatrix[getIndex(destIndex, srcIndex)] = EdgeInfo<EdgeType>(edge);
            }
        }

        // for unweighted
        void addEdge(const VertexType &src, const VertexType &dest)
        {
            if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
            {
                throw std::invalid_argument("One or both vertices do not exist");
            }

            size_t srcIndex = vertexToIndex.at(src);
            size_t destIndex = vertexToIndex.at(dest);

            adjacencyMatrix[getIndex(srcIndex, destIndex)] = EdgeInfo<EdgeType>();

            if (!isDirected)
            {
                adjacencyMatrix[getIndex(destIndex, srcIndex)] = EdgeInfo<EdgeType>();
            }
        }

        // Remove edge
        void removeEdge(const VertexType &src, const VertexType &dest)
        {
            if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
                throw std::invalid_argument("One or both vertices do not exist");

            size_t srcIndex = vertexToIndex.at(src);
            size_t destIndex = vertexToIndex.at(dest);

            adjacencyMatrix[getIndex(srcIndex, destIndex)] = std::nullopt;

            if (!isDirected)
            {
                adjacencyMatrix[getIndex(destIndex, srcIndex)] = std::nullopt;
            }
        }

        // Check if edge exists
        bool hasEdge(const VertexType &src, const VertexType &dest) const
        {
            if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
                throw std::invalid_argument("One or both vertices do not exist");

            size_t srcIndex = vertexToIndex.at(src);
            size_t destIndex = vertexToIndex.at(dest);

            return adjacencyMatrix[getIndex(srcIndex, destIndex)].has_value();
        }

        // Get vertices
        const std::vector<VertexType> &getVertices() const
        {
            return indexToVertex;
        }

        const EdgeType &getEdge(const VertexType &src, const VertexType &dest) const
        {
            if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
            {
                throw std::invalid_argument("One or both vertices do not exist!");
            }
            size_t srcIndex = vertexToIndex.at(src);
            size_t destIndex = vertexToIndex.at(dest);

            auto &edgeValue = adjacencyMatrix[getIndex(srcIndex, destIndex)];

            if (edgeValue.has_value())
            {
                return edgeValue.value().value;
            }
            else
            {
                throw std::runtime_error("No Edge exists between the given vertices.");
            }
        }

        // Get all edges
        std::vector<std::tuple<VertexType, VertexType, EdgeType>> getAllEdges() const
        {
            std::vector<std::tuple<VertexType, VertexType, EdgeType>> edges;

            for (size_t srcIndex = 0; srcIndex < numVertices; ++srcIndex)
            {
                for (size_t destIndex = 0; destIndex < numVertices; ++destIndex)
                {
                    const auto &edgeValue = adjacencyMatrix[getIndex(srcIndex, destIndex)];
                    if (edgeValue.has_value())
                    {
                        edges.emplace_back(
                            indexToVertex[srcIndex],
                            indexToVertex[destIndex],
                            edgeValue.value().value);
                    }
                }
            }
            return edges;
        }
        // Get indegree for a vertex
        [[nodiscard]] size_t indegree(const VertexType& vertex) const
        {
            if (!vertexToIndex.count(vertex))
            {
                throw std::invalid_argument("Vertex does not exist in the graph");
            }
            if (!isDirected)
            {
                std::cerr << "\nIndegree is not defined for undirected graphs. Returning Total Degree\n";
                return totalDegree(vertex);
            }
            size_t vertexIndex = vertexToIndex.at(vertex);
            size_t indegree = 0;
            for (size_t srcIndex = 0; srcIndex < numVertices; ++srcIndex)
            {
                if (adjacencyMatrix[getIndex(srcIndex, vertexIndex)].has_value())
                {
                    indegree++;
                }
            }
            return indegree;
        }
        // Get outdegree for a vertex
        [[nodiscard]] size_t outdegree(const VertexType& vertex) const
        {
            if (!vertexToIndex.count(vertex))
            {
                throw std::invalid_argument("Vertex does not exist in the graph");
            }
            if (!isDirected)
            {
                std::cerr << "\nOutdegree is not defined for undirected graphs. Returning total degree\n";
                return totalDegree(vertex);
            }
            size_t vertexIndex = vertexToIndex.at(vertex);
            size_t outdegree = 0;
            for (size_t destIndex = 0; destIndex < numVertices; ++destIndex)
            {
                if (adjacencyMatrix[getIndex(vertexIndex, destIndex)].has_value())
                {
                    outdegree++;
                }
            }
            return outdegree;
        }
        // Get totalDegree for a vertex
        [[nodiscard]] size_t totalDegree(const VertexType& vertex) const
        {
            if (!vertexToIndex.count(vertex))
            {
                throw std::invalid_argument("Vertex does not exist in the graph");
            }
            if (isDirected)
                return indegree(vertex) + outdegree(vertex);
            size_t vertexIndex = vertexToIndex.at(vertex);
            size_t totaldegree = 0;
            for (size_t srcIndex = 0; srcIndex < numVertices; ++srcIndex)
            {
                if (adjacencyMatrix[getIndex(srcIndex, vertexIndex)].has_value())
                {
                    totaldegree++;
                }
            }
            return totaldegree;
        }
        // Get neighbors for a vertex
        std::set<VertexType> getNeighbors(const VertexType& vertex) const
        {
            if (!vertexToIndex.count(vertex))
            {
                throw std::invalid_argument("Vertex does not exist in the graph");
            }

            size_t vertexIndex = vertexToIndex.at(vertex);

            // Using a set to store neighbors
            std::set<VertexType> neighbors;

            for (size_t destIndex = 0; destIndex < numVertices; ++destIndex)
            {
                if (adjacencyMatrix[getIndex(vertexIndex, destIndex)].has_value())
                {
                    neighbors.insert(indexToVertex[destIndex]);
                }

                // Check reverse direction only if the graph is undirected
                if (!isDirected && adjacencyMatrix[getIndex(destIndex, vertexIndex)].has_value())
                {
                    neighbors.insert(indexToVertex[destIndex]);
                }
            }

            return neighbors;
        }

        // find all paths b/w two vertices
        std::vector<std::vector<VertexType>> findAllPaths(const VertexType &src, const VertexType &dest)
        {
            if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
                throw std::invalid_argument("One or both vertices do not exist");

            std::vector<std::vector<VertexType>> allPaths;
            std::stack<std::pair<VertexType, std::vector<VertexType>>> stack;
            std::map<VertexType, bool> visited;

            stack.push({src, {src}});

            while (!stack.empty())
            {
                auto [current, currentPath] = stack.top();
                stack.pop();
                visited[current] = true;

                if (current == dest)
                {
                    allPaths.push_back(currentPath);
                }
                else
                {
                    size_t currentIndex = vertexToIndex[current];
                    for (size_t i = 0; i < numVertices; ++i)
                    {
                        if (adjacencyMatrix[getIndex(currentIndex, i)].has_value())
                        {
                            VertexType nextVertex = indexToVertex[i];
                            if (std::find(currentPath.begin(), currentPath.end(), nextVertex) == currentPath.end())
                            {
                                auto newPath = currentPath;
                                newPath.push_back(nextVertex);
                                stack.push({nextVertex, newPath});
                            }
                        }
                    }
                }
                visited[current] = false;
            }

            return allPaths;
        }

    void updateEdge(int fromVertex, int toVertex, int weight) {
        // Check if graph is unweighted
        if (!isWeighted) {
            throw std::runtime_error("Graph is unweighted. Cannot update edge with weight.");
        }

        // Check if vertices are valid
        if (fromVertex < 0 || fromVertex >= vertexCount || toVertex < 0 || toVertex >= vertexCount) {
            throw std::out_of_range("One or both vertices do not exist.");
        }

        // Update the edge in the adjacency matrix
        adjacencyMatrix[fromVertex][toVertex] = weight;

        // If the graph is undirected, update the reverse edge
        adjacencyMatrix[toVertex][fromVertex] = weight;
    }

    private:
        std::map<VertexType, size_t> vertexToIndex;
        std::vector<VertexType> indexToVertex;
        std::vector<std::optional<EdgeInfo<EdgeType>>> adjacencyMatrix;
        size_t numVertices = 0;
        bool isDirected;
        bool isWeighted;

        inline size_t getIndex(size_t src, size_t dest) const
        {
            return src * numVertices + dest;
        }
    };
}
