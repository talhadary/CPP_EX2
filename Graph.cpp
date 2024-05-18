#include "Graph.hpp"

using namespace std;
using ariel::Graph;

// Function to check if the adjacency matrix is square
bool Graph::isSquare(const vector<vector<int>> &adjacencyMatrix)
{
    size_t rows = adjacencyMatrix.size();
    if (rows == 0)
    {
        return false;
    }
    size_t cols = adjacencyMatrix[0].size();
    return rows == cols;
}

// Function to count the number of vertices in the graph
size_t Graph::countVertices() const
{
    return graph.size();
}

// Function to count the number of edges in the graph
size_t Graph::countEdges() const
{
    size_t edges = 0;
    for (const auto &row : graph)
    {
        for (int value : row)
        {
            if (value != 0)
            {
                edges++;
            }
        }
    }
    return edges;
}

// Function to load the graph with the given adjacency matrix
void Graph::loadGraph(const vector<vector<int>> &adjacencyMatrix)
{
    if (!isSquare(adjacencyMatrix))
    {
        throw runtime_error("Invalid adjacency matrix: not square");
    }
    graph = adjacencyMatrix;
}

// Function to print the graph
void Graph::printGraph() const
{
    cout << "Graph with " << countVertices() << " vertices and " << countEdges() << " edges:\n"
         << endl;
    for (const auto &row : graph)
    {
        for (int value : row)
        {
            cout << value << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

// Function to get the adjacency matrix of the graph
const vector<vector<int>> &Graph::getGraph() const
{
    return graph;
}

// Function to get the number of vertices in the graph
size_t Graph::getVertices() const
{
    return countVertices();
}

// Function to get the number of edges in the graph
size_t Graph::getEdges() const
{
    return countEdges();
}

// Operator to add another graph to the current graph
Graph Graph::operator+(const Graph &other)
{
    Graph g;
    vector<vector<int>> adjMat(graph.size(), vector<int>(graph.size(), 0));
    const auto &otherGraph = other.getGraph();
    if (graph.size() != otherGraph.size() || graph.empty())
    {
        throw runtime_error("Graphs of different sizes cannot be added");
    }
    for (size_t i = 0; i < graph.size(); ++i)
    {
        for (size_t j = 0; j < graph[i].size(); ++j)
        {
            adjMat[i][j] = graph[i][j] + otherGraph[i][j];
        }
    }
    g.loadGraph(adjMat);
    return g;
}

// Operator to subtract another graph from the current graph
Graph Graph::operator-(const Graph &other)
{
    Graph g;
    vector<vector<int>> adjMat(graph.size(), vector<int>(graph.size(), 0));
    const auto &otherGraph = other.getGraph();
    if (graph.size() != otherGraph.size() || graph.empty())
    {
        throw runtime_error("Graphs of different sizes cannot be subtracted");
    }
    for (size_t i = 0; i < graph.size(); ++i)
    {
        for (size_t j = 0; j < graph[i].size(); ++j)
        {
            adjMat[i][j] = graph[i][j] -= otherGraph[i][j];
        }
    }
    g.loadGraph(adjMat);
    return g;
}

// Operator to perform in-place addition of a scalar value to all elements in the graph
void Graph::operator+=(int num)
{
    for (size_t i = 0; i < graph.size(); ++i)
    {
        for (size_t j = 0; j < graph[i].size(); ++j)
        {
            graph[i][j] += num;
        }
    }
}

// Operator to perform in-place subtraction of a scalar value from all elements in the graph
void Graph::operator-=(int num)
{
    for (size_t i = 0; i < graph.size(); ++i)
    {
        for (size_t j = 0; j < graph[i].size(); ++j)
        {
            graph[i][j] -= num;
        }
    }
}

// Operator to increment all elements in the graph by 1
void Graph::operator++()
{
    for (size_t i = 0; i < graph.size(); ++i)
    {
        for (size_t j = 0; j < graph[i].size(); ++j)
        {
            graph[i][j] += 1;
        }
    }
}

// Postfix version
void Graph::operator++(int)
{
    ++*this;
}

// Operator to decrement all elements in the graph by 1
void Graph::operator--()
{
    for (size_t i = 0; i < graph.size(); ++i)
    {
        for (size_t j = 0; j < graph[i].size(); ++j)
        {
            graph[i][j] -= 1;
        }
    }
}

// Postfix version
void Graph::operator--(int)
{
    --*this;
}

// Unary plus operator
void Graph::operator+()
{
    // Unary plus does not change the sign of the expression
}

// Unary minus operator
void Graph::operator-()
{
    *this *(-1);
}

// Checks if other graph is a proper subset of this graph
bool Graph::operator>(const Graph &other) const
{
    vector<vector<int>> g = other.getGraph();

    if (graph.size() < g.size() || graph[0].size() < g[0].size())
    {
        return false;
    }

    bool flag = false;
    for (size_t i = 0; i < g.size(); i++)
    {
        for (size_t u = 0; u < g.size(); u++)
        {
            if (g[i][u] != 0 && g[i][u] != graph[i][u])
            {
                flag = false;
                break;
            }
            if (g[i][u] != 0 && graph[i][u] != 0)
            {
                flag = true;
            }
        }
    }
    if (flag)
        return true;

    if (countEdges() > other.countEdges())
    {
        return true;
    }

    if (countVertices() > other.countVertices())
    {
        return true;
    }

    return false;
}

// Checks if this graph is a proper subset of other graph
bool Graph::operator<(const Graph &other) const
{
    return other > *this;
}

// Checks if both graphs are equal in value and size
bool Graph::operator==(const Graph &other) const
{
    vector<vector<int>> g = other.getGraph();
    if (graph.size() != g.size() || graph[0].size() != g[0].size())
    {
        return false;
    }
    for (size_t i = 0; i < g.size(); i++)
    {
        for (size_t u = 0; u < g.size(); u++)
        {
            if (graph[i][u] != g[i][u])
            {
                return false;
            }
        }
    }
    return true;
}

// Checks if both Graphs are not equal in value or size
bool Graph::operator!=(const Graph &other) const
{
    return !(*this == other);
}

// Checks if other graph is a subset of this graph
bool Graph::operator>=(const Graph &other) const
{
    return *this > other || *this == other;
}

// Checks if this graph is a subset of other graph
bool Graph::operator<=(const Graph &other) const
{
    return *this < other || *this == other;
}

// Operator to perform scalar multiplication of the graph by a given value
Graph Graph::operator*(int num)
{
    Graph g;
    vector<vector<int>> adjMat(graph.size(), vector<int>(graph.size(), 0));
    for (size_t i = 0; i < graph.size(); ++i)
    {
        for (size_t j = 0; j < graph[i].size(); ++j)
        {
            adjMat[i][j] = graph[i][j] *= num;
        }
    }
    g.loadGraph(adjMat);
    return g;
}

// Operator to multiply two graphs
Graph Graph::operator*(const Graph &other) const
{
    const auto &otherGraph = other.getGraph();
    if (graph[0].size() != otherGraph.size() || graph.empty())
    {
        throw runtime_error("Only valid graph sizes 'n X m * m X l' can be multiplied");
    }
    Graph result;
    vector<vector<int>> resultMatrix(graph.size(), vector<int>(graph.size(), 0));
    for (size_t i = 0; i < graph.size(); ++i)
    {
        for (size_t j = 0; j < graph.size(); ++j)
        {
            for (size_t k = 0; k < graph.size(); ++k)
            {
                resultMatrix[i][j] += graph[i][k] * otherGraph[k][j];
            }
        }
    }
    result.loadGraph(resultMatrix);
    return result;
}

// Output operator <<
ostream &ariel::operator<<(ostream &os, const Graph &g)
{
    g.printGraph();
    return os;
}
