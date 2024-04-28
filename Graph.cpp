#include "Graph.hpp"

using namespace std;
using ariel::Graph;

bool Graph::isSquare()
{
    int rows = graph.size();
    if (rows == 0)
    {
        return false;
    }

    int cols = graph[0].size();
    return rows == cols;
}

int Graph::countVertices()
{
    return graph.size();
}

int Graph::countEdges()
{
    int edges = 0;
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
    if (isSquare())
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

void Graph::printGraph() const
{
    vector<vector<int>> graph = getGraph();
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
    return graph;
}

// Getter method for num of vertices
int Graph::getVertices() const
{
    return vertices;
}

// Getter method for num of edges
int Graph::getEdges() const
{
    return edges;
}
