#pragma once
#include "MatrixRep.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <optional>
#include <set>
#include <stack>
#include <stdexcept>
#include <vector>
namespace Appledore {

// GraphMatrix class template
template <typename VertexType, typename EdgeType, typename Direction>
class GraphMatrix
    : public Appledore::MatrixRepresentation<VertexType, EdgeType> {
public:
  GraphMatrix()
      : isDirected(std::is_same_v<Direction, DirectedG>),
        isWeighted(!std::is_same_v<EdgeType, UnweightedG>) {}

  template <typename... Vertices> void addVertex(Vertices &&...vertices) {
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

  bool operator()(const VertexType &src, const VertexType &dest) {
    if (!vertexToIndex.count(src) || !vertexToIndex.count(dest)) {
      return false;
    }

    size_t srcIndex = vertexToIndex[src];
    size_t destIndex = vertexToIndex[dest];

    if (adjacencyMatrix[getIndex(srcIndex, destIndex)].has_value()) {
      return true;
    } else {
      return false;
    }
  }

  // for weighted.
  void addEdge(const VertexType &src, const VertexType &dest,
               const EdgeType &edge) {
    if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
      throw std::invalid_argument("One or both vertices do not exist");

    size_t srcIndex = vertexToIndex.at(src);
    size_t destIndex = vertexToIndex.at(dest);

    adjacencyMatrix[getIndex(srcIndex, destIndex)] = EdgeInfo<EdgeType>(edge);

    if (!isDirected) {
      adjacencyMatrix[getIndex(destIndex, srcIndex)] = EdgeInfo<EdgeType>(edge);
    }
  }

  // for unweighted
  void addEdge(const VertexType &src, const VertexType &dest) {
    if (!vertexToIndex.count(src) || !vertexToIndex.count(dest)) {
      throw std::invalid_argument("One or both vertices do not exist");
    }

    size_t srcIndex = vertexToIndex.at(src);
    size_t destIndex = vertexToIndex.at(dest);

    adjacencyMatrix[getIndex(srcIndex, destIndex)] = EdgeInfo<EdgeType>();

    if (!isDirected) {
      adjacencyMatrix[getIndex(destIndex, srcIndex)] = EdgeInfo<EdgeType>();
    }
  }

  // Remove edge
  void removeEdge(const VertexType &src, const VertexType &dest) {
    if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
      throw std::invalid_argument("One or both vertices do not exist");

    size_t srcIndex = vertexToIndex.at(src);
    size_t destIndex = vertexToIndex.at(dest);

    adjacencyMatrix[getIndex(srcIndex, destIndex)] = std::nullopt;

    if (!isDirected) {
      adjacencyMatrix[getIndex(destIndex, srcIndex)] = std::nullopt;
    }
  }

  // Check if edge exists
  bool hasEdge(const VertexType &src, const VertexType &dest) const {
    if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
      throw std::invalid_argument("One or both vertices do not exist");

    size_t srcIndex = vertexToIndex.at(src);
    size_t destIndex = vertexToIndex.at(dest);

    return adjacencyMatrix[getIndex(srcIndex, destIndex)].has_value();
  }

  // Get vertices
  const std::vector<VertexType> &getVertices() const { return indexToVertex; }

  const EdgeType &getEdge(const VertexType &src, const VertexType &dest) const {
    if (!vertexToIndex.count(src) || !vertexToIndex.count(dest)) {
      throw std::invalid_argument("One or both vertices do not exist!");
    }
    size_t srcIndex = vertexToIndex.at(src);
    size_t destIndex = vertexToIndex.at(dest);

    auto &edgeValue = adjacencyMatrix[getIndex(srcIndex, destIndex)];

    if (edgeValue.has_value()) {
      return edgeValue.value().value;
    } else {
      throw std::runtime_error("No Edge exists between the given vertices.");
    }
  }

  // Get all edges
  std::vector<std::tuple<VertexType, VertexType, EdgeType>> getAllEdges(
      std::optional<bool> returnSorted = std::nullopt,
      std::function<bool(const std::tuple<VertexType, VertexType, EdgeType> &,
                         const std::tuple<VertexType, VertexType, EdgeType> &)>
          customPredicate = nullptr) const {
    if (!isWeighted)
      throw std::invalid_argument("Given Graph must be Weighted.");
    // Collect all edges
    std::vector<std::tuple<VertexType, VertexType, EdgeType>> edges;

    for (size_t srcIndex = 0; srcIndex < numVertices; ++srcIndex) {
      for (size_t destIndex = 0; destIndex < numVertices; ++destIndex) {
        const std::optional<EdgeInfo<EdgeType>> &edgeValue =
            adjacencyMatrix[getIndex(srcIndex, destIndex)];
        if (edgeValue.has_value()) {
          edges.emplace_back(indexToVertex[srcIndex], indexToVertex[destIndex],
                             edgeValue.value().value);
        }
      }
    }

    constexpr bool isArithmetic = std::is_arithmetic_v<EdgeType>;

    if (!returnSorted.has_value() && customPredicate == nullptr) {
      return edges;
    }

    if (customPredicate) {
      std::sort(edges.begin(), edges.end(), customPredicate);
    } else if (returnSorted.has_value()) {
      if (!isArithmetic) {
        throw std::invalid_argument(
            "Automatic sorting requires EdgeType to be arithmetic.");
      }

      std::sort(edges.begin(), edges.end(),
                [returnSorted](const auto &a, const auto &b) {
                  return returnSorted.value()
                             ? (std::get<2>(a) < std::get<2>(b))
                             : (std::get<2>(a) > std::get<2>(b));
                });
    }

    return edges;
  }

  [[nodiscard]] size_t indegree(const VertexType &vertex) const {
    if (!vertexToIndex.count(vertex)) {
      throw std::invalid_argument("Vertex does not exist in the graph");
    }
    if (!isDirected) {
      std::cerr << "\nIndegree is not defined for undirected graphs. Returning "
                   "Total Degree\n";
      return totalDegree(vertex);
    }
    size_t vertexIndex = vertexToIndex.at(vertex);
    size_t indegree = 0;
    for (size_t srcIndex = 0; srcIndex < numVertices; ++srcIndex) {
      if (adjacencyMatrix[getIndex(srcIndex, vertexIndex)].has_value()) {
        indegree++;
      }
    }
    return indegree;
  }
  [[nodiscard]] size_t outdegree(const VertexType &vertex) const {
    if (!vertexToIndex.count(vertex)) {
      throw std::invalid_argument("Vertex does not exist in the graph");
    }
    if (!isDirected) {
      std::cerr << "\nOutdegree is not defined for undirected graphs. "
                   "Returning total degree\n";
      return totalDegree(vertex);
    }
    size_t vertexIndex = vertexToIndex.at(vertex);
    size_t outdegree = 0;
    for (size_t destIndex = 0; destIndex < numVertices; ++destIndex) {
      if (adjacencyMatrix[getIndex(vertexIndex, destIndex)].has_value()) {
        outdegree++;
      }
    }
    return outdegree;
  }
  [[nodiscard]] size_t totalDegree(const VertexType &vertex) const {
    if (!vertexToIndex.count(vertex)) {
      throw std::invalid_argument("Vertex does not exist in the graph");
    }
    if (isDirected)
      return indegree(vertex) + outdegree(vertex);

    size_t vertexIndex = vertexToIndex.at(vertex);
    size_t totaldegree = 0;
    for (size_t srcIndex = 0; srcIndex < numVertices; ++srcIndex) {
      if (adjacencyMatrix[getIndex(srcIndex, vertexIndex)].has_value()) {
        totaldegree++;
      }
    }
    return totaldegree;
  }
  void __show_states() {
    std::cout << "State of Index to index: ";
    for (size_t i = 0; i < indexToVertex.size(); ++i) {
      std::cout << indexToVertex[i] << " ";
    }
    std::cout << "\nState of Vertex to index: \n";
    for (const auto &[first, second] : vertexToIndex) {
      std::cout << first << " -> " << second << "\n";
    }
    std::cout << "\n Adjacency Matrix: \n";
    for (size_t i = 0; i < numVertices; ++i) {
      for (size_t j = 0; j < numVertices; ++j) {
        if (adjacencyMatrix[getIndex(i, j)].has_value()) {
          std::cout << " 1 ";
        } else {
          std::cout << " 0 ";
        }
      }
      std::cout << "\n";
    }
  }
  std::set<VertexType> getNeighbors(const VertexType &vertex) const {
    if (!vertexToIndex.count(vertex)) {
      throw std::invalid_argument("Vertex does not exist in the graph");
    }

    size_t vertexIndex = vertexToIndex.at(vertex);

    std::set<VertexType> neighbors;

    for (size_t destIndex = 0; destIndex < numVertices; ++destIndex) {
      if (adjacencyMatrix[getIndex(vertexIndex, destIndex)].has_value()) {
        neighbors.insert(indexToVertex[destIndex]);
      }

      if (!isDirected &&
          adjacencyMatrix[getIndex(destIndex, vertexIndex)].has_value()) {
        neighbors.insert(indexToVertex[destIndex]);
      }
    }

    return neighbors;
  }

  std::vector<std::vector<VertexType>>
  findAllPaths(const VertexType &src, const VertexType &dest, size_t pl = 0) {
    if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
      throw std::invalid_argument("One or both vertices do not exist");

    if (pl < 0)
      throw std::invalid_argument("Path limit must be a non-negative integer!");

    if (pl > 0) {
      size_t totalPaths = countPathsDFS(src, dest);
      if (pl > totalPaths)
        throw std::invalid_argument(
            "Path limit exceeds the total number of possible paths");
    }

    std::vector<std::vector<VertexType>> allPaths;
    std::stack<std::pair<VertexType, std::vector<VertexType>>> stack;

    stack.push({src, {src}});

    while (!stack.empty()) {
      std::pair<VertexType, std::vector<VertexType>> currentElement =
          stack.top();
      stack.pop();

      VertexType current = currentElement.first;
      std::vector<VertexType> currentPath = currentElement.second;

      if (current == dest) {
        allPaths.push_back(currentPath);

        if (pl > 0 && allPaths.size() >= pl) {
          break;
        }
      } else {
        size_t currentIndex = vertexToIndex.at(current);
        for (size_t i = 0; i < numVertices; ++i) {
          if (adjacencyMatrix[getIndex(currentIndex, i)].has_value()) {
            VertexType nextVertex = indexToVertex[i];
            bool vertexInPath = false;
            for (const auto &pathVertex : currentPath) {
              if (pathVertex == nextVertex) {
                vertexInPath = true;
                break;
              }
            }

            if (!vertexInPath) {
              auto newPath = currentPath;
              newPath.push_back(nextVertex);
              stack.push({nextVertex, newPath});
            }
          }
        }
      }
    }

    return allPaths;
  }

  [[nodiscard]] double density() const {
    if (numVertices <= 1) {
      return 0.0;
    }

    size_t edgeCount = 0;
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
      if (adjacencyMatrix[i].has_value()) {
        edgeCount++;
      }
    }

    if (!isDirected) {
      edgeCount /= 2;
    }

    double denominator = static_cast<double>(numVertices) * (numVertices - 1);
    double numerator = isDirected ? static_cast<double>(edgeCount)
                                  : 2.0 * static_cast<double>(edgeCount);

    return numerator / denominator;
  }

  [[nodiscard]] bool isConnected() const {
    if (numVertices == 0)
      return true;
    if (isDirected)
      return false;
    std::vector<bool> visited(numVertices, false);
    dfsforConnectivity(0, visited);
    return std::all_of(visited.begin(), visited.end(),
                       [](bool v) { return v; });
  }

  size_t countPathsDFS(const VertexType &src, const VertexType &dest) {
    if (!vertexToIndex.count(src) || !vertexToIndex.count(dest))
      throw std::invalid_argument("One or both vertices do not exist");

    std::stack<std::pair<VertexType, std::vector<VertexType>>> stack;

    stack.push({src, {src}});

    size_t pathCount = 0;

    while (!stack.empty()) {
      std::pair<VertexType, std::vector<VertexType>> currentElement =
          stack.top();
      stack.pop();

      VertexType current = currentElement.first;
      std::vector<VertexType> currentPath = currentElement.second;

      if (current == dest) {
        pathCount++;
      } else {
        size_t currentIndex = vertexToIndex[current];
        for (size_t i = 0; i < numVertices; ++i) {
          if (adjacencyMatrix[getIndex(currentIndex, i)].has_value()) {
            VertexType nextVertex = indexToVertex[i];
            bool vertexInPath = false;
            for (const auto &pathVertex : currentPath) {
              if (pathVertex == nextVertex) {
                vertexInPath = true;
                break;
              }
            }

            if (!vertexInPath) {
              auto newPath = currentPath;
              newPath.push_back(nextVertex);
              stack.push({nextVertex, newPath});
            }
          }
        }
      }
    }

    return pathCount;
  }

  void dfsforConnectivity(size_t start, std::vector<bool> &visited) const {
    std::stack<size_t> stack;
    stack.push(start);

    while (!stack.empty()) {
      size_t current = stack.top();
      stack.pop();

      if (!visited[current]) {
        visited[current] = true;

        for (size_t dest = 0; dest < numVertices; ++dest) {
          if (adjacencyMatrix[getIndex(current, dest)].has_value() &&
              !visited[dest]) {
            stack.push(dest);
          }
        }
      }
    }
  }

  void removeVertex(const VertexType &vert) {

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

  [[nodiscard]] std::vector<VertexType> getIsolated() const {
    if (numVertices == 0) {
      throw std::runtime_error("Graph is empty. No vertices available.");
    }

    std::vector<VertexType> isolatedVertices;

    for (const auto &vertex : indexToVertex) {
      if (vertexToIndex.find(vertex) == vertexToIndex.end()) {
        throw std::invalid_argument("Vertex does not exist in the graph.");
      }

      if (totalDegree(vertex) == 0) {
        isolatedVertices.push_back(vertex);
      }
    }

    return isolatedVertices;
  }

  void updateEdge(const VertexType &src, const VertexType &dest,
                  const EdgeType &newEdgeValue) {
    if (!isWeighted) {
      throw std::logic_error("Cannot update an edge in an unweighted graph.");
    }

    if (!vertexToIndex.count(src) || !vertexToIndex.count(dest)) {
      throw std::invalid_argument("One or both vertices do not exist.");
    }

    size_t srcIndex = vertexToIndex.at(src);
    size_t destIndex = vertexToIndex.at(dest);

    std::optional<EdgeInfo<EdgeType>> edgeInfo =
        adjacencyMatrix[getIndex(srcIndex, destIndex)];
    if (!edgeInfo.has_value()) {
      throw std::runtime_error(
          "No edge exists between the specified vertices.");
    }

    edgeInfo = EdgeInfo<EdgeType>(newEdgeValue);

    if (!isDirected) {
      adjacencyMatrix[getIndex(destIndex, srcIndex)] =
          EdgeInfo<EdgeType>(newEdgeValue);
    }
  }

private:
  std::unordered_map<VertexType, size_t, VertexHasher<VertexType>>
      vertexToIndex;
  std::vector<VertexType> indexToVertex;
  std::vector<std::optional<EdgeInfo<EdgeType>>> adjacencyMatrix;
  size_t numVertices = 0;
  bool isDirected;
  bool isWeighted;

  inline size_t getIndex(size_t src, size_t dest) const {
    return src * numVertices + dest;
  }
};
} // namespace Appledore
