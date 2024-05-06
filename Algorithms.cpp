#include "Algorithms.hpp"

using namespace std;
using ariel::Algorithms;
using ariel::Graph;

/// @brief Performs DFS to recursively find cycles in the graph.
/// @param v The current vertex being visited.
/// @param visited A vector to keep track of visited vertices.
/// @param recStack A stack to track vertices in the current recursion stack.
/// @param graph The adjacency matrix representing the graph.
/// @param parent A vector to record the parent vertex of each vertex, used for cycle detection.
/// @return True if a cycle is detected in the graph, false otherwise.
bool Algorithms::dfs(size_t v, vector<bool> &visited, vector<bool> &recStack, const vector<vector<int>> &graph, vector<size_t> &parent)
{
    visited[v] = true;
    recStack[v] = true;

    for (size_t i = 0; i < graph[v].size(); ++i)
    {
        if (graph[v][i])
        {
            if (!visited[i])
            {
                parent[i] = v;
                if (dfs(i, visited, recStack, graph, parent))
                {
                    return true;
                }
            }
            else if (recStack[i])
            {
                return true;
            }
        }
    }

    recStack[v] = false;
    return false;
}

/// @brief Checks if the graph component starting from the specified vertex is bipartite using BFS.
/// @param start The starting vertex for bipartite checking.
/// @param graph The adjacency matrix of the graph.
/// @param colors A vector to store colors of vertices, where -1 indicates uncolored.
/// @return True if the component is bipartite, false otherwise.
bool Algorithms::isComponentBipartite(size_t start, const vector<vector<int>> &graph, vector<int> &colors)
{
    queue<size_t> q;
    q.push(start);
    colors[start] = 0;

    while (!q.empty())
    {
        size_t current = q.front();
        q.pop();

        for (size_t neighbor = 0; neighbor < graph[current].size(); ++neighbor)
        {
            if (graph[current][neighbor] == 1)
            {
                if (colors[neighbor] == -1)
                {
                    colors[neighbor] = 1 - colors[current];
                    q.push(neighbor);
                }
                else if (colors[neighbor] == colors[current])
                {
                    return false;
                }
            }
        }
    }

    // Print the groups
    cout << "Group A = {";
    for (size_t i = 0; i < colors.size(); i++)
    {
        if (colors[i] == 0)
        {
            cout << i + 1 << " ";
        }
    }
    cout << "}" << endl;

    cout << "Group B = {";
    for (size_t i = 0; i < colors.size(); i++)
    {
        if (colors[i] == 1)
        {
            cout << i + 1 << " ";
        }
    }
    cout << "}" << endl;

    return true;
}

// Helper method for Bellman Ford to relax an edge if possible
bool relaxEdges(const vector<vector<int>> &graph, vector<int> &distance, vector<size_t> &parent, bool &negativeCycleDetected)
{
    size_t n = graph.size();
    bool relaxed = false;

    for (size_t u = 0; u < n; ++u)
    {
        for (size_t v = 0; v < n; ++v)
        {
            if (graph[u][v] != 0 && distance[u] != INF && distance[u] + graph[u][v] < distance[v])
            {
                if (negativeCycleDetected)
                {
                    distance[v] = NEG_INF;
                }
                else
                {
                    distance[v] = distance[u] + graph[u][v];
                    parent[v] = u;
                }
                relaxed = true;
            }
        }
    }

    return relaxed;
}

/// @brief Uses the Bellman-Ford algorithm to detect negative weight cycles from a given starting vertex.
/// @param start The starting vertex for the Bellman-Ford algorithm.
/// @param graph The adjacency matrix of the graph.
/// @param distance A vector to store the shortest path distances from the start vertex.
/// @param parent A vector to store the predecessor of each vertex in the path.
/// @return True if a negative weight cycle is found, false otherwise.
bool Algorithms::bellmanFord(size_t start, const vector<vector<int>> &graph, vector<int> &distance, vector<size_t> &parent)
{
    size_t n = graph.size();
    distance.assign(n, INF);
    parent.assign(n, -1);
    distance[start] = 0;

    // Iterate to relax edges
    bool negativeCycleDetected = false;
    for (size_t i = 0; i < n - 1; ++i)
    {
        if (!relaxEdges(graph, distance, parent, negativeCycleDetected))
            break; // No need to continue if no relaxation occurred
    }

    // Check for negative cycles
    negativeCycleDetected = relaxEdges(graph, distance, parent, negativeCycleDetected);

    // If negative cycle found, update affected vertices
    if (negativeCycleDetected)
    {
        for (size_t i = 0; i < n - 1; ++i)
        {
            relaxEdges(graph, distance, parent, negativeCycleDetected);
        }
    }

    return negativeCycleDetected;
}

