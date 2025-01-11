#include <iostream>
#include <vector>
#include <optional>
#include <unordered_map>
#include <stdexcept>
#include <string>

namespace Appledore {

    template <typename VertexType, typename EdgeType>
    class MixedGraphMatrix {
    public:
        void addVertex(const VertexType &vertex);
        void addEdge(const VertexType &src, const VertexType &dest, std::optional<EdgeType> edgeValue = std::nullopt, bool isDirected = false);
        void addEdge(const VertexType &src, const VertexType &dest, EdgeType edge, bool isDirected = false);

        size_t indegree(const VertexType &vertex) const;
        size_t outdegree(const VertexType &vertex) const;
        size_t totalDegree(const VertexType &vertex) const;

    private:
        struct EdgeInfo {
            EdgeType value;
            bool isDirected;

            EdgeInfo(EdgeType value, bool isDirected)
                : value(value), isDirected(isDirected) {}
        };

        std::unordered_map<VertexType, size_t> vertexToIndex;

        // Workaround for potential template parsing issues
        using OptionalEdgeInfo = std::optional<EdgeInfo<EdgeType>>;

        std::vector<OptionalEdgeInfo> adjacencyMatrix;

        size_t numVertices = 0;

        size_t getIndex(size_t src, size_t dest) const {
            return src * numVertices + dest;
        }
    };

}  // namespace Appledore
