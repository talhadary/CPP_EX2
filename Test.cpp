#include "doctest.h"
#include "Graph.hpp"
#include <sstream>
#include <chrono>
#include <limits>

using namespace ariel;

TEST_CASE("Test loading graph and basic properties")
{
    // Test loading a graph and basic properties
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(g.getGraph() == graph);
    CHECK(g.getVertices() == 3);
    CHECK(g.getEdges() == 4);
}

TEST_CASE("Test loading empty graph")
{
    // Test loading an empty graph
    Graph g;
    vector<vector<int>> empty_graph;
    CHECK_THROWS(g.loadGraph(empty_graph));
}

TEST_CASE("Test loading non-square graph")
{
    // Test loading a non-square graph
    Graph g;
    vector<vector<int>> non_square_graph = {
        {0, 1, 0},
        {1, 0, 1}};
    CHECK_THROWS(g.loadGraph(non_square_graph));
}

TEST_CASE("Test addGraphs method")
{
    // Test addGraphs method
    Graph g1, g2;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 0},
        {1, 0, 0}};
    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    g1.addGraphs(g2);
    vector<vector<int>> expected_result = {
        {0, 2, 1},
        {2, 0, 1},
        {1, 1, 0}};
    CHECK(g1.getGraph() == expected_result);
}

TEST_CASE("Test subtractGraphs method")
{
    // Test subtractGraphs method
    Graph g1, g2;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 0},
        {1, 0, 0}};
    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    g1.subtractGraphs(g2);
    vector<vector<int>> expected_result = {
        {0, 0,-1},
        {0, 0, 1},
        {-1, 1, 0}};
    CHECK(g1.getGraph() == expected_result);
}

TEST_CASE("Test inPlaceAdd method")
{
    // Test inPlaceAdd method
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    g.inPlaceAdd(5);
    vector<vector<int>> expected_result = {
        {5, 6, 5},
        {6, 5, 6},
        {5, 6, 5}};
    CHECK(g.getGraph() == expected_result);
}

TEST_CASE("Test inPlaceSubtract method")
{
    // Test inPlaceSubtract method
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    g.inPlaceSubtract(1);
    vector<vector<int>> expected_result = {
        {-1, 0, -1},
        {0, -1, 0},
        {-1, 0, -1}};
    CHECK(g.getGraph() == expected_result);
}

TEST_CASE("Test increment method")
{
    // Test increment method
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    g.increment();
    vector<vector<int>> expected_result = {
        {1, 2, 1},
        {2, 1, 2},
        {1, 2, 1}};
    CHECK(g.getGraph() == expected_result);
}

TEST_CASE("Test decrement method")
{
    // Test decrement method
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    g.decrement();
    vector<vector<int>> expected_result = {
        {-1, 0, -1},
        {0, -1, 0},
        {-1, 0, -1}};
    CHECK(g.getGraph() == expected_result);
}

TEST_CASE("Test unaryPlus method")
{
    // Test unaryPlus method
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    g.unaryPlus(); // Should not change the graph
    CHECK(g.getGraph() == graph);
}

TEST_CASE("Test unaryMinus method")
{
    // Test unaryMinus method
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    g.unaryMinus();
    vector<vector<int>> expected_result = {
        {0, -1, 0},
        {-1, 0, -1},
        {0, -1, 0}};
    CHECK(g.getGraph() == expected_result);
}

TEST_CASE("Test scalarMultiply method")
{
    // Test scalarMultiply method
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    g.scalarMultiply(3);
    vector<vector<int>> expected_result = {
        {0, 3, 0},
        {3, 0, 3},
        {0, 3, 0}};
    CHECK(g.getGraph() == expected_result);
}

