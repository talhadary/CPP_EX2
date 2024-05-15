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

    public:
        void loadGraph(const vector<vector<int>> &adjacencyMatrix);
        void printGraph() const;
        const vector<vector<int>> &getGraph() const;
        size_t getVertices() const;
        size_t getEdges() const;
        Graph operator+(const Graph &other);
        Graph operator-(const Graph &other);
        void operator+=(int num);
        void operator-=(int num);
        void operator++();
        void operator++(int);
        void operator--();
        void operator--(int);
        void operator+();
        void operator-();
        bool operator>=(const Graph &other) const;
        bool operator<=(const Graph &other) const;
        bool operator==(const Graph &other) const;
        bool operator!=(const Graph &other) const;
        bool operator>(const Graph &other) const;
        bool operator<(const Graph &other) const;
        Graph operator*(int num);
        Graph operator*(const Graph &other) const;

    private:
        static bool isSquare(const vector<vector<int>> &adjacencyMatrix);
        size_t countVertices() const;
        size_t countEdges() const;
    };
} // namespace ariel
