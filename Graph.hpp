#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>

namespace ariel
{
  class Graph
  {
  private:
    std::vector<std::vector<int>> graph;
    int vertices;
    int edges;

    bool isSquare();
    int countVertices();
    int countEdges();

  public:
    void loadGraph(const std::vector<std::vector<int>> &graph);
    void printGraph() const;
    const std::vector<std::vector<int>> &getGraph() const;
    int getVertices() const;
    int getEdges() const;
  };
} // namespace ariel