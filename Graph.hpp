#pragma once

#include <vector>

namespace ariel
{
  class Graph
  {
  private:
    std::vector<std::vector<int>> graph;
    int vertices;
    int edges;

    bool isSquare(const std::vector<std::vector<int>> &graph);
    int countVertices(const std::vector<std::vector<int>> &graph);
    int countEdges(const std::vector<std::vector<int>> &graph);

  public:
    void loadGraph(const std::vector<std::vector<int>> &graph);
    void printGraph() const;
    const std::vector<std::vector<int>> &getGraph() const;
    int getVertices() const;
    int getEdges() const;
  };
} // namespace ariel