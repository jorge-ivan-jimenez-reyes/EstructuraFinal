#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

class Graph {
public:
    Graph(int numVertices); // Constructor que inicializa el número de vértices
    void addEdge(int src, int dest, int weight); // Añadir una arista con peso
    void addTransfer(int src, int dest, int extraTime); // Añadir una transferencia con tiempo extra
    std::vector<int> dijkstra(int src); // Algoritmo de Dijkstra para encontrar el camino más corto desde src
    const std::vector<int>& getPrev() const; // Obtener el vector de predecesores
    void printPathWithNames(const std::vector<int>& prev, int dest, const std::unordered_map<int, std::string>& stationIDToName) const; // Imprimir el camino más corto con nombres de estaciones
    void printStationInfo(int stationID, const std::unordered_map<int, std::string>& stationIDToName) const; // Imprimir información de una estación
    void printConnections(int stationID, const std::unordered_map<int, std::string>& stationIDToName) const; // Imprimir conexiones de una estación

private:
    int numVertices; // Número de vértices en el grafo
    std::vector<std::vector<std::pair<int, int>>> adjList; // Lista de adyacencia
    std::vector<int> prev; // Vector de predecesores
};

#endif // GRAPH_H
