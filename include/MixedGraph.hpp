#pragma once

#include "MatrixRep.hpp"
#include <iostream>
#include <optional>
#include <stdexcept>
#include <unordered_map>
#include <vector>
namespace Appledore {
template <typename VertexType, typename EdgeType = bool>
class MixedGraphMatrix
    : public Appledore::MatrixRepresentation<VertexType, EdgeType> {
public:
  template <typename... VertexArgs> void addVertex(VertexArgs &&...vertices);
  size_t getNumVertices() const;
  const std::vector<VertexType> &getVertices() const;
  bool hasEdge(const VertexType &src, const VertexType &dest) const;
  EdgeType getEdgeValue(const VertexType &src, const VertexType &dest) const;
  std::vector<EdgeType> getEdges() const;
  MixedGraphMatrix() : vertexToIndex(), indexToVertex(), adjacencyMatrix() {};
  void removeEdge(const VertexType &src, const VertexType &dest);
  void updateEdge(const VertexType &, const VertexType &, const EdgeType &);
  void addEdge(const VertexType &src, const VertexType &dest,
               std::optional<EdgeType> edgeValue, bool isDirected = false);
  void addEdge(const VertexType &src, const VertexType &dest, bool isDirected);
  void addEdge(const VertexType &src, const VertexType &dest,
               const EdgeType &edge);
  void addEdge(const VertexType &src, const VertexType &dest,
               const EdgeType &edge, bool isDirected);
  void removeVertex(const VertexType &vert);

  [[nodiscard]] size_t indegree(const VertexType &vertex) const;
  [[nodiscard]] size_t outdegree(const VertexType &vertex) const;
  [[nodiscard]] size_t totalDegree(const VertexType &vertex) const;

  const bool operator()(VertexType src, VertexType dest) const {
    if (!vertexToIndex.count(src) || !vertexToIndex.count(dest)) {
      return false;
    }
    size_t srcIndex = vertexToIndex.at(src);
    size_t destIndex = vertexToIndex.at(dest);
    size_t index = getIndex(srcIndex, destIndex);
    return adjacencyMatrix[index].has_value();
  }

private:
  std::unordered_map<VertexType, size_t, VertexHasher<VertexType>>
      vertexToIndex;
  std::vector<VertexType> indexToVertex;
  std::vector<std::optional<EdgeInfo<EdgeType>>> adjacencyMatrix;
  size_t numVertices = 0;
  inline size_t getIndex(size_t src, size_t dest) const;
};

template <typename VertexType, typename EdgeType>
template <typename... Vertices>
void MixedGraphMatrix<VertexType, EdgeType>::addVertex(Vertices &&...vertices) {
  auto add_single_vertex = [this](const VertexType &vertex) {
    if (vertexToIndex.count(vertex)) {
      return;
    }
    size_t newIndex = numVertices++;
    vertexToIndex[vertex] = newIndex;
    indexToVertex.push_back(vertex);
  };

  size_t oldSize = numVertices;

  (add_single_vertex(std::forward<Vertices>(vertices)), ...);

  if (oldSize == numVertices) {
    return;
  }

  std::vector<std::optional<EdgeInfo<EdgeType>>> newMatrix(
      numVertices * numVertices, std::nullopt);

  for (size_t i = 0; i < oldSize; ++i) {
    for (size_t j = 0; j < oldSize; ++j) {
      newMatrix[i * numVertices + j] =
          std::move(adjacencyMatrix[i * oldSize + j]);
    }
  }

  adjacencyMatrix = std::move(newMatrix);
}

template <typename VertexType, typename EdgeType>
size_t
Appledore::MixedGraphMatrix<VertexType, EdgeType>::getNumVertices() const {
  return numVertices;
}

template <typename VertexType, typename EdgeType>
EdgeType MixedGraphMatrix<VertexType, EdgeType>::getEdgeValue(
    const VertexType &src, const VertexType &dest) const {
  if (!vertexToIndex.count(src) || !vertexToIndex.count(dest)) {
    throw std::invalid_argument("One or both vertices do not exist");
  }

  size_t srcIndex = vertexToIndex.at(src);
  size_t destIndex = vertexToIndex.at(dest);

  size_t index = getIndex(srcIndex, destIndex);

  if (!adjacencyMatrix[index].has_value()) {
    throw std::runtime_error("Edge does not exist");
  }

  return adjacencyMatrix[index]->value;
}

template <typename VertexType, typename EdgeType>
inline size_t
MixedGraphMatrix<VertexType, EdgeType>::getIndex(size_t src,
                                                 size_t dest) const {
  return src * numVertices + dest;
}

template <typename VertexType, typename EdgeType>
// generic, being used by all overloads.
void MixedGraphMatrix<VertexType, EdgeType>::addEdge(
    const VertexType &src, const VertexType &dest,
    std::optional<EdgeType> edgeValue, bool isDirected) {
  if (!vertexToIndex.count(src) || !vertexToIndex.count(dest)) {
    throw std::invalid_argument("One or both vertices do not exist");
  }

  size_t srcIndex = vertexToIndex.at(src);
  size_t destIndex = vertexToIndex.at(dest);

  size_t index = getIndex(srcIndex, destIndex);
  adjacencyMatrix[index] =
      EdgeInfo<EdgeType>(edgeValue.value_or(EdgeType()), isDirected);

  if (!isDirected) {
    size_t reverseIndex = getIndex(destIndex, srcIndex);
    adjacencyMatrix[reverseIndex] =
        EdgeInfo<EdgeType>(edgeValue.value_or(EdgeType()), isDirected);
  }
}
template <typename VertexType, typename EdgeType>
// case 1: non weidghted, directed/undirected egde.
void MixedGraphMatrix<VertexType, EdgeType>::addEdge(const VertexType &src,
                                                     const VertexType &dest,
                                                     bool isDirected) {
  addEdge(src, dest, std::nullopt, isDirected);
}
template <typename VertexType, typename EdgeType>
// case 2: weighted, undirected egde.
void MixedGraphMatrix<VertexType, EdgeType>::addEdge(const VertexType &src,
                                                     const VertexType &dest,
                                                     const EdgeType &edge) {
  addEdge(src, dest, edge, false);
}
template <typename VertexType, typename EdgeType>
// case 3: weighted, undirected egde.
void MixedGraphMatrix<VertexType, EdgeType>::addEdge(const VertexType &src,
                                                     const VertexType &dest,
                                                     const EdgeType &edge,
                                                     bool isDirected) {
  addEdge(src, dest, std::optional<EdgeType>(edge), isDirected);
}

template <typename VertexType, typename EdgeType>
void MixedGraphMatrix<VertexType, EdgeType>::removeEdge(
    const VertexType &src, const VertexType &dest) {
  if (!vertexToIndex.count(src) || !vertexToIndex.count(dest)) {
    throw std::invalid_argument("One or both vertices do not exist");
  }

  size_t srcIndex = vertexToIndex[src];
  size_t destIndex = vertexToIndex[dest];

  size_t index = getIndex(srcIndex, destIndex);
  adjacencyMatrix[index] = std::nullopt;

  if (!adjacencyMatrix[getIndex(destIndex, srcIndex)]
           .value_or(EdgeInfo<EdgeType>())
           .isDirected) {
    adjacencyMatrix[getIndex(destIndex, srcIndex)] = std::nullopt;
  }
}

template <typename VertexType, typename EdgeType>
bool MixedGraphMatrix<VertexType, EdgeType>::hasEdge(
    const VertexType &src, const VertexType &dest) const {
  if (!vertexToIndex.count(src) || !vertexToIndex.count(dest)) {
    throw std::invalid_argument("One or both vertices do not exist");
  }

  size_t srcIndex = vertexToIndex.at(src);
  size_t destIndex = vertexToIndex.at(dest);

  return adjacencyMatrix[getIndex(srcIndex, destIndex)].has_value();
}
template <typename VertexType, typename EdgeType>
void MixedGraphMatrix<VertexType, EdgeType>::updateEdge(
    const VertexType &src, const VertexType &dest, const EdgeType &newValue) {
  if (!vertexToIndex.count(src) || !vertexToIndex.count(dest)) {
    throw std::invalid_argument("One or both vertices do not exist");
  }

  size_t srcIndex = vertexToIndex.at(src);
  size_t destIndex = vertexToIndex.at(dest);

  size_t index = getIndex(srcIndex, destIndex);

  if (!adjacencyMatrix[index].has_value()) {
    throw std::runtime_error("Edge does not exist");
  }

  adjacencyMatrix[index]->value = newValue;

  // If the edge is undirected, update the reverse edge too
  if (!adjacencyMatrix[index]->isDirected) {
    size_t reverseIndex = getIndex(destIndex, srcIndex);
    adjacencyMatrix[reverseIndex]->value = newValue;
  }
}

template <typename VertexType, typename EdgeType>
const std::vector<VertexType> &
MixedGraphMatrix<VertexType, EdgeType>::getVertices() const {
  return indexToVertex;
}

template <typename VertexType, typename EdgeType>
std::vector<EdgeType> MixedGraphMatrix<VertexType, EdgeType>::getEdges() const {
  std::vector<EdgeType> edges;

  for (size_t src = 0; src < numVertices; ++src) {
    for (size_t dest = 0; dest < numVertices; ++dest) {
      size_t index = src * numVertices + dest;

      if (adjacencyMatrix[index].has_value()) {
        if (adjacencyMatrix[index]->isDirected) {
          edges.push_back(adjacencyMatrix[index]->value);
        } else if (src <= dest) {
          edges.push_back(adjacencyMatrix[index]->value);
        }
      }
    }
  }
  return edges;
}

template <typename VertexType, typename EdgeType>
void MixedGraphMatrix<VertexType, EdgeType>::removeVertex(
    const VertexType &vert) {

  if (!vertexToIndex.count(vert)) {
    throw std::invalid_argument("Vertex does not exist in the graph.");
  }

  size_t remIdx = vertexToIndex[vert];
  size_t lastIdx = numVertices - 1;

  if (remIdx != lastIdx) {
    for (size_t c = 0; c < numVertices; ++c) {
      std::swap(adjacencyMatrix[getIndex(remIdx, c)],
                adjacencyMatrix[getIndex(lastIdx, c)]);
    }
    for (size_t r = 0; r < numVertices; ++r) {
      std::swap(adjacencyMatrix[getIndex(r, remIdx)],
                adjacencyMatrix[getIndex(r, lastIdx)]);
    }

    VertexType movedVertex = indexToVertex[lastIdx];
    vertexToIndex[movedVertex] = remIdx;
    indexToVertex[remIdx] = movedVertex;
  }

  vertexToIndex.erase(vert);
  indexToVertex.pop_back();

  size_t newSize = (numVertices - 1) * (numVertices - 1);
  std::vector<std::optional<EdgeInfo<EdgeType>>> newMatrix(newSize);

  for (size_t r = 0; r < numVertices - 1; ++r) {
    for (size_t c = 0; c < numVertices - 1; ++c) {
      newMatrix[r * (numVertices - 1) + c] = adjacencyMatrix[getIndex(r, c)];
    }
  }

  adjacencyMatrix = std::move(newMatrix);

  --numVertices;
}

template <typename VertexType, typename EdgeType>
size_t MixedGraphMatrix<VertexType, EdgeType>::indegree(
    const VertexType &vertex) const {
  if (!vertexToIndex.count(vertex)) {
    throw std::invalid_argument("Vertex does not exist");
  }

  size_t vertexIndex = vertexToIndex.at(vertex);
  size_t inDegreeCount = 0;

  for (size_t src = 0; src < numVertices; ++src) {
    if (adjacencyMatrix[getIndex(src, vertexIndex)].has_value()) {
      ++inDegreeCount;
    }
  }

  return inDegreeCount;
}

template <typename VertexType, typename EdgeType>
size_t MixedGraphMatrix<VertexType, EdgeType>::outdegree(
    const VertexType &vertex) const {
  if (!vertexToIndex.count(vertex)) {
    throw std::invalid_argument("Vertex does not exist");
  }

  size_t vertexIndex = vertexToIndex.at(vertex);
  size_t outDegreeCount = 0;

  for (size_t dest = 0; dest < numVertices; ++dest) {
    if (adjacencyMatrix[getIndex(vertexIndex, dest)].has_value()) {
      ++outDegreeCount;
    }
  }

  return outDegreeCount;
}

template <typename VertexType, typename EdgeType>
size_t MixedGraphMatrix<VertexType, EdgeType>::totalDegree(
    const VertexType &vertex) const {
  if (!vertexToIndex.count(vertex)) {
    throw std::invalid_argument("Vertex does not exist");
  }

  size_t vertexIndex = vertexToIndex.at(vertex);
  size_t totalDegreeCount = 0;

  for (size_t other = 0; other < numVertices; ++other) {
    auto forwardIndex = getIndex(vertexIndex, other);
    auto backwardIndex = getIndex(other, vertexIndex);

    if (adjacencyMatrix[forwardIndex].has_value()) {
      if (adjacencyMatrix[forwardIndex]->isDirected) {
        ++totalDegreeCount;
      } else {
        ++totalDegreeCount;
      }
    }

    if (adjacencyMatrix[backwardIndex].has_value() &&
        adjacencyMatrix[backwardIndex]->isDirected) {
      ++totalDegreeCount;
    }
  }

  return totalDegreeCount;
}

}; // namespace Appledore