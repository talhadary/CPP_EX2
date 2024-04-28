#pragma once

#include "Graph.hpp"
#include <vector>

namespace ariel
{
  class Algorithms
  {
  public:
    static bool isConnected(const Graph &g);
    static vector<int> shortestPath(const Graph &g, int start, int end);
    static bool isContainsCycle(const Graph &g);
    static bool isBipartite(const Graph &g);
    static bool negativeCycle(const Graph &g);

  private:
    static bool dfs(int v, std::vector<bool> &visited, std::vector<bool> &recStack, const std::vector<std::vector<int>> &graph, std::vector<int> &parent);
    static bool isComponentBipartite(int start, const std::vector<std::vector<int>> &graph, std::vector<int> &colors);
    static bool bellmanFord(int start, const std::vector<std::vector<int>> &graph, std::vector<int> &distance, std::vector<int> &parent);
  };
} // namespace ariel