#pragma once

#include "Graph.hpp"
#include <vector>

namespace ariel
{
class Algorithms
{
  public:
    bool isConnected(const Graph &g) const;
    std::vector<int> shortestPath(const Graph &g, int start, int end) const;
    bool isContainsCycle(const Graph &g) const;
    bool isBipartite(const Graph &g) const;
    bool negativeCycle(const Graph &g) const;

  private:
    bool dfs(int v, std::vector<bool> &visited, std::vector<bool> &recStack, const std::vector<std::vector<int>> &graph,
             std::vector<int> &parent);
    bool isComponentBipartite(int start, const std::vector<std::vector<int>> &graph, std::vector<int> &colors);
    bool bellmanFord(int start, const std::vector<std::vector<int>> &graph, std::vector<int> &distance,
                     std::vector<int> &parent);
};
} // namespace ariel