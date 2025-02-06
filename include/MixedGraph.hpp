#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>
#include <optional>
#include <map>
#include "MatrixRep.hpp"
namespace Appledore
{
    template <typename VertexType, typename EdgeType = bool>
    class MixedGraphMatrix : public Appledore::MatrixRepresentation
    {
    public:
        template <typename... VertexArgs>
        void addVertex(VertexArgs&&... vertices);
        size_t getNumVertices() const;
        const std::map<VertexType, size_t>& getVertexToIndex() const;
        const std::vector<VertexType>& getIndexToVertex() const;
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
    template <typename... VertexArgs>
    void MixedGraphMatrix<VertexType, EdgeType>::addVertex(VertexArgs&&... vertices) {
        // Helper lambda to add a single vertex
        auto addSingleVertex = [this](auto&& vertex) {
            try {
                // Check if the vertex type matches the graph's VertexType
                if constexpr (!std::is_convertible_v<std::decay_t<decltype(vertex)>, VertexType>) {
                    std::cerr << "Vertex type mismatch: Expected " << typeid(VertexType).name() << " but got "
                            << typeid(vertex).name() << ". Skipping addition of this vertex.\n";
                    return;
                }

                // Check if the vertex already exists
                if (vertexToIndex.count(vertex)) {
                    std::cerr << "Vertex " << vertex << " already exists. Skipping.\n";
                    return;
                }

                const size_t old_numVertices = numVertices;
                const size_t new_numVertices = old_numVertices + 1;

                // Update vertex mappings
                vertexToIndex[vertex] = old_numVertices;
                indexToVertex.push_back(std::forward<decltype(vertex)>(vertex));

                // Create new adjacency matrix with increased size
                std::vector<std::optional<EdgeInfo<EdgeType>>> newMatrix(new_numVertices * new_numVertices, std::nullopt);

                // Copy existing elements to the new matrix
                for (size_t row = 0; row < old_numVertices; ++row) {
                    for (size_t col = 0; col < old_numVertices; ++col) {
                        const size_t oldIndex = row * old_numVertices + col;
                        const size_t newIndex = row * new_numVertices + col;
                        newMatrix[newIndex] = std::move(adjacencyMatrix[oldIndex]);
                    }
                }

                // Update the adjacency matrix and number of vertices
                adjacencyMatrix = std::move(newMatrix);
                numVertices = new_numVertices;  // Ensure numVertices is updated correctly

            } catch (const std::exception& e) {
                // Handle the exception and log the error but continue adding valid vertices
                std::cerr << "Error adding vertex " << vertex << ": " << e.what() << "\n";
            }
        };

        // Process each vertex in the parameter pack
        (addSingleVertex(std::forward<VertexArgs>(vertices)), ...);
    }

    template <typename VertexType, typename EdgeType>
    size_t Appledore::MixedGraphMatrix<VertexType, EdgeType>::getNumVertices() const {
        return numVertices;
    }

    template <typename VertexType, typename EdgeType>
    const std::map<VertexType, size_t>& MixedGraphMatrix<VertexType, EdgeType>::getVertexToIndex() const {
        return vertexToIndex;
    }

    template <typename VertexType, typename EdgeType>
    const std::vector<VertexType>& MixedGraphMatrix<VertexType, EdgeType>::getIndexToVertex() const {
        return indexToVertex;
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

    template <typename VertexType, typename EdgeType>
    void MixedGraphMatrix<VertexType, EdgeType>::removeVertex(const VertexType &vert)
    {

        if (!vertexToIndex.count(vert))
        {
            throw std::invalid_argument("Vertex does not exist in the graph.");
        }

        size_t remIdx = vertexToIndex[vert];
        size_t lastIdx = numVertices - 1;

        if (remIdx != lastIdx)
        {
            for (size_t c = 0; c < numVertices; ++c)
            {
                std::swap(adjacencyMatrix[getIndex(remIdx, c)], adjacencyMatrix[getIndex(lastIdx, c)]);
            }
            for (size_t r = 0; r < numVertices; ++r)
            {
                std::swap(adjacencyMatrix[getIndex(r, remIdx)], adjacencyMatrix[getIndex(r, lastIdx)]);
            }

            VertexType movedVertex = indexToVertex[lastIdx];
            vertexToIndex[movedVertex] = remIdx;
            indexToVertex[remIdx] = movedVertex;
        }

        vertexToIndex.erase(vert);
        indexToVertex.pop_back();

        size_t newSize = (numVertices - 1) * (numVertices - 1);
        std::vector<std::optional<EdgeInfo<EdgeType>>> newMatrix(newSize);

        for (size_t r = 0; r < numVertices - 1; ++r)
        {
            for (size_t c = 0; c < numVertices - 1; ++c)
            {
                newMatrix[r * (numVertices - 1) + c] = adjacencyMatrix[getIndex(r, c)];
            }
        }

        adjacencyMatrix = std::move(newMatrix);

        --numVertices;
    }
   
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