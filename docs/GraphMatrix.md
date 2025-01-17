# GraphMatrix.h Documentation

## Overview of `GraphMatrix.h`
- **Purpose**:  
  `GraphMatrix.h` defines the `GraphMatrix` class for representing a graph using an adjacency matrix. It provides functions for adding/removing edges, checking for edge existence, and querying adjacency relationships.

- **Key Functionality**:  
  This file enables users to work with graphs using matrix representations, making graph operations like edge addition/removal and checking adjacency efficient.

- **Structure**:  
  The file includes class declarations, member functions, and utility functions for manipulating an adjacency matrix. It also defines mappings for vertex-to-index and index-to-vertex conversions.

- **Role in the Library**:  
  The file serves as the core for representing graphs with adjacency matrices. It is used for efficient graph operations, particularly when dealing with sparse graphs.

### Components
- **Classes & Structures**:
  - `GraphMatrix`: Represents the graph using an adjacency matrix.
  
  - **Data Structures**:
    - `adjacencyMatrix`: A 2D matrix (e.g., `std::vector<std::vector<bool>>`) representing the adjacency between vertices.
    - `vertexToIndex`: A mapping of vertex labels (e.g., `std::map<std::string, size_t>`) to matrix indices.
    - `indexToVertex`: A reverse mapping of indices back to vertex labels.

- **Template Parameters**:  
  If there are any, describe the template parameters used, such as the data type of the edges or vertices.

- **Function Signatures**:
  - `void addEdge(const std::string &v1, const std::string &v2);`
  - `bool hasEdge(const std::string &v1, const std::string &v2) const;`
  - `size_t getVertexIndex(const std::string &vertex) const;`

### Adjacency Matrix Structure
- **Description**:  
  The adjacency matrix is a 2D structure where each cell `(i, j)` indicates the presence (or weight) of an edge between the vertex corresponding to index `i` and vertex corresponding to index `j`.

- **Implementation**:  
  The matrix is typically a `std::vector<std::vector<bool>>` or `std::vector<std::vector<int>>` in C++.

### Vertex to Index Mappings
- **`vertexToIndex`**:  
  Maps vertex labels to matrix indices.
  
- **`indexToVertex`**:  
  Maps matrix indices to vertex labels.

## Connections
- **Related Files**:  
  - `MixedGraph.h`: A file for handling more complex graphs, which may include both directed and undirected edges.

  - **Interaction**:  
    `GraphMatrix.h` provides the matrix-based graph functionality, and `MixedGraph.h` can extend it with additional edge types and properties.

## Visual Explanations

### Diagram 1: Structure of Adjacency Matrix
- A visual diagram showing the structure of the adjacency matrix.

### Diagram 2: Vertex-to-Index Mapping
- A visual diagram explaining how `vertexToIndex` and `indexToVertex` work.

