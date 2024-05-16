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

    Graph g4;

    cout << "g1 + g2 = g4\n" << endl;
    g4 = g1 + g2;
    cout << g4 << endl;

    cout << "g1 - g2 = g4\n" << endl;
    g4 = g2 - g3;
    cout << g4 << endl;

    cout << "g3\n" << endl;
    cout << g3 << endl;
    cout << "g3 += 5\n" << endl;
    cout << g3 << endl;
    g3 += 5;
    cout << g3 << endl;
    
    cout << "g3 -= 5\n" << endl;
    g3 -= 5;
    cout << g3 << endl;

    cout << "++g1\n--g2\n" << endl;
    ++g1;
    --g2;
    cout << g1 << endl;
    cout << g2 << endl;

    cout << "g2++\ng1--\n" << endl;
    g2++;
    g1--;
    cout << g1 << endl ;
    cout << g2 << endl;

    cout << "+g1\n-g2\n" << endl;
    +g1;
    -g2;
    cout << g1 << endl;
    cout << g2 << endl;

    cout << "g4 = g3 * 9\n" << endl;
    g4 = g3 * 9;
    cout << g3 << endl;

    cout << "g4 = g1 * g2\n" << endl;
    g4 = g1 * g2;
    cout << g4 << endl;
}
