#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <functional>

class Graph {
public:
    Graph(int numVertices);
    void addEdge(int src, int dest, int weight);
    std::vector<int> dijkstra(int src);
    const std::vector<int>& getPrev() const;

private:
    int numVertices;
    std::vector<std::vector<std::pair<int, int>>> adjList;
    std::vector<int> prev;
};

#endif // GRAPH_H
