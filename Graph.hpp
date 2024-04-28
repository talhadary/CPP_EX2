#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>

using namespace std;
class Graph
{
  private:
    vector<vector<int>> graph;
    int vertices;
    int edges;

    bool isSquare(const vector<vector<int>> &graph);
    int countVertices(const vector<vector<int>> &graph);
    int countEdges(const vector<vector<int>> &graph);

  public:
    void loadGraph(vector<vector<int>> &graph);
    void printGraph();
    const vector<vector<int>> &getGraph() const;
    int getVertices() const;
    int getEdges() const;
};

#endif // GRAPH_HPP