/// @brief bfs search to see of we can get from each vertex to each vertex in graph
/// @param g the Graph object to check
/// @return true if graph is connected, false otherwise
bool Algorithms::isConnected(const Graph &g)
{
    vector<vector<int>> graph = g.getGraph();
    size_t vertices = size_t(g.getVertices());
    vector<bool> visited(vertices, false);
    queue<size_t> travers;

    travers.push(0); // Start traversal from vertex 0

    while (!travers.empty())
    {
        size_t curr = travers.front();
        travers.pop();

        if (!visited[curr])
        {
            visited[curr] = true;
            size_t ind = 0;
            for (int neighbor : graph[curr])
            {
                if (neighbor && !visited[ind])
                {
                    travers.push(ind);
                }
                ind++;
            }
        }
    }

    // Check if all vertices were visited
    for (bool v : visited)
    {
        if (!v)
        {
            return false;
        }
    }
    return true;
}

/// @brief finds the shortest path between two vertices using bellman ford helper method
/// @param g Graph object to check
/// @param start starting vertex
/// @param end end vertex
/// @return array of vertices that make up the shortest path
vector<size_t> Algorithms::shortestPath(const Graph &g, size_t start, size_t end)
{
    size_t vertices = g.getVertices();
    vector<vector<int>> graph = g.getGraph();
    vector<int> dist;
    vector<size_t> prev;
    bellmanFord(start, graph, dist, prev); // no  need for the returned bool, the method changes the arrays we declared

    vector<size_t> path; // Path is empty

    // if there is a shortest path, build it into path
    if (prev[end] != INF && dist[end] != NEG_INF)
    {
        for (size_t at = end; at != INF; at = prev[at])
        {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());
    }

    return path;
}

/// @brief checks if graph contains cycle
/// @param g Graph object to check
/// @return true if contains cycle, false otherwise
bool Algorithms::isContainsCycle(const Graph &g)
{
    const vector<vector<int>> &graph = g.getGraph();
    size_t n = g.getVertices();
    vector<bool> visited(n, false);
    vector<bool> recStack(n, false);
    vector<size_t> parent(n, INF);

    for (size_t i = 0; i < n; ++i)
    {
        if (!visited[i])
        {
            if (dfs(i, visited, recStack, graph, parent))
            {
                return true;
            }
        }
    }

    return false;
}

/// @brief checks if a graph is bipartite (can be split into two groups such that no 2 vertices in the same group share an edge)
/// @param g Graph object to check
/// @return true if bipartite, false otherwise
bool Algorithms::isBipartite(const Graph &g)
{
    const vector<vector<int>> &graph = g.getGraph();
    size_t n = g.getVertices();
    vector<int> colors(n, -1); // Initialize colors, -1 indicates uncolored

    // Checks for each vertex in graph
    for (size_t i = 0; i < n; ++i)
    {
        if (colors[i] == -1)
        {                                                // Vertex not visited yet
            if (!isComponentBipartite(i, graph, colors)) // Checks specific vertex
            {
                return false; // Not bipartite
            }
        }
    }

    return true; // Bipartite
}

/// @brief Checks for the presence of any negative weight cycles in the graph using Bellman-Ford algorithm from every vertex.
/// @param g The Graph object containing the adjacency matrix and vertex count.
/// @return True if any negative weight cycle is found, false otherwise.
bool Algorithms::negativeCycle(const Graph &g)
{
    const vector<vector<int>> &graph = g.getGraph();
    size_t n = g.getVertices();
    vector<int> distance;
    vector<size_t> parent;

    // Goes over all vertices incase of disconnected vertex
    for (size_t i = 0; i < n; ++i)
    {
        if (bellmanFord(i, graph, distance, parent))
        {
            return true; // Negative cycle found
        }
    }

    return false; // No negative cycle found
}
