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

    vector<vector<int>> graph1 = 
    {{1, 0, 0, 0},
     {0,-2, 0, 3},
     {0, 0, 3, 5},
     {0, 0, 0, 0}};
    g1.loadGraph(graph1);
    g1.printGraph();

    Algorithms::isConnected(g1);
    Algorithms::isBipartite(g1);
    Algorithms::isContainsCycle(g1);
    Algorithms::negativeCycle(g1);
    vector<size_t> path1 = Algorithms::shortestPath(g1, 0, 3);

    if (path1.size() == 0)
    {
        cout<< "no path!" << endl;
    }
    else
    {
        for (size_t vertex : path1)
        {
            cout << vertex << " ";
        }
        cout << endl;
    }

    Graph g2;

    vector<vector<int>> graph2 = 
    {{0, 0, 0, 0},
     {0,-2, 0,-3},
     {1, 1, 3, 5},
     {0,-10, 0, 0}};
    
    g2.loadGraph(graph2);
    g2.printGraph();

    Algorithms::isConnected(g2);
    Algorithms::isBipartite(g2);
    Algorithms::isContainsCycle(g2);
    Algorithms::negativeCycle(g2);
    vector<size_t> path2 = Algorithms::shortestPath(g2, 3, 1);

    if (path2.size() == 0)
    {
        cout<< "no path!" << endl;
    }
    else
    {
        for (size_t vertex : path2)
        {
            cout << vertex << " ";
        }
        cout << endl;
    }

    Graph g3;

    vector<vector<int>> graph3 = 
    {{0, 1, 1, 0},
     {1, 0, 0, 1},
     {1, 0, 0, 1},
     {0, 1, 1, 0}};
    
    g3.loadGraph(graph3);
    g3.printGraph();

    Algorithms::isConnected(g3);
    Algorithms::isBipartite(g3);
    Algorithms::isContainsCycle(g3);
    Algorithms::negativeCycle(g3);
    vector<size_t> path3 = Algorithms::shortestPath(g3, 3, 2);

    if (path3.size() == 0)
    {
        cout<< "no path!" << endl;
    }
    else
    {
        for (size_t vertex : path3)
        {
            cout << vertex << " ";
        }
        cout << endl;
    }
}
