#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <limits>
#include <queue>
#include <utility>

class Graph {
private:
    int numVertices;
    std::vector<std::vector<std::pair<int, int>>> adjList;

public:
    Graph(int vertices);
    void addEdge(int start, int end, int weight);
    void dijkstra(int startVertex);
};

#endif
