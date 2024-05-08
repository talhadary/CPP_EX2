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

    public:
        void loadGraph(const std::vector<std::vector<int>> &adjacencyMatrix);
        void printGraph() const;
        const std::vector<std::vector<int>> &getGraph() const;
        size_t getVertices() const;
        size_t getEdges() const;
        void addGraphs(const Graph &other);
        void subtractGraphs(const Graph &other);
        void inPlaceAdd(int num);
        void inPlaceSubtract(int num);
        void increment();
        void decrement();
        void unaryPlus();
        void unaryMinus();
        void scalarMultiply(int num);
        Graph multiplyGraphs(const Graph &other) const;

    private:
        static bool isSquare(const std::vector<std::vector<int>> &adjacencyMatrix);
        size_t countVertices() const;
        size_t countEdges() const;
    };
} // namespace ariel