TEST_CASE("Test performance of graph operations")
{
    // Test performance for large graphs
    Graph g8, g9;
    const int size = 1000;
    vector<vector<int>> large_graph(size, vector<int>(size, 1)); // 1000x1000 matrix filled with ones
    g8.loadGraph(large_graph);
    g9.loadGraph(large_graph);
    
    // Measure time for addition operation
    auto start_addition = chrono::steady_clock::now();
    g8.addGraphs(g9);
    auto end_addition = chrono::steady_clock::now();
    auto addition_time = chrono::duration_cast<chrono::milliseconds>(end_addition - start_addition).count();
    CHECK(addition_time < 100); // Addition operation should complete within 100 milliseconds

    // Measure time for scalar multiplication operation
    auto start_scalar_multiply = chrono::steady_clock::now();
    g8.scalarMultiply(5);
    auto end_scalar_multiply = chrono::steady_clock::now();
    auto scalar_multiply_time = chrono::duration_cast<chrono::milliseconds>(end_scalar_multiply - start_scalar_multiply).count();
    CHECK(scalar_multiply_time < 100); // Scalar multiplication operation should complete within 100 milliseconds
}

TEST_CASE("Test loading graph and basic properties")
{
    // Test loading a graph and basic properties
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(g.getGraph() == graph);
    CHECK(g.getVertices() == 3);
    CHECK(g.getEdges() == 4);
}

TEST_CASE("Test loading empty graph")
{
    // Test loading an empty graph
    Graph g;
    vector<vector<int>> empty_graph;
    CHECK_THROWS(g.loadGraph(empty_graph));
}

TEST_CASE("Test loading non-square graph")
{
    // Test loading a non-square graph
    Graph g;
    vector<vector<int>> non_square_graph = {
        {0, 1, 0},
        {1, 0, 1}};
    CHECK_THROWS(g.loadGraph(non_square_graph));
}

TEST_CASE("Test addGraphs method")
{
    // Test addGraphs method
    Graph g1, g2;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 0},
        {1, 0, 0}};
    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    g1.addGraphs(g2);
    vector<vector<int>> expected_result = {
        {0, 2, 1},
        {2, 0, 1},
        {1, 1, 0}};
    CHECK(g1.getGraph() == expected_result);
}

TEST_CASE("Test subtractGraphs method")
{
    // Test subtractGraphs method
    Graph g1, g2;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 0},
        {1, 0, 0}};
    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    g1.subtractGraphs(g2);
    vector<vector<int>> expected_result = {
        {0, 0,-1},
        {0, 0, 1},
        {-1, 1, 0}};
    CHECK(g1.getGraph() == expected_result);
}

TEST_CASE("Test inPlaceAdd method")
{
    // Test inPlaceAdd method
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    g.inPlaceAdd(5);
    vector<vector<int>> expected_result = {
        {5, 6, 5},
        {6, 5, 6},
        {5, 6, 5}};
    CHECK(g.getGraph() == expected_result);
}

TEST_CASE("Test inPlaceSubtract method")
{
    // Test inPlaceSubtract method
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    g.inPlaceSubtract(1);
    vector<vector<int>> expected_result = {
        {-1, 0, -1},
        {0, -1, 0},
        {-1, 0, -1}};
    CHECK(g.getGraph() == expected_result);
}

TEST_CASE("Test increment method")
{
    // Test increment method
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    g.increment();
    vector<vector<int>> expected_result = {
        {1, 2, 1},
        {2, 1, 2},
        {1, 2, 1}};
    CHECK(g.getGraph() == expected_result);
}

TEST_CASE("Test decrement method")
{
    // Test decrement method
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    g.decrement();
    vector<vector<int>> expected_result = {
        {-1, 0, -1},
        {0, -1, 0},
        {-1, 0, -1}};
    CHECK(g.getGraph() == expected_result);
}

TEST_CASE("Test unaryPlus method")
{
    // Test unaryPlus method
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    g.unaryPlus(); // Should not change the graph
    CHECK(g.getGraph() == graph);
}

TEST_CASE("Test unaryMinus method")
{
    // Test unaryMinus method
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    g.unaryMinus();
    vector<vector<int>> expected_result = {
        {0, -1, 0},
        {-1, 0, -1},
        {0, -1, 0}};
    CHECK(g.getGraph() == expected_result);
}

TEST_CASE("Test scalarMultiply method")
{
    // Test scalarMultiply method
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    g.scalarMultiply(3);
    vector<vector<int>> expected_result = {
        {0, 3, 0},
        {3, 0, 3},
        {0, 3, 0}};
    CHECK(g.getGraph() == expected_result);
}

