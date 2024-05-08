#include "doctest.h"
#include "Graph.hpp"
#include "Algorithms.hpp"
#include <sstream>

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

TEST_CASE("Test isConnected with connected and disconnected graphs")
{
    // Test isConnected with connected and disconnected graphs
    Graph g;
    SUBCASE("Connected graph")
    {
        vector<vector<int>> connected_graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g.loadGraph(connected_graph);
        CHECK(Algorithms::isConnected(g) == true);
    }
    SUBCASE("Disconnected graph")
    {
        vector<vector<int>> disconnected_graph = {
            {0, 1, 0, 0},
            {1, 0, 0, 0},
            {0, 0, 0, 1},
            {0, 0, 1, 0}};
        g.loadGraph(disconnected_graph);
        CHECK(Algorithms::isConnected(g) == false);
    }
}

TEST_CASE("Test isBipartite with bipartite and non-bipartite graphs")
{
    // Test isBipartite with bipartite and non-bipartite graphs
    Graph g;
    SUBCASE("Bipartite graph")
    {
        vector<vector<int>> bipartite_graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g.loadGraph(bipartite_graph);
        CHECK(Algorithms::isBipartite(g) == true);
    }
    SUBCASE("Non-bipartite graph")
    {
        vector<vector<int>> non_bipartite_graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 1}};
        g.loadGraph(non_bipartite_graph);
        CHECK(Algorithms::isBipartite(g) == false);
    }
}

TEST_CASE("Test isContainsCycle with acyclic and cyclic graphs")
{
    // Test isContainsCycle with acyclic and cyclic graphs
    Graph g;
    SUBCASE("Acyclic graph")
    {
        vector<vector<int>> acyclic_graph = {
            {0, 1, 0},
            {0, 0, 1},
            {0, 0, 0}};
        g.loadGraph(acyclic_graph);
        CHECK(Algorithms::isContainsCycle(g) == false);
    }
    SUBCASE("Cyclic graph")
    {
        vector<vector<int>> cyclic_graph = {
            {0, 1, 0},
            {0, 0, 1},
            {1, 0, 0}};
        g.loadGraph(cyclic_graph);
        CHECK(Algorithms::isContainsCycle(g) == true);
    }
}

TEST_CASE("Test negativeCycle with graphs containing negative weight cycles")
{
    // Test negativeCycle with graphs containing negative weight cycles
    Graph g;
    SUBCASE("Graph with negative weight cycle")
    {
        vector<vector<int>> graph_with_negative_cycle = {
            {0, 1, -1},
            {-1, 0, 1},
            {1, -1, 0}};
        g.loadGraph(graph_with_negative_cycle);
        CHECK(Algorithms::negativeCycle(g) == true);
    }
    SUBCASE("Graph without negative weight cycle")
    {
        vector<vector<int>> graph_without_negative_cycle = {
            {0, 1, 0},
            {0, 0, 1},
            {1, 0, 0}};
        g.loadGraph(graph_without_negative_cycle);
        CHECK(Algorithms::negativeCycle(g) == false);
    }
}

TEST_CASE("Test shortestPath with various graphs and vertex pairs")
{
    // Test shortestPath with various graphs and vertex pairs
    Graph g;
    SUBCASE("Shortest path in a connected graph")
    {
        vector<vector<int>> connected_graph = {
            {0, 1, 1},
            {1, 0, 1},
            {1, 1, 0}};
        g.loadGraph(connected_graph);
        CHECK(Algorithms::shortestPath(g, 0, 2) == vector<size_t>{0, 2});
    }
    SUBCASE("Shortest path in a disconnected graph")
    {
        vector<vector<int>> disconnected_graph = {
            {0, 1, 0, 0},
            {1, 0, 0, 0},
            {0, 0, 0, 1},
            {0, 0, 1, 0}};
        g.loadGraph(disconnected_graph);
        CHECK(Algorithms::shortestPath(g, 0, 3) == vector<size_t>{});
    }
    SUBCASE("Shortest path in a graph with negative weights")
    {
        vector<vector<int>> graph_with_negative_weights = {
            {0, 1, -2},
            {0, 0, 3},
            {0, 0, 0}};
        g.loadGraph(graph_with_negative_weights);
        CHECK(Algorithms::shortestPath(g, 0, 2) == vector<size_t>{0, 2});
    }
}
TEST_CASE("Test loading graph with negative edge weights")
{
    // Test loading a graph with negative edge weights
    Graph g;
    vector<vector<int>> graph_with_negative_weights = {
        {0, 1, -2},
        {0, 0, 3},
        {0, 0, 0}};
    g.loadGraph(graph_with_negative_weights);
    CHECK(g.getGraph() == graph_with_negative_weights);
}

TEST_CASE("Test loading graph with zero edge weights")
{
    // Test loading a graph with zero edge weights
    Graph g;
    vector<vector<int>> graph_with_zero_weights = {
        {0, 1, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph_with_zero_weights);
    CHECK(g.getGraph() == graph_with_zero_weights);
}

TEST_CASE("Test loading large graph")
{
    // Test loading a large graph
    Graph g;
    vector<vector<int>> large_graph(1000, vector<int>(1000, 0)); // 1000x1000 matrix filled with zeros
    g.loadGraph(large_graph);
    CHECK(g.getGraph() == large_graph);
}

TEST_CASE("Test shortestPath with unreachable vertices")
{
    // Test shortestPath with unreachable vertices
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {0, 0, 1},
        {0, 0, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::shortestPath(g, 0, 2) == vector<size_t>{0, 1, 2});
}

TEST_CASE("Test shortestPath with same start and end vertices")
{
    // Test shortestPath with same start and end vertices
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::shortestPath(g, 1, 1) == vector<size_t>{1});
}

TEST_CASE("Test negativeCycle with large graph")
{
    // Test negativeCycle with large graph
    Graph g;
    vector<vector<int>> graph(1000, vector<int>(1000, 0)); // 1000x1000 matrix filled with zeros
    graph[0][1] = -5; // introducing a negative weight cycle
    graph[1][2] = 3;
    graph[2][0] = 1;
    g.loadGraph(graph);
    CHECK(Algorithms::negativeCycle(g) == true);
}