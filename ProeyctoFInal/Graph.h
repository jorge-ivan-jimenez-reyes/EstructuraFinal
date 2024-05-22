#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <functional>
#include <unordered_map>

class Graph {
public:
    Graph(int numVertices);
    void addEdge(int src, int dest, int weight);
    void addTransfer(int src, int dest, int extraTime);
    std::vector<int> dijkstra(int src);
    const std::vector<int>& getPrev() const;
    std::vector<std::vector<int>> getAllRoutes(int src, int dest);

private:
    int numVertices;
    std::vector<std::vector<std::pair<int, int>>> adjList;
    std::vector<int> prev;
    std::unordered_map<int, std::unordered_map<int, int>> transferTimes;

    void dfs(int u, int dest, std::vector<bool>& visited, std::vector<int>& path, std::vector<std::vector<int>>& allPaths);
};

#endif // GRAPH_H
