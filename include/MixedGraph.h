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
        MixedGraphMatrix();

        void addVertex(const VertexType &vertex);
        void addEdge(const VertexType &src, const VertexType &dest, std::optional<EdgeType> edgeValue = {}, bool isDirected = false);
        void addEdge(const VertexType &src, const VertexType &dest, bool isDirected);
        void addEdge(const VertexType &src, const VertexType &dest, const EdgeType &edge);
        void addEdge(const VertexType &src, const VertexType &dest, const EdgeType &edge, bool isDirected);

        void removeEdge(const VertexType &src, const VertexType &dest);
        void updateEdge(const VertexType &src, const VertexType &dest, const EdgeType &newValue);

        [[nodiscard]] size_t indegree(const VertexType &vertex) const;
        [[nodiscard]] size_t outdegree(const VertexType &vertex) const;
        [[nodiscard]] size_t totalDegree(const VertexType &vertex) const;

        const std::vector<VertexType> &getVertices() const;
        bool hasEdge(const VertexType &src, const VertexType &dest) const;
        EdgeType getEdgeValue(const VertexType &src, const VertexType &dest) const;
        std::vector<EdgeType> getEdges() const;

    private:
        std::map<VertexType, size_t> vertexToIndex;
        std::vector<VertexType> indexToVertex;
        std::vector<std::optional<EdgeInfo<EdgeType>>> adjacencyMatrix;
        size_t numVertices;

        inline size_t getIndex(size_t src, size_t dest) const;
    };

    // Constructor
    template <typename VertexType, typename EdgeType>
    MixedGraphMatrix<VertexType, EdgeType>::MixedGraphMatrix() : numVertices(0) {}

    // Add a vertex
    template <typename VertexType, typename EdgeType>
    void MixedGraphMatrix<VertexType, EdgeType>::addVertex(const VertexType &vertex)
    {
        if (vertexToIndex.count(vertex))
        {
            std::cout << "Vertex already exists\n";
            return;
        }

        size_t newIndex = numVertices++;
        vertexToIndex[vertex] = newIndex;
        indexToVertex.push_back(vertex);

        adjacencyMatrix.resize(numVertices * numVertices, std::nullopt);
    }

    // Add edges (all overloads)
    template <typename VertexType, typename EdgeType>
    void MixedGraphMatrix<VertexType, EdgeType>::addEdge(const VertexType &src, const VertexType &dest, std::optional<EdgeType> edgeValue, bool isDirected)
    {
        if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
        {
            throw std::invalid_argument("One or both vertices do not exist");
        }

        size_t srcIndex = vertexToIndex.at(src);
        size_t destIndex = vertexToIndex.at(dest);

        size_t index = getIndex(srcIndex, destIndex);
        adjacencyMatrix[index] = EdgeInfo<EdgeType>(edgeValue.value_or(EdgeType()), isDirected);

        if (!isDirected)
        {
            size_t reverseIndex = getIndex(destIndex, srcIndex);
            adjacencyMatrix[reverseIndex] = EdgeInfo<EdgeType>(edgeValue.value_or(EdgeType()), isDirected);
        }
    }

    template <typename VertexType, typename EdgeType>
    void MixedGraphMatrix<VertexType, EdgeType>::addEdge(const VertexType &src, const VertexType &dest, bool isDirected)
    {
        addEdge(src, dest, std::nullopt, isDirected);
    }

    template <typename VertexType, typename EdgeType>
    void MixedGraphMatrix<VertexType, EdgeType>::addEdge(const VertexType &src, const VertexType &dest, const EdgeType &edge)
    {
        addEdge(src, dest, edge, false);
    }

    template <typename VertexType, typename EdgeType>
    void MixedGraphMatrix<VertexType, EdgeType>::addEdge(const VertexType &src, const VertexType &dest, const EdgeType &edge, bool isDirected)
    {
        addEdge(src, dest, std::optional<EdgeType>(edge), isDirected);
    }

    // Degree-related methods
    template <typename VertexType, typename EdgeType>
    size_t MixedGraphMatrix<VertexType, EdgeType>::indegree(const VertexType &vertex) const
    {
        if (!vertexToIndex.count(vertex))
        {
            throw std::invalid_argument("Vertex does not exist");
        }

        size_t vertexIndex = vertexToIndex.at(vertex);
        size_t inDegreeCount = 0;

        for (size_t src = 0; src < numVertices; ++src)
        {
            if (adjacencyMatrix[getIndex(src, vertexIndex)].has_value())
            {
                ++inDegreeCount;
            }
        }

        return inDegreeCount;
    }

    template <typename VertexType, typename EdgeType>
    size_t MixedGraphMatrix<VertexType, EdgeType>::outdegree(const VertexType &vertex) const
    {
        if (!vertexToIndex.count(vertex))
        {
            throw std::invalid_argument("Vertex does not exist");
        }

        size_t vertexIndex = vertexToIndex.at(vertex);
        size_t outDegreeCount = 0;

        for (size_t dest = 0; dest < numVertices; ++dest)
        {
            if (adjacencyMatrix[getIndex(vertexIndex, dest)].has_value())
            {
                ++outDegreeCount;
            }
        }

        return outDegreeCount;
    }

    template <typename VertexType, typename EdgeType>
    size_t MixedGraphMatrix<VertexType, EdgeType>::totalDegree(const VertexType &vertex) const
    {
        return indegree(vertex) + outdegree(vertex);
    }

    // Utility methods
    template <typename VertexType, typename EdgeType>
    inline size_t MixedGraphMatrix<VertexType, EdgeType>::getIndex(size_t src, size_t dest) const
    {
        return src * numVertices + dest;
    }

    template <typename VertexType, typename EdgeType>
    const std::vector<VertexType> &MixedGraphMatrix<VertexType, EdgeType>::getVertices() const
    {
        return indexToVertex;
    }

    template <typename VertexType, typename EdgeType>
    bool MixedGraphMatrix<VertexType, EdgeType>::hasEdge(const VertexType &src, const VertexType &dest) const
    {
        if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
        {
            throw std::invalid_argument("One or both vertices do not exist");
        }

        return adjacencyMatrix[getIndex(vertexToIndex.at(src), vertexToIndex.at(dest))].has_value();
    }
} // namespace Appledore
