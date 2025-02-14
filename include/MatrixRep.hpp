#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>
#include <optional>
#include <map>
#include <stack>
#include <algorithm>
#include <set>
#include <random>
#include <chrono>
#include <sstream>
namespace Appledore
{
    struct DirectedG{};
    struct UndirectedG{};
    struct UnweightedG{};

    std::string __generate_vertex_name()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        const std::string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        const size_t name_length = 10;
        std::uniform_int_distribution<> dist(0, charset.size() - 1);
        std::stringstream ss;
        for (size_t i = 0; i < name_length; ++i)
        {
            ss << charset[dist(gen)];
        }
        auto now = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
        ss << "_" << duration;
        return ss.str();
    }
    class GraphVertex
    {
    public:
        size_t __id_;
        static size_t nextId;
        std::string __v___name;

        GraphVertex()
        {
            __id_ = nextId++;
            __v___name = __generate_vertex_name();
        }
        GraphVertex(std::string vertexName) : __v___name{vertexName} {};

        bool operator<(const GraphVertex &other) const
        {
            return __id_ < other.__id_;
        }
        bool operator==(const GraphVertex &other) const
        {
            return __id_ == other.__id_;
        }
    };
    size_t Appledore::GraphVertex::nextId = 1;
    class GraphEdge
    {
    public:
        size_t __id_;
        static size_t nextId;
        std::string __e___name;
        GraphEdge()
        {
            __id_ = nextId++;
            __e___name = __generate_vertex_name();
        }
        GraphEdge(std::string edge_name): __e___name{edge_name}{};

        bool operator<(const GraphEdge &other) const
        {
            return __id_ < other.__id_;
        }
        bool operator>(const GraphEdge &other) const
        {
            return __id_ > other.__id_;
        }
        bool operator==(const GraphEdge &other) const
        {
            return __id_ == other.__id_;
        }
    };
    size_t Appledore::GraphEdge::nextId = 1;
    template<typename VertexType, typename EdgeType>
    class MatrixRepresentation
    {
        // common methods.
    };
    template <typename EdgeType>
    struct EdgeInfo
    {
        EdgeType value;
        bool isDirected;

        EdgeInfo() : value(), isDirected(false) {}
        EdgeInfo(const EdgeType &value, bool isDirected = false)
            : value(value), isDirected(isDirected) {}
    };

}