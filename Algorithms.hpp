#pragma once

#include "Graph.hpp"
#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>

using namespace std;
const int INF = numeric_limits<int>::max();
namespace ariel
{
    class Algorithms
    {
    public:
        static bool isConnected(const Graph &g);
        static vector<size_t> shortestPath(const Graph &g, size_t start, size_t end);
        static bool isContainsCycle(const Graph &g);
        static bool isBipartite(const Graph &g);
        static bool negativeCycle(const Graph &g);

    private:
        static bool dfs(ulong v, vector<bool> &visited, vector<bool> &recStack, const vector<vector<int>> &graph, vector<ulong> &parent);
        static bool isComponentBipartite(ulong start, const vector<vector<int>> &graph, vector<int> &colors);
        static bool bellmanFord(ulong start, const vector<vector<int>> &graph, vector<int> &distance, vector<int> &parent);
    };
} // namespace ariel