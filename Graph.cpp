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
    cout << "Graph with " << countVertices() << " vertices and " << countEdges() << " edges\n";
    for (const auto &row : graph)
    {
        for (int value : row)
        {
            cout << value << ' ';
        }
        cout << '\n';
    }
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

// Function to add another graph to the current graph
void Graph::addGraphs(const Graph &other)
{
    const auto &otherGraph = other.getGraph();
    if (graph.size() != otherGraph.size() || graph.empty())
    {
        throw runtime_error("Graphs of different sizes cannot be added");
    }
    for (size_t i = 0; i < graph.size(); ++i)
    {
        for (size_t j = 0; j < graph[i].size(); ++j)
        {
            graph[i][j] += otherGraph[i][j];
        }
    }
}

// Function to subtract another graph from the current graph
void Graph::subtractGraphs(const Graph &other)
{
    const auto &otherGraph = other.getGraph();
    if (graph.size() != otherGraph.size() || graph.empty())
    {
        throw runtime_error("Graphs of different sizes cannot be subtracted");
    }
    for (size_t i = 0; i < graph.size(); ++i)
    {
        for (size_t j = 0; j < graph[i].size(); ++j)
        {
            graph[i][j] -= otherGraph[i][j];
        }
    }
}

// Function to perform in-place addition of a scalar value to all elements in the graph
void Graph::inPlaceAdd(int num)
{
    for (auto &row : graph)
    {
        for (int &element : row)
        {
            element += num;
        }
    }
}

// Function to perform in-place subtraction of a scalar value from all elements in the graph
void Graph::inPlaceSubtract(int num)
{
    for (auto &row : graph)
    {
        for (int &element : row)
        {
            element -= num;
        }
    }
}

// Function to increment all elements in the graph by 1
void Graph::increment()
{
    inPlaceAdd(1);
}

// Function to decrement all elements in the graph by 1
void Graph::decrement()
{
    inPlaceSubtract(1);
}

// Unary plus operator function
void Graph::unaryPlus()
{
    // Unary plus does not change the sign of the expression
}

// Unary minus operator function
void Graph::unaryMinus()
{
    Graph::scalarMultiply(-1);
}

// Function to perform scalar multiplication of the graph by a given value
void Graph::scalarMultiply(int num)
{
    for (auto &row : graph)
    {
        for (int &element : row)
        {
            element *= num;
        }
    }
}

// Function to multiply two graphs
Graph Graph::multiplyGraphs(const Graph &other) const
{
    const auto &otherGraph = other.getGraph();
    if (graph.size() != otherGraph.size() || graph.empty())
    {
        throw runtime_error("Graphs of different sizes cannot be multiplied");
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
