#pragma once

#include "Graph.hpp"
#include <vector>

namespace ariel
{
class Algorithms
{
  public:
    int isConnected(const Graph &g) const;
    std::vector<int> shortestPath(const Graph &g, int start, int end) const;
    int isContainsCycle(const Graph &g) const;
    int isBipartite(const Graph &g) const;
    int negativeCycle(const Graph &g) const;

  private:
    bool dfs(int v, std::vector<bool> &visited, std::vector<bool> &recStack, const std::vector<std::vector<int>> &graph,
             std::vector<int> &parent) const;
    bool isComponentBipartite(int start, const std::vector<std::vector<int>> &graph, std::vector<int> &colors) const;
    bool bellmanFord(int start, const std::vector<std::vector<int>> &graph, std::vector<int> &distance,
                     std::vector<int> &parent) const;
};
} // namespace ariel