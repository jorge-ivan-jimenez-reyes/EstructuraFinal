// Graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <limits>

class Graph {
public:
    int numVertices;
    std::vector<std::vector<std::pair<int, int>>> adjList;

    Graph(int vertices);
    void addEdge(int src, int dest, int weight);
    std::vector<int> dijkstra(int source);
};

#endif
