#include "Graph.h"
#include <iostream>

Graph::Graph(int vertices) : numVertices(vertices), adjList(vertices) {}

void Graph::addEdge(int start, int end, int weight) {
    adjList[start].push_back(std::make_pair(end, weight));
}

void Graph::dijkstra(int startVertex) {
    std::vector<int> distances(numVertices, std::numeric_limits<int>::max());
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> priorityQueue;

    distances[startVertex] = 0;
    priorityQueue.push(std::make_pair(0, startVertex));

    while (!priorityQueue.empty()) {
        int u = priorityQueue.top().second;
        priorityQueue.pop();

        for (auto& i : adjList[u]) {
            int v = i.first;
            int weight = i.second;

            if (distances[v] > distances[u] + weight) {
                distances[v] = distances[u] + weight;
                priorityQueue.push(std::make_pair(distances[v], v));
            }
        }
    }

    // Output the shortest paths from start vertex.
    std::cout << "Vertex Distance from Source\n";
    for (int i = 0; i < numVertices; i++)
        std::cout << i << "\t\t" << distances[i] << "\n";
}
