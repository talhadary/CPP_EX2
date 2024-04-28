#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;
using ariel::Algorithms;
using ariel::Graph;

bool Algorithms::dfs(ulong v, vector<bool> &visited, vector<bool> &recStack, const vector<vector<int>> &graph, vector<ulong> &parent)
{
    visited[v] = true;
    recStack[v] = true;

    for (ulong i = 0; i < graph[v].size(); ++i)
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

bool Algorithms::isComponentBipartite(ulong start, const vector<vector<int>> &graph, vector<int> &colors)
{
    queue<ulong> q;
    q.push(start);
    colors[start] = 0;

    while (!q.empty())
    {
        ulong current = q.front();
        q.pop();

        for (ulong neighbor = 0; neighbor < graph[current].size(); ++neighbor)
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
    for (ulong i = 0; i < colors.size(); i++)
    {
        if (colors[i] == 0)
        {
            cout << i + 1 << " ";
        }
    }
    cout << "}" << endl;

    cout << "Group B = {";
    for (ulong i = 0; i < colors.size(); i++)
    {
        if (colors[i] == 1)
        {
            cout << i + 1 << " ";
        }
    }
    cout << "}" << endl;

    return true;
}

bool Algorithms::bellmanFord(ulong start, const vector<vector<int>> &graph, vector<int> &distance, vector<int> &parent)
{
    ulong n = graph.size();
    distance.assign(n, INF);
    parent.assign(n, -1);
    distance[start] = 0;

    for (ulong i = 0; i < n - 1; ++i)
    {
        for (ulong u = 0; u < n; ++u)
        {
            for (ulong v = 0; v < n; ++v)
            {
                if (graph[u][v] != 0 && distance[u] != INF && distance[u] + graph[u][v] < distance[v])
                {
                    distance[v] = distance[u] + graph[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    for (ulong u = 0; u < n; ++u)
    {
        for (ulong v = 0; v < n; ++v)
        {
            if (graph[u][v] != 0 && distance[u] != INF && distance[u] + graph[u][v] < distance[v])
            {
                return true;
            }
        }
    }

    return false;
}

bool Algorithms::isConnected(const Graph &g)
{
    vector<vector<int>> graph = g.getGraph();
    ulong vertices = ulong(g.getVertices());
    vector<bool> visited(vertices, false);
    queue<ulong> travers;

    travers.push(0); // Start traversal from vertex 0

    while (!travers.empty())
    {
        ulong curr = travers.front();
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

vector<size_t> Algorithms::shortestPath(const Graph &g, size_t start, size_t end)
{
    vector<vector<int>> graph = g.getGraph();
    size_t vertices = g.getVertices();
    vector<int> dist(vertices, INF);
    vector<bool> visited(vertices, false);
    vector<size_t> prev(vertices, INF);
    priority_queue<pair<size_t, size_t>, vector<pair<size_t, size_t>>, greater<pair<size_t, size_t>>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty())
    {
        size_t u = pq.top().second;
        pq.pop();

        if (u == end)
        {
            break;
        }

        if (!visited[u])
        {
            visited[u] = true;

            for (size_t v = 0; v < vertices; ++v)
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

    vector<size_t> path;
    if (prev[end] != INF)
    {
        for (size_t at = end; at != INF; at = prev[at])
        {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());
    }
    else
    {
        path.push_back(start);
    }

    return path;
}

bool Algorithms::isContainsCycle(const Graph &g)
{
    const vector<vector<int>> &graph = g.getGraph();
    size_t n = g.getVertices();
    vector<bool> visited(n, false);
    vector<bool> recStack(n, false);
    vector<ulong> parent(n, INF);

    for (ulong i = 0; i < n; ++i)
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

bool Algorithms::isBipartite(const Graph &g)
{
    const vector<vector<int>> &graph = g.getGraph();
    size_t n = g.getVertices();
    vector<int> colors(n, -1); // Initialize colors, -1 indicates uncolored

    for (ulong i = 0; i < n; ++i)
    {
        if (colors[i] == -1)
        { // Vertex not visited yet
            if (!isComponentBipartite(i, graph, colors))
            {
                return false; // Not bipartite
            }
        }
    }

    return true; // Bipartite
}

bool Algorithms::negativeCycle(const Graph &g)
{
    const vector<vector<int>> &graph = g.getGraph();
    size_t n = g.getVertices();
    vector<int> distance;
    vector<int> parent;

    for (size_t i = 0; i < n; ++i)
    {
        if (bellmanFord(i, graph, distance, parent))
        {
            return true; // Negative cycle found
        }
    }

    return false; // No negative cycle found
}
