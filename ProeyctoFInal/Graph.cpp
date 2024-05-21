#include "Graph.h"
#include <queue>
#include <functional>
#include <vector>
#include <utility>
#include <limits>
#include <string>

Graph::Graph(int numVertices) : numVertices(numVertices) {
    adjList.resize(numVertices);
}

void Graph::addEdge(int src, int dest, int weight) {
    adjList[src].emplace_back(dest, weight);
    adjList[dest].emplace_back(src, weight); // Añadir la conexión en ambas direcciones si es bidireccional
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
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
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

std::string Graph::distanceToString(int distance) const {
    if (distance == std::numeric_limits<int>::max()) {
        return "No route found";
    }
    return std::to_string(distance);
}
