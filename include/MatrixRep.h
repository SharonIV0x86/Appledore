#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>
#include <optional>
#include <map>
#include <stack>
#include <algorithm>
#include <set>


namespace Appledore{
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
    };
    size_t Appledore::GraphVertex::nextId = 1;
    class MatrixRepresentation{
        //common methods goes here.
    };
}