#include <iostream>
#include <random>
#include <vector>
#include "../include/GraphMatrix.hpp"
using namespace Appledore;

namespace Appledore
{
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
        }
        [[nodiscard]] type_store_data get_vertex_name()
        {
            return vertex_name;
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