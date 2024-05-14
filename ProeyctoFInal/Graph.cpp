// Graph.cpp
#include "Graph.h"
#include <queue>

Graph::Graph(int vertices) : numVertices(vertices), adjList(vertices) {}

void Graph::addEdge(int src, int dest, int weight) {
    adjList[src].push_back(std::make_pair(dest, weight));
}

std::vector<int> Graph::dijkstra(int source) {
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    std::vector<int> dist(numVertices, std::numeric_limits<int>::max());

    pq.push(std::make_pair(0, source));
    dist[source] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto& p : adjList[u]) {
            int v = p.first;
            int weight = p.second;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(std::make_pair(dist[v], v));
            }
        }
    }
    return dist;
}
