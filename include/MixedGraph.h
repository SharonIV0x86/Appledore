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
        void addVertex(const VertexType &vertex);
        const std::vector<VertexType> &getVertices() const;
        bool hasEdge(const VertexType &src, const VertexType &dest) const;
        EdgeType getEdgeValue(const VertexType &src, const VertexType &dest) const;
        std::vector<EdgeType> getEdges() const;
        MixedGraphMatrix() : vertexToIndex(), indexToVertex(), adjacencyMatrix() {};
        void removeEdge(const VertexType &src, const VertexType &dest);
        void updateEdge(const VertexType &, const VertexType &, const EdgeType &);
        void addEdge(const VertexType &src, const VertexType &dest, std::optional<EdgeType> edgeValue, bool isDirected = false);
        void addEdge(const VertexType &src, const VertexType &dest, bool isDirected);
        void addEdge(const VertexType &src, const VertexType &dest, const EdgeType &edge);
        void addEdge(const VertexType &src, const VertexType &dest, const EdgeType &edge, bool isDirected);
        void removeVertex(const VertexType &vert);

        [[nodiscard]] size_t indegree(const VertexType &vertex) const;
        [[nodiscard]] size_t outdegree(const VertexType &vertex) const;
        [[nodiscard]] size_t totalDegree(const VertexType &vertex) const;

        const bool operator()(VertexType src, VertexType dest) const
        {
            if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
            {
                return false;
            }
            size_t srcIndex = vertexToIndex.at(src);
            size_t destIndex = vertexToIndex.at(dest);
            size_t index = getIndex(srcIndex, destIndex);
            return adjacencyMatrix[index].has_value();
        }

    private:
        std::map<VertexType, size_t> vertexToIndex;
        std::vector<VertexType> indexToVertex;
        std::vector<std::optional<EdgeInfo<EdgeType>>> adjacencyMatrix;
        size_t numVertices = 0;
        inline size_t getIndex(size_t src, size_t dest) const;
    };

    template <typename VertexType, typename EdgeType>
    void MixedGraphMatrix<VertexType, EdgeType>::addVertex(const VertexType &vertex)
    {
        if (vertexToIndex.count(vertex))
        {
            std::cout << "Vertex already exists\n";
            return;
        }

        size_t newIndex = numVertices;
        vertexToIndex[vertex] = newIndex;
        indexToVertex.push_back(vertex);
        numVertices++;

        adjacencyMatrix.resize(numVertices * numVertices, std::nullopt);
    }

    template <typename VertexType, typename EdgeType>
    EdgeType MixedGraphMatrix<VertexType, EdgeType>::getEdgeValue(const VertexType &src, const VertexType &dest) const
    {
        if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
        {
            throw std::invalid_argument("One or both vertices do not exist");
        }

        size_t srcIndex = vertexToIndex.at(src);
        size_t destIndex = vertexToIndex.at(dest);

        size_t index = getIndex(srcIndex, destIndex);

        if (!adjacencyMatrix[index].has_value())
        {
            throw std::runtime_error("Edge does not exist");
        }

        return adjacencyMatrix[index]->value;
    }

    template <typename VertexType, typename EdgeType>
    inline size_t MixedGraphMatrix<VertexType, EdgeType>::getIndex(size_t src, size_t dest) const
    {
        return src * numVertices + dest;
    }

    template <typename VertexType, typename EdgeType>
    // generic, being used by all overloads.
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
    // case 1: non weidghted, directed/undirected egde.
    void MixedGraphMatrix<VertexType, EdgeType>::addEdge(const VertexType &src, const VertexType &dest, bool isDirected)
    {
        addEdge(src, dest, std::nullopt, isDirected);
    }
    template <typename VertexType, typename EdgeType>
    // case 2: weighted, undirected egde.
    void MixedGraphMatrix<VertexType, EdgeType>::addEdge(const VertexType &src, const VertexType &dest, const EdgeType &edge)
    {
        addEdge(src, dest, edge, false);
    }
    template <typename VertexType, typename EdgeType>
    // case 3: weighted, undirected egde.
    void MixedGraphMatrix<VertexType, EdgeType>::addEdge(const VertexType &src, const VertexType &dest, const EdgeType &edge, bool isDirected)
    {
        addEdge(src, dest, std::optional<EdgeType>(edge), isDirected);
    }

    template <typename VertexType, typename EdgeType>
    void MixedGraphMatrix<VertexType, EdgeType>::removeEdge(const VertexType &src, const VertexType &dest)
    {
        if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
        {
            throw std::invalid_argument("One or both vertices do not exist");
        }

        size_t srcIndex = vertexToIndex[src];
        size_t destIndex = vertexToIndex[dest];

        size_t index = getIndex(srcIndex, destIndex);
        adjacencyMatrix[index] = std::nullopt;

        if (!adjacencyMatrix[getIndex(destIndex, srcIndex)].value_or(EdgeInfo<EdgeType>()).isDirected)
        {
            adjacencyMatrix[getIndex(destIndex, srcIndex)] = std::nullopt;
        }
    }

    template <typename VertexType, typename EdgeType>
    bool MixedGraphMatrix<VertexType, EdgeType>::hasEdge(const VertexType &src, const VertexType &dest) const
    {
        if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
        {
            throw std::invalid_argument("One or both vertices do not exist");
        }

        size_t srcIndex = vertexToIndex.at(src);
        size_t destIndex = vertexToIndex.at(dest);

        return adjacencyMatrix[getIndex(srcIndex, destIndex)].has_value();
    }
    template <typename VertexType, typename EdgeType>
    void MixedGraphMatrix<VertexType, EdgeType>::updateEdge(const VertexType &src, const VertexType &dest, const EdgeType &newValue)
    {
        if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
        {
            throw std::invalid_argument("One or both vertices do not exist");
        }

        size_t srcIndex = vertexToIndex.at(src);
        size_t destIndex = vertexToIndex.at(dest);

        size_t index = getIndex(srcIndex, destIndex);

        if (!adjacencyMatrix[index].has_value())
        {
            throw std::runtime_error("Edge does not exist");
        }

        adjacencyMatrix[index]->value = newValue;

        // If the edge is undirected, update the reverse edge too
        if (!adjacencyMatrix[index]->isDirected)
        {
            size_t reverseIndex = getIndex(destIndex, srcIndex);
            adjacencyMatrix[reverseIndex]->value = newValue;
        }
    }

    template <typename VertexType, typename EdgeType>
    const std::vector<VertexType> &MixedGraphMatrix<VertexType, EdgeType>::getVertices() const
    {
        return indexToVertex;
    }

    template <typename VertexType, typename EdgeType>
    std::vector<EdgeType> MixedGraphMatrix<VertexType, EdgeType>::getEdges() const
    {
        std::vector<EdgeType> edges;

        for (size_t src = 0; src < numVertices; ++src)
        {
            for (size_t dest = 0; dest < numVertices; ++dest)
            {
                size_t index = src * numVertices + dest;

                if (adjacencyMatrix[index].has_value())
                {
                    if (adjacencyMatrix[index]->isDirected)
                    {
                        edges.push_back(adjacencyMatrix[index]->value);
                    }
                    else if (src <= dest)
                    {
                        edges.push_back(adjacencyMatrix[index]->value);
                    }
                }
            }
        }
        return edges;
    }

    // ---------------------------------------------------
    // New method to remove a vertex from the graph
    // ---------------------------------------------------
    template <typename VertexType, typename EdgeType>
    void MixedGraphMatrix<VertexType, EdgeType>::removeVertex(const VertexType &vert)
    {
        if (!vertexToIndex.count(vert))
        {
            throw std::invalid_argument("Vertex does not exist");
        }

        size_t removeIndex = vertexToIndex[vert];

        // Step 1: Remove entry from map and the corresponding entry in indexToVertex
        vertexToIndex.erase(vert);

        // Step 2: We will re-map the last vertex in `indexToVertex` to fill the gap
        if (removeIndex != numVertices - 1)
        {
            VertexType lastVertex = indexToVertex[numVertices - 1];

            indexToVertex[removeIndex] = lastVertex;

            vertexToIndex[lastVertex] = removeIndex;
        }

        indexToVertex.pop_back();
        --numVertices;

        // Step 3: Rebuild the adjacencyMatrix to remove the row and column of `removeIndex`
        std::vector<std::optional<EdgeInfo<EdgeType>>> newMatrix(numVertices * numVertices, std::nullopt);

        for (size_t i = 0; i <= numVertices; ++i)
        {
            if (i == removeIndex)
                continue;

            for (size_t j = 0; j <= numVertices; ++j)
            {
                if (j == removeIndex)
                    continue;
                if (i < numVertices && j < numVertices)
                {
                    size_t oldRow = (i < removeIndex) ? i : i + 1;
                    size_t oldCol = (j < removeIndex) ? j : j + 1;

                    newMatrix[i * numVertices + j] = adjacencyMatrix[oldRow * (numVertices + 1) + oldCol];
                }
            }
        }

        adjacencyMatrix = std::move(newMatrix);
    }
    // ---------------------------------------------------
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
        if (!vertexToIndex.count(vertex))
        {
            throw std::invalid_argument("Vertex does not exist");
        }

        size_t vertexIndex = vertexToIndex.at(vertex);
        size_t totalDegreeCount = 0;

        for (size_t other = 0; other < numVertices; ++other)
        {
            auto forwardIndex = getIndex(vertexIndex, other);
            auto backwardIndex = getIndex(other, vertexIndex);

            if (adjacencyMatrix[forwardIndex].has_value())
            {
                if (adjacencyMatrix[forwardIndex]->isDirected)
                {
                    ++totalDegreeCount;
                }
                else
                {
                    ++totalDegreeCount;
                }
            }

            if (adjacencyMatrix[backwardIndex].has_value() &&
                adjacencyMatrix[backwardIndex]->isDirected)
            {
                ++totalDegreeCount;
            }
        }

        return totalDegreeCount;
    }

};
