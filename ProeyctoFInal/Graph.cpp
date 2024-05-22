#include "Graph.h"
#include <queue>
#include <functional>
#include <vector>
#include <utility>
#include <limits>
#include <unordered_map>
#include <algorithm>

Graph::Graph(int numVertices) : numVertices(numVertices) {
    adjList.resize(numVertices);
}

void Graph::addEdge(int src, int dest, int weight) {
    adjList[src].emplace_back(dest, weight);
    adjList[dest].emplace_back(src, weight); // Asegurando bidireccionalidad
}

void Graph::addTransfer(int src, int dest, int extraTime) {
    transferTimes[src][dest] = extraTime;
    transferTimes[dest][src] = extraTime; // Asume transferencias bidireccionales
}

std::vector<int> Graph::dijkstra(int src) {
    std::vector<int> dist(numVertices, std::numeric_limits<int>::max());
    prev.resize(numVertices, -1);
    dist[src] = 0;

    using pii = std::pair<int, int>;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
    pq.emplace(0, src);

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const auto& [v, weight] : adjList[u]) {
            int newDist = dist[u] + weight;

            // Considerar el tiempo extra de transferencia si existe
            if (transferTimes[u].find(v) != transferTimes[u].end()) {
                newDist += transferTimes[u][v];
            }

            if (newDist < dist[v]) {
                dist[v] = newDist;
                prev[v] = u;
                pq.emplace(dist[v], v);
            }
        }
    }

    return dist;
}

const std::vector<int>& Graph::getPrev() const {
    return prev;
}

std::vector<int> Graph::getShortestPath(int src, int dest) {
    dijkstra(src);
    std::vector<int> path;
    for (int at = dest; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());
    if (path.size() == 1 && path[0] != src) {
        path.clear(); // No hay ruta
    }
    return path;
}
