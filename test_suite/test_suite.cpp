#include "../include/GraphMatrix.hpp"
#include <iostream>
#include "tests_GraphMatrix.hpp"

int main(int argc, char *argv[])
{
    if (argc > 1 && std::string(argv[1]) == "graph-matrix")
    {
        C_TestGraphMatrix test1;
        test1.create_graph();
        test1.init_tests();
        test1.show_vertex_data();
    }
    else
    {
        std::cout << "Usage: " << argv[0] << " graph-matrix" << std::endl;
    }

    return 0;
}