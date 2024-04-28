#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <iostream>
#include <vector>

namespace Algorithms {

    class Algorithms {
      public:
        bool isConnected(Graph &g);
        std::vector<int> shortestPath(Graph g, int start, int end);
        int isContainsCycle(Graph g);
        int isBipartite(Graph g);
        int negativeCycle(Graph g);

      private:
        bool dfs(int v, std::vector<bool> &visited, std::vector<bool> &recStack, const std::vector<std::vector<int>> &graph,
                 std::vector<int> &parent);
        bool isComponentBipartite(int start, const std::vector<std::vector<int>> &graph, std::vector<int> &colors);
        bool bellmanFord(int start, const std::vector<std::vector<int>> &graph, std::vector<int> &distance,
                         std::vector<int> &parent);
    };

} // namespace Algorithms

#endif // ALGORITHMS_HPP
