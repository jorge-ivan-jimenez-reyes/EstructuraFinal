#include "Graph.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <utility>
#include <limits>
#include <algorithm>

// Constructor que inicializa la lista de adyacencia con el n�mero de v�rtices
Graph::Graph(int numVertices) : numVertices(numVertices) {
    adjList.resize(numVertices);
}

// M�todo para a�adir una arista bidireccional al grafo
void Graph::addEdge(int src, int dest, int weight) {
    adjList[src].emplace_back(dest, weight); // A�ade arista de src a dest
    adjList[dest].emplace_back(src, weight); // A�ade arista de dest a src para asegurar bidireccionalidad
}

// M�todo para a�adir una transferencia bidireccional al grafo
void Graph::addTransfer(int src, int dest, int extraTime) {
    adjList[src].emplace_back(dest, extraTime); // A�ade transferencia de src a dest
    adjList[dest].emplace_back(src, extraTime); // A�ade transferencia de dest a src para asegurar bidireccionalidad
}

// M�todo que implementa el algoritmo de Dijkstra para encontrar el camino m�s corto desde src
std::vector<int> Graph::dijkstra(int src) {
    std::vector<int> dist(numVertices, std::numeric_limits<int>::max()); // Inicializa las distancias a infinito
    prev.resize(numVertices, -1); // Inicializa el vector de predecesores
    dist[src] = 0; // La distancia a la fuente es 0

    using pii = std::pair<int, int>;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq; // Cola de prioridad para el algoritmo de Dijkstra
    pq.emplace(0, src); // A�ade la fuente a la cola de prioridad

    while (!pq.empty()) {
        int u = pq.top().second; // Obtiene el v�rtice con la menor distancia
        pq.pop(); // Elimina el v�rtice de la cola de prioridad

        for (const auto& [v, weight] : adjList[u]) { // Recorre los vecinos del v�rtice u
            int newDist = dist[u] + weight; // Calcula la nueva distancia

            if (newDist < dist[v]) { // Si la nueva distancia es menor que la distancia actual
                dist[v] = newDist; // Actualiza la distancia
                prev[v] = u; // Actualiza el predecesor
                pq.emplace(dist[v], v); // A�ade el vecino a la cola de prioridad
            }
        }
    }

    return dist; // Devuelve el vector de distancias
}

// M�todo para obtener el vector de predecesores
const std::vector<int>& Graph::getPrev() const {
    return prev;
}

// M�todo para imprimir el camino m�s corto usando nombres de estaciones
void Graph::printPathWithNames(const std::vector<int>& prev, int dest, const std::unordered_map<int, std::string>& stationIDToName) const {
    if (dest < 0 || dest >= prev.size() || prev[dest] == -1) { // Verifica si hay un camino v�lido
        std::cerr << "No route found to the destination." << std::endl;
        return;
    }

    std::vector<int> path; // Vector para almacenar el camino
    for (int at = dest; at != -1; at = prev[at]) { // Recorre el vector de predecesores para construir el camino
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end()); // Invierte el camino para obtener el orden correcto

    std::cout << "Shortest route:" << std::endl;
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << stationIDToName.at(path[i] + 1); // Ajuste para �ndice basado en 1
        if (i < path.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
}

// M�todo para imprimir informaci�n de una estaci�n
void Graph::printStationInfo(int stationID, const std::unordered_map<int, std::string>& stationIDToName) const {
    if (stationID < 0 || stationID >= numVertices) {
        std::cerr << "Error: Invalid station ID." << std::endl;
        return;
    }
    std::cout << "Station ID: " << stationID + 1 << std::endl;
    std::cout << "Station Name: " << stationIDToName.at(stationID + 1) << std::endl;
}

// M�todo para imprimir las conexiones de una estaci�n
void Graph::printConnections(int stationID, const std::unordered_map<int, std::string>& stationIDToName) const {
    if (stationID < 0 || stationID >= numVertices) {
        std::cerr << "Error: Invalid station ID." << std::endl;
        return;
    }
    std::cout << "Connections from " << stationIDToName.at(stationID + 1) << ":" << std::endl;
    for (const auto& [neighbor, weight] : adjList[stationID]) {
        std::cout << " - To " << stationIDToName.at(neighbor + 1) << " with weight " << weight << std::endl;
    }
}
