#include "Algorithms.hpp"
#include "Graph.hpp"
#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <stdexcept>
#include <vector>

using namespace std;
using ariel::Algorithms;
using ariel::Graph;
const int INF = numeric_limits<int>::max();

bool dfs(int v, vector<bool> &visited, vector<bool> &recStack, const vector<vector<int>> &graph, vector<int> &parent)
{
    visited[v] = true;
    recStack[v] = true;

    for (int i = 0; i < graph[v].size(); ++i)
    {
        if (graph[v][i])
        { // There's an edge from v to i
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
                // Cycle detected, print the cycle
                vector<int> cycle;
                for (int x = v; x != i; x = parent[x])
                {
                    cycle.push_back(x);
                }
                cycle.push_back(i);
                cycle.push_back(v);
                cout << "Cycle detected: ";
                for (int j = cycle.size() - 1; j >= 0; --j)
                {
                    cout << cycle[j] << " ";
                }
                cout << endl;
                return true;
            }
        }
    }

    recStack[v] = false;
    return false;
}

bool isComponentBipartite(int start, const vector<vector<int>> &graph, vector<int> &colors)
{
    queue<int> q;
    q.push(start);
    colors[start] = 0; // Color the start vertex with 0

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        for (int neighbor = 0; neighbor < graph[current].size(); ++neighbor)
        {
            if (graph[current][neighbor] == 1)
            { // Check if neighbor exists
                if (colors[neighbor] == -1)
                {
                    colors[neighbor] = 1 - colors[current]; // Assign opposite color
                    q.push(neighbor);
                }
                else if (colors[neighbor] == colors[current])
                {
                    return false; // Conflict, not bipartite
                }
            }
        }
    }

    return true; // No conflicts, bipartite
}

bool bellmanFord(int start, const vector<vector<int>> &graph, vector<int> &distance, vector<int> &parent)
{
    int n = graph.size();
    distance.assign(n, INF);
    parent.assign(n, -1);
    distance[start] = 0;

    // Relax edges repeatedly
    for (int i = 0; i < n - 1; ++i)
    {
        for (int u = 0; u < n; ++u)
        {
            for (int v = 0; v < n; ++v)
            {
                if (graph[u][v] != 0 && distance[u] != INF && distance[u] + graph[u][v] < distance[v])
                {
                    distance[v] = distance[u] + graph[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    // Check for negative cycles
    for (int u = 0; u < n; ++u)
    {
        for (int v = 0; v < n; ++v)
        {
            if (graph[u][v] != 0 && distance[u] != INF && distance[u] + graph[u][v] < distance[v])
            {
                // Negative cycle detected, reconstruct the cycle
                vector<int> cycle;
                for (int x = v; x != u; x = parent[x])
                {
                    cycle.push_back(x);
                }
                cycle.push_back(u);
                cycle.push_back(v);
                cout << "Negative cycle detected: ";
                for (int j = cycle.size() - 1; j >= 0; --j)
                {
                    cout << cycle[j] << " ";
                }
                cout << endl;
                return true;
            }
        }
    }

    return false; // No negative cycle found
}

bool isConnected(Graph &g)
{
    vector<vector<int>> graph = g.getGraph();
    int vertices = g.getVertices();
    vector<bool> visited(vertices, false);
    queue<int> travers;
    travers.push(0);
    int curr;

    while (!travers.empty())
    {
        curr = travers.front();
        visited[curr] = true;
        for (int i : graph[curr])
        {
            if (!visited[i])
            {
                travers.push(i);
            }
        }
        travers.pop();
    }
    for (bool vertex : visited)
    {
        if (!vertex)
        {
            return false;
        }
    }
    return true;
}

vector<int> shortestPath(Graph g, int start, int end)
{
    vector<vector<int>> graph = g.getGraph();
    int vertices = g.getVertices();
    vector<int> dist(vertices, INF);
    vector<bool> visited(vertices, false);
    vector<int> prev(vertices, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if (u == end)
        {
            break;
        }

        if (!visited[u])
        {
            visited[u] = true;

            for (int v = 0; v < vertices; ++v)
            {
                if (graph[u][v] != 0)
                {
                    int alt = dist[u] + graph[u][v];
                    if (alt < dist[v])
                    {
                        dist[v] = alt;
                        prev[v] = u;
                        pq.push({dist[v], v});
                    }
                }
            }
        }
    }
    vector<int> path;
    for (int at = end; at != -1; at = prev[at])
    {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

int isContainsCycle(Graph g)
{
    const vector<vector<int>> &graph = g.getGraph();
    int n = g.getVertices();
    vector<bool> visited(n, false);
    vector<bool> recStack(n, false);
    vector<int> parent(n, -1);

    for (int i = 0; i < n; ++i)
    {
        if (!visited[i])
        {
            if (dfs(i, visited, recStack, graph, parent))
            {
                return 1;
            }
        }
    }

    return 0; // No cycle found
}

int isBipartite(Graph g)
{
    const vector<vector<int>> &graph = g.getGraph();
    int n = g.getVertices();
    vector<int> colors(n, -1); // Initialize colors, -1 indicates uncolored
    bool flag;

    for (int i = 0; i < n; ++i)
    {
        if (colors[i] == -1)
        { // Vertex not visited yet
            if (!isComponentBipartite(i, graph, colors))
            {
                return 0; // Not bipartite
            }
        }
    }

    return 1; // Bipartite
}

int negativeCycle(Graph g)
{
    const vector<vector<int>> &graph = g.getGraph();
    int n = g.getVertices();
    vector<int> distance;
    vector<int> parent;

    for (int i = 0; i < n; ++i)
    {
        if (bellmanFord(i, graph, distance, parent))
        {
            return 1; // Negative cycle found
        }
    }

    return 0; // No negative cycle found
};
