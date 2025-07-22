#include <iostream>
#include <random>
#include <vector>
#include <string_view>
#include <string>
#include "../include/GraphMatrix.hpp"

namespace Appledore {

    // ANSI escape codes for text colors
    constexpr std::string_view ANSI_COLOR_RED = "\x1b[31m";
    constexpr std::string_view ANSI_COLOR_GREEN = "\x1b[32m";
    constexpr std::string_view ANSI_COLOR_YELLOW = "\x1b[33m";
    constexpr std::string_view ANSI_COLOR_BLUE = "\x1b[34m";
    constexpr std::string_view ANSI_COLOR_MAGENTA = "\x1b[35m";
    constexpr std::string_view ANSI_COLOR_CYAN = "\x1b[36m";
    constexpr std::string_view ANSI_COLOR_RESET = "\x1b[0m";

    inline void printColoredText(const std::string& text, std::string_view colorCode) {
        std::cout << colorCode << text << ANSI_COLOR_RESET << '\n';
    }

    template <typename T>
    class custom_vertex_1 : public GraphVertex {
        T vertex_name;

    public:
        std::vector<int> random_data;

        custom_vertex_1(const T& v_name, bool seed_random = false) 
            : vertex_name(v_name) 
        {
            random_data.reserve(20);

            if (seed_random) {
                std::random_device rd;
                std::mt19937 engine(rd());
                std::uniform_int_distribution<int> dist(1, 100);
                for (int i = 0; i < 20; ++i) {
                    random_data.push_back(dist(engine));
                }
            } else {
                for (int i = 1; i <= 20; ++i) {
                    random_data.push_back(i);
                }
            }
        }

        [[nodiscard]] T get_vertex_name() const noexcept {
            return vertex_name;
        }

        void show_random_data() const {
            for (const int val : random_data) {
                std::cout << val << ' ';
            }
            std::cout << '\n';
        }

        bool operator==(const custom_vertex_1& other) const noexcept {
            return vertex_name == other.vertex_name;
        }
    };

    template <typename W>
    class custom_edge_1 : public GraphEdge {
    public:
        W weight;

        explicit custom_edge_1(W w) : weight(w) {}
    };

    // Primitive types for testing/customization
    namespace PrimitiveVertexEdges_T {
        using vertex_primitive_1_t = int;
        using edge_primitive_1_t = float;

        using vertex_primitive_2_t = float;
        using edge_primitive_2_t = double;

        using vertex_primitive_3_t = int;
        using edge_primitive_3_t = char;

        using vertex_primitive_4_t = std::string;
        using edge_primitive_4_t = int;
    }

    namespace CustomVertexEdges_T {
        using CustomVertex_1 = custom_vertex_1<PrimitiveVertexEdges_T::vertex_primitive_1_t>;
        using CustomEdge_1 = custom_edge_1<PrimitiveVertexEdges_T::edge_primitive_1_t>;

        using CustomVertex_2 = custom_vertex_1<PrimitiveVertexEdges_T::vertex_primitive_2_t>;
        using Custom_Edge_2 = custom_edge_1<PrimitiveVertexEdges_T::edge_primitive_2_t>;

        using CustomVertex_3 = custom_vertex_1<PrimitiveVertexEdges_T::vertex_primitive_3_t>;
        using CustomEdge_3 = custom_edge_1<PrimitiveVertexEdges_T::edge_primitive_1_t>;
    }

}
