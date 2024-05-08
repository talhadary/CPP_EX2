#include "Graph.hpp"

using namespace std;
using ariel::Graph;

bool Graph::isSquare(const std::vector<std::vector<int>> &adjacencyMatrix)
{
    size_t rows = adjacencyMatrix.size();
    if (rows == 0)
    {
        return false;
    }
    size_t cols = adjacencyMatrix[0].size();
    return rows == cols;
}

size_t Graph::countVertices() const
{
    return graph.size();
}

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

void Graph::loadGraph(const std::vector<std::vector<int>> &adjacencyMatrix)
{
    if (!isSquare(adjacencyMatrix))
    {
        throw std::runtime_error("Invalid adjacency matrix: not square");
    }
    graph = adjacencyMatrix;
}

void Graph::printGraph() const
{
    std::cout << "Graph with " << countVertices() << " vertices and " << countEdges() << " edges\n";
    for (const auto &row : graph)
    {
        for (int value : row)
        {
            std::cout << value << ' ';
        }
        std::cout << '\n';
    }
}

const std::vector<std::vector<int>> &Graph::getGraph() const
{
    return graph;
}

size_t Graph::getVertices() const
{
    return countVertices();
}

size_t Graph::getEdges() const
{
    return countEdges();
}

void Graph::addGraphs(const Graph &other)
{
    const auto &otherGraph = other.getGraph();
    if (graph.size() != otherGraph.size() || graph.empty())
    {
        throw std::runtime_error("Graphs of different sizes cannot be added");
    }
    for (size_t i = 0; i < graph.size(); ++i)
    {
        for (size_t j = 0; j < graph[i].size(); ++j)
        {
            graph[i][j] += otherGraph[i][j];
        }
    }
}

void Graph::subtractGraphs(const Graph &other)
{
    const auto &otherGraph = other.getGraph();
    if (graph.size() != otherGraph.size() || graph.empty())
    {
        throw std::runtime_error("Graphs of different sizes cannot be subtracted");
    }
    for (size_t i = 0; i < graph.size(); ++i)
    {
        for (size_t j = 0; j < graph[i].size(); ++j)
        {
            graph[i][j] -= otherGraph[i][j];
        }
    }
}

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

void Graph::increment()
{
    inPlaceAdd(1);
}

void Graph::decrement()
{
    inPlaceSubtract(1);
}

void Graph::unaryPlus()
{
    // Unary plus does not change the sign of the expression
}

void Graph::unaryMinus()
{
    Graph::scalarMultiply(-1);
}

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

Graph Graph::multiplyGraphs(const Graph &other) const
{
    const auto &otherGraph = other.getGraph();
    if (graph.size() != otherGraph.size() || graph.empty())
    {
        throw std::runtime_error("Graphs of different sizes cannot be multiplied");
    }
    Graph result;
    std::vector<std::vector<int>> resultMatrix(graph.size(), std::vector<int>(graph.size(), 0));
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