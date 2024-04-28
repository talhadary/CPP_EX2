#include "Graph.hpp"

using namespace std;
using ariel::Graph;

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

size_t Graph::countVertices()
{
    return graph.size();
}

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

void Graph::printGraph()
{
    vector<vector<int>> graph = this->graph;
    cout << "Graph with " << vertices << " vertices and " << edges << " edges" << endl;
    for (const vector<int> &row : graph)
    {
        for (int value : row)
        {
            cout << value << " ";
        }
        cout << endl;
    }
}

// Getter method to access the graph
const vector<vector<int>> &Graph::getGraph() const
{
    return this->graph;
}

// Getter method for num of vertices
size_t Graph::getVertices() const
{
    return this->vertices;
}

// Getter method for num of edges
size_t Graph::getEdges() const
{
    return this->edges;
}
