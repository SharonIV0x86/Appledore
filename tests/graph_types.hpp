#include <iostream>
#include <random>
#include <vector>
#include "../include/GraphMatrix.hpp"
using namespace Appledore;

namespace Appledore
{
    // ANSI escape codes for text colors
    constexpr std::string_view ANSI_COLOR_RED = "\x1b[31m";
    constexpr std::string_view ANSI_COLOR_GREEN = "\x1b[32m";
    constexpr std::string_view ANSI_COLOR_YELLOW = "\x1b[33m";
    constexpr std::string_view ANSI_COLOR_BLUE = "\x1b[34m";
    constexpr std::string_view ANSI_COLOR_MAGENTA = "\x1b[35m";
    constexpr std::string_view ANSI_COLOR_CYAN = "\x1b[36m";
    constexpr std::string_view ANSI_COLOR_RESET = "\x1b[0m"; // escape code to reset the color after printing the colored text
    // string_view provides a lightweight object that offers read-only access to a string or a part of a string
    inline void printColoredText(std::string text, std::string_view colorCode)
    {
        std::cout << colorCode << text << ANSI_COLOR_RESET;
    }
    template <typename type_store_data>
    class custom_vertex_1 : public GraphVertex
    {
        type_store_data vertex_name;

    public:
        std::vector<int> random_data;
        custom_vertex_1(type_store_data v_name, bool seed_random = false)
        {
            vertex_name = v_name;
            if (seed_random)
            {
                std::random_device rd;
                std::mt19937 engine(rd());
                std::uniform_int_distribution<int> dist(1, 100);

                for (int i = 0; i < 20; ++i)
                {
                    random_data.push_back(dist(engine));
                }
            }
            else
            {
                for (int i = 0; i < 20; i++)
                    random_data.push_back(i + 1);
            }
        }
        [[nodiscard]] type_store_data get_vertex_name()
        {
            return vertex_name;
        }
        void show_random_data()
        {
            for (const auto &ae : random_data)
            {
                std::cout << ae << " ";
            }
        }
    };
    template <typename weight_type>
    class custom_edge_1 : public GraphEdge
    {
    public:
        weight_type weight;
        custom_edge_1(weight_type w) : weight(w) {};
    };

    // helper types for future dev, not being used as of now.
    namespace PrimitiveVertexEdges_T
    {

        using vertex_primitive_1_t = int;
        using edge_primitive_1_t = float;

        using vertex_primitive_2_t = float;
        using edge_primitive_2_t = double;

        using vertex_primitive_3_t = int;
        using edge_primitive_3_t = char;

        using vertex_primitive_4_t = std::string;
        using edge_primitive_4_t = int;
    }

    namespace CustomVertexEdges_T
    {

        using CustomVertex_1 = custom_vertex_1<PrimitiveVertexEdges_T::vertex_primitive_1_t>;
        using CustomEdge_1 = custom_edge_1<PrimitiveVertexEdges_T::edge_primitive_1_t>;

        using CustomVertex_2 = custom_vertex_1<PrimitiveVertexEdges_T::vertex_primitive_2_t>;
        using Custom_Edge_2 = custom_edge_1<PrimitiveVertexEdges_T::edge_primitive_2_t>;

        using CustomVertex_3 = custom_vertex_1<PrimitiveVertexEdges_T::vertex_primitive_3_t>;
        using CustomEdge_3 = custom_edge_1<PrimitiveVertexEdges_T::edge_primitive_1_t>;
    }

}