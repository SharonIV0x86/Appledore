**📌 Overview**

GraphMatrix.h is a header file that defines the GraphMatrix class, which represents a graph using an adjacency matrix. This data structure is useful for graph-related operations such as:

Adding and removing vertices and edges
Retrieving connectivity information
Efficient traversal and manipulation of graph data
**🔹 Key Features**
Adjacency Matrix Representation: Uses a 2D matrix to store edges.
Supports Weighted and Unweighted Graphs: Can handle edge weights efficiently.
Template-based Design: Allows customization of vertex and edge types.

**📌 Structure of GraphMatrix.h**

**🔹 Templates Used**
template <typename VertexType, typename EdgeType>
class GraphMatrix

VertexType: Represents the type of vertices (e.g., int, std::string).
EdgeType: Represents the type of edge weights (int, double, etc.).

**🔹 Class Definition**
template <typename VertexType, typename EdgeType>
class GraphMatrix {
private:
    std::vector<std::vector<EdgeType>> adjacencyMatrix;
    std::unordered_map<VertexType, int> vertexToIndex;
    std::unordered_map<int, VertexType> indexToVertex;
public:
    void addVertex(const VertexType& vertex);
    void addEdge(const VertexType& src, const VertexType& dest, EdgeType weight);
    bool hasEdge(const VertexType& src, const VertexType& dest);
    EdgeType getEdgeValue(const VertexType& src, const VertexType& dest);
    std::vector<VertexType> getNeighbors(const VertexType& vertex);
};

**🔹 Important Components**
**adjacencyMatrix**	- A 2D vector representing edges between vertices.
**vertexToIndex** - Maps a vertex to its corresponding index in adjacencyMatrix.
**indexToVertex** - Maps an index in adjacencyMatrix back to the corresponding vertex.

📌 How GraphMatrix.h Works

Adding a Vertex:
Assigns an index to the vertex.
Expands the adjacency matrix.
Adding an Edge:
Updates the adjacency matrix with the edge weight.
Retrieving Neighbors:
Uses the adjacency matrix to find connected vertices.

📌 Connections to Other Files
🔹 Dependencies
MixedGraph.h: Uses GraphMatrix as a base class for handling directed and undirected edges.
GraphAlgorithms.h: Uses GraphMatrix to implement shortest path, DFS, BFS, etc.
🔹 Interaction with Other Components
GraphMatrix.h acts as the core data structure for graphs, enabling efficient access and modification of graph-related data.

📌 Visual Representation

🔹 Adjacency Matrix Structure
![Graphical Representation](<assets/Adjacency Matrix Structure.png>)

🔹 Vertex Mapping
![Graphical Representation](<assets/Vertex Mapping.jpg>)

📌 Available Methods
void addVertex(const VertexType& vertex);
void addEdge(const VertexType& src, const VertexType& dest, EdgeType weight);
bool hasEdge(const VertexType& src, const VertexType& dest);
EdgeType getEdgeValue(const VertexType& src, const VertexType& dest);
std::vector<VertexType> getNeighbors(const VertexType& vertex);
