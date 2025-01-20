# MixedGraph.h Documentation

## Overview of `MixedGraph.h`
- **Purpose**:  
  `MixedGraph.h` defines the `MixedGraph` class for representing a graph with multiple edge types (e.g., directed, undirected). It extends the basic graph structure provided by `GraphMatrix.h` by adding flexibility for handling various edge types.

- **Key Functionality**:  
  This file allows users to define graphs with mixed edges, using adjacency matrices for graph representation but also handling edge properties (e.g., direction, weight).

- **Structure**:  
  Similar to `GraphMatrix.h`, this file contains class declarations and functions. However, it adds more flexibility for edge types and may include additional data structures for storing edge properties.

- **Role in the Library**:  
  This file builds upon `GraphMatrix.h` by introducing more sophisticated handling for mixed-edge graphs.

### Components
- **Classes & Structures**:
  - `MixedGraph`: A class that extends `GraphMatrix` to handle mixed edge types.
  
  - **Data Structures**:
    - `adjacencyMatrix`: A matrix that may hold different edge properties (e.g., directed, undirected, weighted).
    - `edgeTypeMap`: A mapping that defines the type of each edge.

- **Template Parameters**:  
  Describe any template parameters, especially if the graph uses custom edge types.

- **Function Signatures**:
  - `void addDirectedEdge(const std::string &from, const std::string &to);`
  - `void addUndirectedEdge(const std::string &v1, const std::string &v2);`

### Interaction with `GraphMatrix.h`
- **MixedGraph & GraphMatrix Integration**:  
  `MixedGraph.h` can use the adjacency matrix functionality from `GraphMatrix.h` while introducing more flexibility in edge handling (e.g., supporting both directed and undirected edges).

## Visual Explanations

### Diagram 1: Structure of Mixed-Edge Adjacency Matrix
- A visual diagram showing the structure of an adjacency matrix in a mixed-edge graph.

### Diagram 2: Mixed Graph Edges and Types
- A visual diagram showing how `edgeTypeMap` works and how edges can have different properties (directed, undirected, weighted).

