#include "Graph.h"
#include <iostream>

using namespace std;

Graph::Graph(int vertices) : numVertices(vertices), adjList(vertices) {}

void Graph::addEdge(int start, int end, int weight) {
    adjList[start].push_back(make_pair(end, weight));
}

void Graph::dijkstra(int startVertex) {
    vector<int> distances(numVertices, numeric_limits<int>::max());
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> priorityQueue;

    distances[startVertex] = 0;
    priorityQueue.push(make_pair(0, startVertex));

    while (!priorityQueue.empty()) {
        int u = priorityQueue.top().second;
        priorityQueue.pop();

        for (auto& i : adjList[u]) {
            int v = i.first;
            int weight = i.second;

            if (distances[v] > distances[u] + weight) {
                distances[v] = distances[u] + weight;
                priorityQueue.push(make_pair(distances[v], v));
            }
        }
    }





    cout << "Vertex Distance from Source\n";
    for (int i = 0; i < numVertices; i++)
        cout << i << "\t\t" << distances[i] << "\n";
}
