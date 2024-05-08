/*
 * Demo program for Exercise 2.
 * Author: Tal Hadary.
 */

#include "Graph.hpp"
#include "Algorithms.hpp"
using ariel::Algorithms;
using ariel::Graph;
using namespace std;

int main()
{
    Graph g1;
    Graph g2;
    Graph g3;

    vector<vector<int>> graph1 = 
    {{1, 0, 0, 0},
     {0,-2, 0, 3},
     {0, 0, 3, 5},
     {0, 0, 0, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = 
    {{0, 0, 0, 0},
     {0,-2, 0,-3},
     {1, 1, 3, 5},
     {0,-10, 0, 0}};
    g2.loadGraph(graph2);

    vector<vector<int>> graph3 = 
    {{0, 1, 1, 0},
     {1, 0, 0, 1},
     {1, 0, 0, 1},
     {0, 1, 1, 0}};
    g3.loadGraph(graph3);

    vector<vector<int>> graph4;
    vector<vector<int>> graph5;

    g1.addGraphs(g2);
    g1.printGraph();

    g2.subtractGraphs(g3);
    g2.printGraph();

    g3.inPlaceAdd(5);
    g3.printGraph();
    g3.inPlaceSubtract(3);
    g3.printGraph();

    g1.increment();
    g2.decrement();
    g1.printGraph();
    g2.printGraph();

    g1.unaryPlus();
    g2.unaryMinus();
    g1.printGraph();
    g2.printGraph();

    g3.scalarMultiply(9);
    g3.printGraph();

    Graph g = g1.multiplyGraphs(g2);
    g.printGraph();
}
