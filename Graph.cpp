#include "Graph.hpp"

using namespace std;
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

int Graph::countVertices(const vector<vector<int>> &graph)
{
    return graph.size();
}

int Graph::countEdges(const vector<vector<int>> &graph)
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

void Graph::loadGraph(vector<vector<int>> &graph)
{
    if (isSquare(graph))
    {
        this->graph = graph;
        this->vertices = countVertices(graph);
        this->edges = countEdges(graph);
    }
    else
    {
        cout << "Error: this matrix isn't square!" << endl;
    }
}

void Graph::printGraph()
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
