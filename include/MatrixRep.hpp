#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>
#include <optional>
#include <map>
#include <stack>
#include <algorithm>
#include <set>

namespace Appledore
{
    struct DirectedG
    {
    };
    struct UndirectedG
    {
    };
    struct UnweightedG
    {
    };
    class GraphVertex
    {
    public:
        size_t id;
        static size_t nextId;

        GraphVertex()
        {
            id = nextId++;
        }

        bool operator<(const GraphVertex &other) const
        {
            return id < other.id;
        }
        bool operator==(const GraphVertex &other) const
        {
            return id == other.id;
        }

        friend std::ostream& operator<<(std::ostream& src, const GraphVertex& other) {
            src << "Vertex " << other.id;
            return src;
        }
    };
    size_t Appledore::GraphVertex::nextId = 1;
    class GraphEdge
    {
    public:
        size_t id;
        static size_t nextId;

        GraphEdge()
        {
            id = nextId++;
        }

        bool operator<(const GraphEdge &other) const
        {
            return id < other.id;
        }
        bool operator>(const GraphEdge &other) const
        {
            return id > other.id;
        }
        bool operator==(const GraphEdge &other) const
        {
            return id == other.id;
        }
    };
    size_t Appledore::GraphEdge::nextId = 1;
    class MatrixRepresentation{
        //common methods.
    };

}