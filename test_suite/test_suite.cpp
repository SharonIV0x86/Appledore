#include "../include/GraphMatrix.hpp"
#include <iostream>
#include "tests_GraphMatrix.hpp"

int main(int argc, char *argv[])
{
    if (argc > 1 && std::string(argv[1]) == "graph-matrix")
    {
        Appledore::C_TestGraphMatrix tester;
        tester.create_graph();
        tester.init_tests();
        tester.show_vertex_data();
    }
    else
    {
        std::cout << "Usage: " << argv[0] << " graph-matrix" << std::endl;
    }

    return 0;
}