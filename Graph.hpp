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
    size_t vertices;
    size_t edges;

    static bool isSquare(const std::vector<std::vector<int>> &graph);
    size_t countVertices();
    size_t countEdges();

  public:
    void loadGraph(const std::vector<std::vector<int>> &graph);
    void printGraph();
    const std::vector<std::vector<int>> &getGraph() const;
    size_t getVertices() const;
    size_t getEdges() const;
  };
} // namespace ariel