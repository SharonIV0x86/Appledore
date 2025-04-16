#include <gtest/gtest.h>
#include "GraphMatrix.hpp"

class GraphMatrixTest : public ::testing::Test {
protected:
    GraphMatrix<int> graph;

    void SetUp() override {
        // Create a sample graph for testing
        graph.addVertex(1);
        graph.addVertex(2);
        graph.addVertex(3);
        graph.addEdge(1, 2, 5);
        graph.addEdge(2, 3, 10);
    }
};

// Test getEdge function
TEST_F(GraphMatrixTest, GetEdge) {
    EXPECT_EQ(graph.getEdge(1, 2), 5);
    EXPECT_EQ(graph.getEdge(2, 3), 10);
    EXPECT_EQ(graph.getEdge(1, 3), -1);  // Edge doesn't exist
}

// Test findAllPaths function
TEST_F(GraphMatrixTest, FindAllPaths) {
    auto paths = graph.findAllPaths(1, 3);
    ASSERT_FALSE(paths.empty());
    EXPECT_EQ(paths.size(), 1);
    EXPECT_EQ(paths[0], std::vector<int>({1, 2, 3}));
}

// Test isConnected function
TEST_F(GraphMatrixTest, IsConnected) {
    EXPECT_TRUE(graph.isConnected(1, 3)); // 1 → 2 → 3
    EXPECT_FALSE(graph.isConnected(3, 1)); // No reverse path
}

// Test removeVertex function
TEST_F(GraphMatrixTest, RemoveVertex) {
    graph.removeVertex(2);
    EXPECT_EQ(graph.getEdge(1, 2), -1);
    EXPECT_EQ(graph.getEdge(2, 3), -1);
    EXPECT_FALSE(graph.isConnected(1, 3));
}

// Test getIsolated function
TEST_F(GraphMatrixTest, GetIsolated) {
    graph.addVertex(4);
    auto isolated = graph.getIsolated();
    EXPECT_EQ(isolated.size(), 1);
    EXPECT_EQ(isolated[0], 4);
}

