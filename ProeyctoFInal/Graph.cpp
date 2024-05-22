#include "Graph.h"
#include <queue>
#include <functional>
#include <vector>
#include <utility>
#include <limits>
#include <unordered_map>

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

void Graph::dfs(int u, int dest, std::vector<bool>& visited, std::vector<int>& path, std::vector<std::vector<int>>& allPaths) {
    visited[u] = true;
    path.push_back(u);

    if (u == dest) {
        allPaths.push_back(path);
    }
    else {
        for (const auto& [v, weight] : adjList[u]) {
            if (!visited[v]) {
                dfs(v, dest, visited, path, allPaths);
            }
        }
    }

    path.pop_back();
    visited[u] = false;
}

std::vector<std::vector<int>> Graph::getAllRoutes(int src, int dest) {
    std::vector<bool> visited(numVertices, false);
    std::vector<int> path;
    std::vector<std::vector<int>> allPaths;
    dfs(src, dest, visited, path, allPaths);
    return allPaths;
}
