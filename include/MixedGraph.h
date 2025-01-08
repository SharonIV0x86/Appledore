#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>
#include <optional>
#include <map>

namespace Appledore
{
    template <typename EdgeType>
    struct EdgeInfo
    {
        EdgeType value;
        bool isDirected;

        EdgeInfo() : value(), isDirected(false) {}
        EdgeInfo(const EdgeType &value, bool isDirected = false)
            : value(value), isDirected(isDirected) {}
    };

    template <typename VertexType, typename EdgeType = bool>
    class MixedGraphMatrix
    {
    public:
        MixedGraphMatrix()
            : vertexToIndex(), indexToVertex(), adjacencyMatrix(), numVertices(0) {}

        void addVertex(const VertexType &vertex)
        {
            if (vertexToIndex.count(vertex))
                throw std::invalid_argument("Vertex already exists.");
            vertexToIndex[vertex] = numVertices;
            indexToVertex.push_back(vertex);
            ++numVertices;

            size_t newSize = numVertices * numVertices;
            adjacencyMatrix.resize(newSize);
        }

        const std::vector<VertexType> &getVertices() const
        {
            return indexToVertex;
        }

        void addEdge(const VertexType &src, const VertexType &dest, std::optional<EdgeType> edgeValue = {}, bool isDirected = false)
        {
            if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
                throw std::invalid_argument("One or more vertices not found.");

            size_t srcIndex = vertexToIndex[src];
            size_t destIndex = vertexToIndex[dest];

            adjacencyMatrix[getIndex(srcIndex, destIndex)] = EdgeInfo<EdgeType>(edgeValue.value_or(EdgeType()), isDirected);

            if (!isDirected)
            {
                adjacencyMatrix[getIndex(destIndex, srcIndex)] = EdgeInfo<EdgeType>(edgeValue.value_or(EdgeType()), isDirected);
            }
        }

        void addEdge(const VertexType &src, const VertexType &dest, const EdgeType &edge, bool isDirected)
        {
            addEdge(src, dest, std::optional<EdgeType>(edge), isDirected);
        }

        void addEdge(const VertexType &src, const VertexType &dest, const EdgeType &edge)
        {
            addEdge(src, dest, std::optional<EdgeType>(edge), false);
        }

        void addEdge(const VertexType &src, const VertexType &dest, bool isDirected)
        {
            addEdge(src, dest, std::nullopt, isDirected);
        }

        void removeEdge(const VertexType &src, const VertexType &dest)
        {
            if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
                throw std::invalid_argument("One or more vertices not found.");

            size_t srcIndex = vertexToIndex[src];
            size_t destIndex = vertexToIndex[dest];

            adjacencyMatrix[getIndex(srcIndex, destIndex)] = std::nullopt;
            adjacencyMatrix[getIndex(destIndex, srcIndex)] = std::nullopt;
        }

        bool hasEdge(const VertexType &src, const VertexType &dest) const
        {
            if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
                return false;

            size_t srcIndex = vertexToIndex.at(src);
            size_t destIndex = vertexToIndex.at(dest);

            return adjacencyMatrix[getIndex(srcIndex, destIndex)].has_value();
        }

        EdgeType getEdgeValue(const VertexType &src, const VertexType &dest) const
        {
            if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
                throw std::invalid_argument("One or more vertices not found.");

            size_t srcIndex = vertexToIndex.at(src);
            size_t destIndex = vertexToIndex.at(dest);
            size_t index = getIndex(srcIndex, destIndex);

            if (!adjacencyMatrix[index])
                throw std::invalid_argument("Edge does not exist.");

            return adjacencyMatrix[index]->value;
        }

        std::vector<EdgeType> getEdges() const
        {
            std::vector<EdgeType> edges;

            for (const auto &edge : adjacencyMatrix)
            {
                if (edge.has_value())
                {
                    edges.push_back(edge->value);
                }
            }

            return edges;
        }

        size_t indegree(const VertexType &vertex) const
        {
            if (!vertexToIndex.count(vertex))
                throw std::invalid_argument("Vertex not found.");

            size_t vertexIndex = vertexToIndex.at(vertex);
            size_t inDeg = 0;

            for (size_t i = 0; i < numVertices; ++i)
            {
                if (adjacencyMatrix[getIndex(i, vertexIndex)] && adjacencyMatrix[getIndex(i, vertexIndex)]->isDirected)
                {
                    ++inDeg;
                }
            }

            return inDeg;
        }

        size_t outdegree(const VertexType &vertex) const
        {
            if (!vertexToIndex.count(vertex))
                throw std::invalid_argument("Vertex not found.");

            size_t vertexIndex = vertexToIndex.at(vertex);
            size_t outDeg = 0;

            for (size_t i = 0; i < numVertices; ++i)
            {
                if (adjacencyMatrix[getIndex(vertexIndex, i)] && adjacencyMatrix[getIndex(vertexIndex, i)]->isDirected)
                {
                    ++outDeg;
                }
            }

            return outDeg;
        }

        size_t totalDegree(const VertexType &vertex) const
        {
            if (!vertexToIndex.count(vertex))
                throw std::invalid_argument("Vertex not found.");

            size_t vertexIndex = vertexToIndex.at(vertex);
            size_t totalDeg = 0;

            for (size_t i = 0; i < numVertices; ++i)
            {
                if (adjacencyMatrix[getIndex(vertexIndex, i)])
                {
                    ++totalDeg;
                }

                if (adjacencyMatrix[getIndex(i, vertexIndex)] && adjacencyMatrix[getIndex(i, vertexIndex)]->isDirected)
                {
                    ++totalDeg;
                }
            }

            return totalDeg;
        }

        const bool operator()(VertexType src, VertexType dest) const
        {
            return hasEdge(src, dest);
        }

    private:
        std::map<VertexType, size_t> vertexToIndex;
        std::vector<VertexType> indexToVertex;
        std::vector<std::optional<EdgeInfo<EdgeType>>> adjacencyMatrix;
        size_t numVertices;

        inline size_t getIndex(size_t src, size_t dest) const
        {
            return src * numVertices + dest;
        }
    };
}
