#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

class Graph {
public:
    Graph(int numVertices); // Constructor que inicializa el n�mero de v�rtices
    void addEdge(int src, int dest, int weight); // A�adir una arista con peso
    void addTransfer(int src, int dest, int extraTime); // A�adir una transferencia con tiempo extra
    std::vector<int> dijkstra(int src); // Algoritmo de Dijkstra para encontrar el camino m�s corto desde src
    const std::vector<int>& getPrev() const; // Obtener el vector de predecesores
    void printPathWithNames(const std::vector<int>& prev, int dest, const std::unordered_map<int, std::string>& stationIDToName) const; // Imprimir el camino m�s corto con nombres de estaciones
    void printStationInfo(int stationID, const std::unordered_map<int, std::string>& stationIDToName) const; // Imprimir informaci�n de una estaci�n
    void printConnections(int stationID, const std::unordered_map<int, std::string>& stationIDToName) const; // Imprimir conexiones de una estaci�n

private:
    int numVertices; // N�mero de v�rtices en el grafo
    std::vector<std::vector<std::pair<int, int>>> adjList; // Lista de adyacencia
    std::vector<int> prev; // Vector de predecesores
};

#endif // GRAPH_H
