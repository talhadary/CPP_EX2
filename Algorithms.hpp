#pragma once

#include "Graph.hpp"
#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>

const int INF = std::numeric_limits<int>::max();
namespace ariel
{
    class Algorithms
    {
    public:
        static bool isConnected(const Graph &g);
        static std::vector<size_t> shortestPath(const Graph &g, size_t start, size_t end);
        static bool isContainsCycle(const Graph &g);
        static bool isBipartite(const Graph &g);
        static bool negativeCycle(const Graph &g);

    private:
        static bool dfs(ulong v, std::vector<bool> &visited, std::vector<bool> &recStack, const std::vector<std::vector<int>> &graph, std::vector<ulong> &parent);
        static bool isComponentBipartite(ulong start, const std::vector<std::vector<int>> &graph, std::vector<int> &colors);
        static bool bellmanFord(ulong start, const std::vector<std::vector<int>> &graph, std::vector<int> &distance, std::vector<int> &parent);
    };
} // namespace ariel