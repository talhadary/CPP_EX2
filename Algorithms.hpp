#pragma once

#include "Graph.hpp"
#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>

using namespace std;
const int INF = numeric_limits<int>::max();
const int NEG_INF = numeric_limits<int>::min();

namespace ariel
{
    class Algorithms
    {
    private:
        static bool dfs(size_t v, vector<bool> &visited, vector<bool> &recStack, const vector<vector<int>> &graph, vector<size_t> &parent);
        static bool isComponentBipartite(size_t start, const vector<vector<int>> &graph, vector<size_t> &colors, vector<vector<size_t>> &groups);
        static bool bellmanFord(size_t start, const vector<vector<int>> &graph, vector<int> &distance, vector<size_t> &parent);
    
    public:
        static bool isConnected(const Graph &g);
        static vector<size_t> shortestPath(const Graph &g, size_t start, size_t end);
        static bool isContainsCycle(const Graph &g);
        static bool isBipartite(const Graph &g);
        static bool negativeCycle(const Graph &g);
    };

} // namespace ariel