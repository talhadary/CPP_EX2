#include "Algorithms.hpp"

using namespace std;
using ariel::Algorithms;
using ariel::Graph;

/// @brief Performs Depth-First Search (DFS) to recursively find cycles in the graph.
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

/// @brief Checks if the graph component starting from the specified vertex is bipartite.
/// @param start The starting vertex for bipartite checking.
/// @param graph The adjacency matrix of the graph.
/// @param colors A vector to store colors of vertices, where INF indicates uncolored.
/// @param groups A vector of vectors that represent the 2 color groups.
/// @return True if the component is bipartite, false otherwise.
bool Algorithms::isComponentBipartite(size_t start, const vector<vector<int>> &graph, vector<size_t> &colors, vector<vector<size_t>> &groups)
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
            if (graph[current][neighbor] != 0)
            {
                if (colors[neighbor] == INF)
                {
                    colors[neighbor] = 1 - colors[current];
                    q.push(neighbor);
                }
                else if (colors[neighbor] == colors[current])
                {
                    // If the vertex has been visited and is the same color as the previous vertex, return false (not bipartite)
                    return false;
                }
            }
        }
    }

    // Add the vertices to groups
    vector<size_t> group1;
    vector<size_t> group2;

    for (size_t i = 0; i < colors.size(); i++)
    {
        if (colors[i] == 0)
        {
            group1.push_back(i);
        }
        else
        {
            group2.push_back(i);
        }
    }
    groups.push_back(group1);
    groups.push_back(group2);

    // All checks passed, return true (bipartite)
    return true;
}

// Helper method for Bellman-Ford to relax an edge if possible
bool relaxEdges(const vector<vector<int>> &graph, vector<int> &distance, vector<size_t> &parent, bool &negativeCycleDetected)
{
    size_t n = graph.size();
    bool relaxed = false; // Flag to keep track if edges have been relaxed or not

    // Relaxes all edges once
    for (size_t u = 0; u < n; ++u)
    {
        for (size_t v = 0; v < n; ++v)
        {
            if (graph[u][v] != 0 && distance[u] != INF && distance[u] + graph[u][v] < distance[v])
            {
                // If a negative cycle has been detected, set distance to negative infinity
                if (negativeCycleDetected)
                {
                    distance[v] = NEG_INF;
                }
                // Otherwise, update distance and parent vectors
                else
                {
                    distance[v] = distance[u] + graph[u][v];
                    parent[v] = u;
                }
                relaxed = true;
            }
        }
    }

    // Return the flag indicating whether any edges were relaxed
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
    parent.assign(n, INF);
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

/// @brief Checks if the graph is connected using Breadth-First Search (BFS).
/// @param g The Graph object to check.
/// @return True if the graph is connected, false otherwise.
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
                // If an edge exists and we haven't visited it, add it to the queue
                if (neighbor && !visited[ind])
                {
                    travers.push(ind);
                }
                ind++;
            }
        }
    }

    // Check if all vertices were visited and prints accordingly
    for (bool v : visited)
    {
        if (!v)
        {
            cout << "Graph is not connected!" << endl;
            return false;
        }
    }
    cout << "Graph is connected!" << endl;
    return true;
}

/// @brief Finds the shortest path between two vertices using the Bellman-Ford algorithm.
/// @param g The Graph object to check.
/// @param start The starting vertex.
/// @param end The end vertex.
/// @return An array of vertices that make up the shortest path.
vector<size_t> Algorithms::shortestPath(const Graph &g, size_t start, size_t end)
{
    size_t vertices = g.getVertices();
    vector<vector<int>> graph = g.getGraph();
    vector<int> dist;
    vector<size_t> prev;
    bellmanFord(start, graph, dist, prev);
    vector<size_t> path; // Initialize the path vector

    // If start = end, return start
    if (start == end)
    {
        path.push_back(start);
        return path;
    }
    
    // If there is a shortest path, build it into path
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

/// @brief Checks if the graph contains any cycles.
/// @param g The Graph object to check.
/// @return True if the graph contains a cycle, false otherwise.
bool Algorithms::isContainsCycle(const Graph &g)
{
    const vector<vector<int>> &graph = g.getGraph();
    size_t n = g.getVertices();
    vector<bool> visited(n, false);
    vector<bool> recStack(n, false);
    vector<size_t> parent(n, INF);

    // Check for cycles using DFS
    for (size_t i = 0; i < n; ++i)
    {
        if (!visited[i])
        {
            if (dfs(i, visited, recStack, graph, parent))
            {
                cout << "Cycle detected!" << endl;
                return true; // Cycle detected
            }
        }
    }

    cout << "No cycle detected!" << endl;
    return false; // No cycle found
}

/// @brief Checks if a graph is bipartite.
/// @param g The Graph object to check.
/// @return True if the graph is bipartite, false otherwise.
bool Algorithms::isBipartite(const Graph &g)
{
    const vector<vector<int>> &graph = g.getGraph();
    size_t n = g.getVertices();
    vector<vector<size_t>> groups;
    vector<size_t> colors(n, INF); // Initialize colors, INF indicates uncolored

    // Check each vertex in the graph
    for (size_t i = 0; i < n; ++i)
    {
        if (colors[i] == INF)
        {                                                        // Vertex not visited yet
            if (!isComponentBipartite(i, graph, colors, groups)) // Check specific vertex
            {
                cout << "Graph is not Bipartite!" << endl;
                return false; // Not bipartite
            }
        }
    }

    // Print the groups
    cout << "Graph is Bipartite! These are the possible groups:" << endl;
    for (size_t i = 0; i < groups.size(); i++)
    {
        cout << "Group " << (i % 2) + 1 << ": ";
        for (size_t vertex : groups[i])
        {
            cout << vertex << " ";
        }
        cout << endl;
    }

    return true; // Bipartite
}

/// @brief Checks for the presence of any negative weight cycles in the graph.
/// @param g The Graph object containing the adjacency matrix and vertex count.
/// @return True if any negative weight cycle is found, false otherwise.
bool Algorithms::negativeCycle(const Graph &g)
{
    const vector<vector<int>> &graph = g.getGraph();
    size_t n = g.getVertices();
    vector<int> distance;
    vector<size_t> parent;

    // Check for negative cycles from each vertex
    for (size_t i = 0; i < n; ++i)
    {
        if (bellmanFord(i, graph, distance, parent))
        {
            cout << "Negative cycle detected!" << endl;
            return true; // Negative cycle found
        }
    }

    cout << "No negative cycle detected!" << endl;
    return false; // No negative cycle found
}
