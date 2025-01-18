# **📌 Overview**

``GraphMatrix.h`` is a header file that defines the GraphMatrix class, which represents a graph using an adjacency matrix. This data structure is useful for graph-related operations such as:

- Adding and removing vertices and edges
- Retrieving connectivity information
- Efficient traversal and manipulation of graph data


**🔹 Key Features**
Adjacency Matrix Representation: Uses a 1D matrix flattened as 2D matrix to store edges.
Supports Weighted and Unweighted Graphs along: Can handle edge weights efficiently.
Template-based Design: Allows customization of vertex and edge types.

# **📌 Structure of GraphMatrix.h**

### **🔹 Templates Used**
```cpp
template <typename VertexType, typename EdgeType>
class GraphMatrix {}
```
VertexType: Represents the type of vertices (e.g., int, std::string).
EdgeType: Represents the type of edge weights (int, double, etc.).

### **🔹 Class Definition**
```cpp
template <typename VertexType, typename EdgeType>
class GraphMatrix {
private:

    std::map<VertexType, size_t> vertexToIndex;
    std::vector<VertexType> indexToVertex;
    std::vector<std::optional<EdgeInfo<EdgeType>>> adjacencyMatrix;
    size_t numVertices = 0;
    bool isDirected;
    bool isWeighted;
public:
    void addVertex(const VertexType& vertex);
    void addEdge(const VertexType& src, const VertexType& dest, EdgeType weight);
    bool hasEdge(const VertexType& src, const VertexType& dest);
    EdgeType getEdgeValue(const VertexType& src, const VertexType& dest);
    std::vector<VertexType> getNeighbors(const VertexType& vertex);
    ...
};
```
# **🔹 Important Components**
### 1. **adjacencyMatrix**
The ``adjacencyMatrix`` is a 1-Dimensional Vector that is being viewed as a 2-Dimensional vector by using a formula to calculate offsets to store values. Each value in the ``adjacencyMatrix`` is a ``std::optional`` value which means each element can have a value of ``EdgeInfo`` struct type or each element can be a ``std::nullopt`` signifying that there is no value present.


### 2. **``numVertices``**
This variable is maintained as private member to indicate the number of vertices which are currently present in a graph.

### 3. ``isDirected`` and ``isWeighted``
These two variables are also private, they are used to determine about the directionality and weightedness of a graph.

### 4. **vertexToIndex** 
Maps a vertex to its corresponding index for faster lookups using a ``std::map``.
### 5. **indexToVertex**  
Maps a index to each of the vertex in the order they are inserted.

### How are ``indexToVertex`` and ``vertexToIndex`` related?
Consider a graph as empty, and suppose if you add a vertex **"A"** the vertex is first added to the last index of the ``indexToVertex`` in this case the **"A"** is saved at 0th index. And in ``vertexToIndex`` the integer index corresponding to vertex **"A"** is 0.


# 📌 How GraphMatrix.h Works

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
