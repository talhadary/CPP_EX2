#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;
namespace ariel
{
  class Graph
  {
  private:
    vector<vector<int>> graph;
    size_t vertices;
    size_t edges;

    static bool isSquare(const vector<vector<int>> &graph);
    size_t countVertices();
    size_t countEdges();

  public:
    void loadGraph(const vector<vector<int>> &graph);
    void printGraph();
    const vector<vector<int>> &getGraph() const;
    size_t getVertices() const;
    size_t getEdges() const;
  };
} // namespace ariel