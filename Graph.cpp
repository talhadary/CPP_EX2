#include "Graph.hpp"

using namespace std;
using ariel::Graph;

/// @brief Checks if the given graph is square (number of rows equals number of columns).
/// @param graph The adjacency matrix representing the graph.
/// @return True if the graph is square, false otherwise.
bool Graph::isSquare(const vector<vector<int>> &graph)
{
    int rows = graph.size();
    if (rows == 0)
    {
        return false;
    }

    int cols = graph[0].size();
    return rows == cols;
}

/// @brief Counts the number of vertices in the graph.
/// @return The number of vertices.
size_t Graph::countVertices()
{
    return graph.size();
}

/// @brief Counts the number of edges in the graph.
/// @return The number of edges.
size_t Graph::countEdges()
{
    size_t edges = 0;
    for (const vector<int> &row : graph)
    {
        for (int value : row)
        {
            if (value != 0)
                edges++;
        }
    }
    return edges;
}

/// @brief Loads the graph from the given adjacency matrix.
/// @param graph The adjacency matrix representing the graph.
/// @throw runtime_error if the adjacency matrix is not square.
void Graph::loadGraph(const vector<vector<int>> &graph)
{
    if (isSquare(graph))
    {
        this->graph = graph;
        this->vertices = countVertices();
        this->edges = countEdges();
    }
    else
    {
        throw runtime_error("Invalid adjacency matrix!");
    }
}

/// @brief Prints the graph adjacency matrix.
void Graph::printGraph()
{
    vector<vector<int>> graph = this->graph;
    cout << "Graph with " << vertices << " vertices and " << edges << " edges" << endl;
    for (const vector<int> &row : graph)
    {
        for (int value : row)
        {
            if (value >= 0) cout << " "; // Ensure proper spacing for positive values
            cout << value << " ";
        }
        cout << endl;
    }
}

/// @brief Getter method to access the graph.
/// @return The adjacency matrix representing the graph.
const vector<vector<int>> &Graph::getGraph() const
{
    return this->graph;
}

/// @brief Getter method for the number of vertices.
/// @return The number of vertices in the graph.
size_t Graph::getVertices() const
{
    return this->vertices;
}

/// @brief Getter method for the number of edges.
/// @return The number of edges in the graph.
size_t Graph::getEdges() const
{
    return this->edges;
}
