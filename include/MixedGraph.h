#pragma once

#include <vector>
#include <optional>
#include <unordered_map>
#include <stdexcept>

template <typename VertexType, typename EdgeType = bool>
class MixedGraphMatrix {
public:
    MixedGraphMatrix();
    void addEdge(const VertexType &src, const VertexType &dest, std::optional<EdgeType> edgeValue = {}, bool isDirected = false);
    void addEdge(const VertexType &src, const VertexType &dest, const EdgeType &edge);
    void addEdge(const VertexType &src, const VertexType &dest, bool isDirected);
    [[nodiscard]] int indegree(const VertexType &vertex) const;
    [[nodiscard]] int outdegree(const VertexType &vertex) const;
    [[nodiscard]] int totalDegree(const VertexType &vertex) const;
    void removeEdge(const VertexType &src, const VertexType &dest);
    void updateEdge(const VertexType &src, const VertexType &dest, const EdgeType &edgeValue);

private:
    std::unordered_map<VertexType, size_t> vertexToIndex;
    std::vector<VertexType> indexToVertex;
    std::vector<std::optional<EdgeType>> adjacencyMatrix;
    size_t numVertices;

    size_t getIndex(const VertexType &vertex) const;
    size_t getIndex(size_t srcIndex, size_t destIndex) const;
};

// Definitions

template <typename VertexType, typename EdgeType>
MixedGraphMatrix<VertexType, EdgeType>::MixedGraphMatrix() : numVertices(0) {}

template <typename VertexType, typename EdgeType>
size_t MixedGraphMatrix<VertexType, EdgeType>::getIndex(const VertexType &vertex) const {
    auto it = vertexToIndex.find(vertex);
    if (it == vertexToIndex.end()) throw std::invalid_argument("Vertex does not exist");
    return it->second;
}

template <typename VertexType, typename EdgeType>
size_t MixedGraphMatrix<VertexType, EdgeType>::getIndex(size_t srcIndex, size_t destIndex) const {
    return srcIndex * numVertices + destIndex;
}

template <typename VertexType, typename EdgeType>
void MixedGraphMatrix<VertexType, EdgeType>::addEdge(const VertexType &src, const VertexType &dest, std::optional<EdgeType> edgeValue, bool isDirected) {
    size_t srcIndex = getIndex(src);
    size_t destIndex = getIndex(dest);
    adjacencyMatrix[getIndex(srcIndex, destIndex)] = edgeValue;
    if (!isDirected) {
        adjacencyMatrix[getIndex(destIndex, srcIndex)] = edgeValue;
    }
}

template <typename VertexType, typename EdgeType>
void MixedGraphMatrix<VertexType, EdgeType>::addEdge(const VertexType &src, const VertexType &dest, const EdgeType &edge) {
    addEdge(src, dest, std::optional<EdgeType>(edge), false);
}

template <typename VertexType, typename EdgeType>
void MixedGraphMatrix<VertexType, EdgeType>::addEdge(const VertexType &src, const VertexType &dest, bool isDirected) {
    addEdge(src, dest, std::nullopt, isDirected);
}

template <typename VertexType, typename EdgeType>
void MixedGraphMatrix<VertexType, EdgeType>::removeEdge(const VertexType &src, const VertexType &dest) {
    size_t srcIndex = getIndex(src);
    size_t destIndex = getIndex(dest);
    adjacencyMatrix[getIndex(srcIndex, destIndex)] = std::nullopt;
    adjacencyMatrix[getIndex(destIndex, srcIndex)] = std::nullopt;
}

template <typename VertexType, typename EdgeType>
void MixedGraphMatrix<VertexType, EdgeType>::updateEdge(const VertexType &src, const VertexType &dest, const EdgeType &edgeValue) {
    size_t srcIndex = getIndex(src);
    size_t destIndex = getIndex(dest);
    adjacencyMatrix[getIndex(srcIndex, destIndex)] = edgeValue;
}

template <typename VertexType, typename EdgeType>
[[nodiscard]] int MixedGraphMatrix<VertexType, EdgeType>::indegree(const VertexType &vertex) const {
    size_t vertexIndex = getIndex(vertex);
    int degree = 0;
    for (size_t i = 0; i < numVertices; ++i) {
        if (adjacencyMatrix[getIndex(i, vertexIndex)].has_value()) {
            ++degree;
        }
    }
    return degree;
}

template <typename VertexType, typename EdgeType>
[[nodiscard]] int MixedGraphMatrix<VertexType, EdgeType>::outdegree(const VertexType &vertex) const {
    size_t vertexIndex = getIndex(vertex);
    int degree = 0;
    for (size_t i = 0; i < numVertices; ++i) {
        if (adjacencyMatrix[getIndex(vertexIndex, i)].has_value()) {
            ++degree;
        }
    }
    return degree;
}

template <typename VertexType, typename EdgeType>
[[nodiscard]] int MixedGraphMatrix<VertexType, EdgeType>::totalDegree(const VertexType &vertex) const {
    return indegree(vertex) + outdegree(vertex);
}
