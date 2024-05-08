# CPP_EX1_24

## Overview
This project implements various graph algorithms using C++. The algorithms include determining strong connectivity, finding shortest paths, detecting cycles, checking bipartiteness, and identifying negative cycles in a graph.

## Files
- `Graph.cpp`: Contains the implementation of the Graph class, which represents a graph using an adjacency matrix. It includes methods to load a graph from an adjacency matrix and to print the graph.
- `Graph.hpp`: The header file for `Graph.cpp`, contains the declaration of the ariel namespace, the Graph class and its data members.
- `Algorithms.cpp`: Implements the graph algorithms mentioned above.
- `Algorithms.hpp`: The header file for `Algorithms.cpp`, contains the declaration of the ariel namespace, the Algorithms class and its data members.

## Graph Implementation

The Graph Class, which is part of the ariel namespace, contains private data members and member functions:
1. `graph`: An adjacency matrix (2-dimensional vector int array) representing the vertices and the edges between them.
2. `vertices`: A count of how many vertices the graph contains.
3. `edges`: A count of how many edges the graph has. I chose to count the edges as if all the graphs are directed, meaning undirected graphs are directed graphs with edges in both directions.
4. `isSquare()`: Validity check for the adjacency matrix. Checks if the matrix has a size and if it's a square matrix.
5. `countVertices()`: Returns the size of the adjacency matrix (number of rows).
6. `countEdges`: Since we consider every graph as a directed graph here, we go over every vertex, and count how many edges it has (count every connection twice), and return the value.

The Graph class also has public data members and member functions:
7. `loadGraph(graph)`: Receives an adjacency matrix, checks its validity using isSquare(). If it's valid, updates the graph private data member, if it's not, throws an exception.
8. `printGraph()`: Prints out "Graph with x vertices and y edges", then prints the graph in the following format:
                                            
{0, 1, 0}
{1, 0, 1}
{0, 1, 0}

3. `getGraph()`: Returns the Adjacency matrix by reference.
4. `getVertices()`: Returns private data member `vertices` by value.
5. `getEdges()`: Return private data member `edges` by value.

## Algorithms Implementations

All the algorithms treat all graphs as directed graphs! undirected graphs are just directed graphs with edges going both ways.

1. `isConnected(g)`: Determines if the graph 'g' is strongly connected using a modified BFS. Traverses in BFS through the graph and keeps track of visited vertices. Then checks if we visited all the vertices. Does this to each vertex in the graph (in case of a directed graph). If every time we visited each vertex, the graph is strongly connected.
2. `shortestPath(g, start, end)`: Uses Bellman-Ford algorithm to find the shortest path between any two vertices in a graph. If it doesn't exist, it returns an empty array. IF there's a negative loop changes the distance of every affected vertex to negative infinite, and there is no shortest path between any vertex and this one. The algorithm works as follows:
    - Initialize a list of distances to each vertex, with the value of infinity, and change the start vertex to 0.
    - Initialize a list of the previous vertex to each vertex you reach (e.g., prev[1] = 0 meaning we got to vertex 1 from vertex 0).
    - Begin from the start vertex and check the distance to each vertex using the first path you find. If the new distance to each node you reach is smaller than the current (infinity), switch it for the new one.
    - Do that again n-1 times, each time use the new best path and try to optimize it.
    - if we can optimize again, there's a negative cycle. optimize every affected veertex n-1 more times to -INF.
    - When you can't optimize it anymore, reconstruct the path using the prev list and return it.
3. `isContainsCycle(g)`: Detects if there is any cycle in graph 'g' using a DFS. It works as follows:
    - Initializing visited array to keep track of visited vertices. Initializing recStack array to keep track of the vertices we visited during the current search. Initializing parent array to keep track of which vertex came after which.
    - For each vertex we didn't visit before, do a DFS.
    - If during the search we come across the same vertex twice, we found a cycle. Reconstruct it using the parent and recStack arrays. Print the cycle and return true.
    - If we didn't find a cycle in any of the searches, return false.
4. `isBipartite(g)`: Checks if the graph 'g' is bipartite. The algorithm works as follows:
    - Initializing colors array with all elements as INF. We send each vertex with the color INF (not visited) to a helper method, where we initialize a queue.
    - In the helper method, we iterate over the graph from the start vertex and check the color of each vertex we get to. If it's not colored, color it opposite of the previous vertex. If it is colored the same as the previous vertex, the graph is not bipartite, return false, else do nothing. If after going over all vertices we didn't return false, return true. Print the possible color groups.
5. `negativeCycle(g)`: Identifies a negative cycle in graph 'g' using Bellman Ford algorithm. It works similarly to `shortestPath()`. After we find the shortest path possible with n-1 iterations, if we can still improve it, that means we can infinitely improve it. That is because there's a cycle with a negative net distance. Create a new array, and backtrack while adding the vertices to the array, then return the array and return true. If no cycles are found, return false.

## Contributor
- [Tal Hadary](ID:326648706)