TEST_CASE("Test for loading large graph")
{
    // Test loading a large graph
    Graph g;
    const int size = 1000;
    vector<vector<int>> large_graph(size, vector<int>(size, 1)); // 1000x1000 matrix filled with ones
    g.loadGraph(large_graph);
    CHECK(g.getGraph() == large_graph);
}

TEST_CASE("Test loading graph with negative values")
{
    // Test loading a graph with negative values
    Graph g;
    vector<vector<int>> graph = {
        {0, -1, 0},
        {-1, 0, -1},
        {0, -1, 0}};
    g.loadGraph(graph);
    CHECK(g.getGraph() == graph);
}

TEST_CASE("Test loading graph with zero edges")
{
    // Test loading a graph with zero edges
    Graph g;
    vector<vector<int>> graph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph);
    CHECK(g.getGraph() == graph);
}

TEST_CASE("Test loading graph with self-loops")
{
    // Test loading a graph with self-loops
    Graph g;
    vector<vector<int>> graph = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}};
    g.loadGraph(graph);
    CHECK(g.getGraph() == graph);
}

TEST_CASE("Test loading graph with negative self-loops")
{
    // Test loading a graph with negative self-loops
    Graph g;
    vector<vector<int>> graph = {
        {-1, 0, 0},
        {0, -1, 0},
        {0, 0, -1}};
    g.loadGraph(graph);
    CHECK(g.getGraph() == graph);
}

TEST_CASE("Test loading graph with duplicate edges")
{
    // Test loading a graph with duplicate edges
    Graph g;
    vector<vector<int>> graph = {
        {1, 1, 0},
        {1, 0, 1},
        {0, 1, 1}};
    g.loadGraph(graph);
    CHECK(g.getGraph() == graph);
}

TEST_CASE("Test loading graph with negative cycles")
{
    // Test loading a graph with negative cycles
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}};
    g.loadGraph(graph);
    CHECK(g.getGraph() == graph);
}

TEST_CASE("Test loading graph with disconnected components")
{
    // Test loading a graph with disconnected components
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph);
    CHECK(g.getGraph() == graph);
}

TEST_CASE("Test initializing graph with single vertex")
{
    // Test initializing a graph with a single vertex
    Graph g;
    vector<vector<int>> single_vertex_graph = {{0}};
    g.loadGraph(single_vertex_graph);
    CHECK(g.getGraph() == single_vertex_graph);
    CHECK(g.getVertices() == 1);
    CHECK(g.getEdges() == 0);
}

TEST_CASE("Test initializing graph with disconnected vertices")
{
    // Test initializing a graph with disconnected vertices
    Graph g;
    vector<vector<int>> disconnected_vertices_graph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(disconnected_vertices_graph);
    CHECK(g.getGraph() == disconnected_vertices_graph);
    CHECK(g.getVertices() == 3);
    CHECK(g.getEdges() == 0);
}

TEST_CASE("Test adding graph with all zeros")
{
    // Test adding a graph with all zeros to another graph
    Graph g1, g2;
    vector<vector<int>> graph1 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    vector<vector<int>> graph2 = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}};
    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    g1.addGraphs(g2);
    CHECK(g1.getGraph() == graph2);
}

TEST_CASE("Test subtracting graph with all zeros")
{
    // Test subtracting a graph with all zeros from another graph
    Graph g1, g2;
    vector<vector<int>> graph1 = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}};
    vector<vector<int>> graph2 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    g1.subtractGraphs(g2);
    CHECK(g1.getGraph() == graph1);
}

TEST_CASE("Test adding graph with all negative values")
{
    // Test adding a graph with all negative values to another graph
    Graph g1, g2;
    vector<vector<int>> graph1 = {
        {-1, -1, -1},
        {-1, -1, -1},
        {-1, -1, -1}};
    vector<vector<int>> graph2 = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}};
    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    g1.addGraphs(g2);
    vector<vector<int>> expected_result = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    CHECK(g1.getGraph() == expected_result);
}
