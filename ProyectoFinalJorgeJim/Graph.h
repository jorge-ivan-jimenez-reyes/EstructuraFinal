#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;

// Hash function para std::pair
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

class Graph {
public:
    Graph(int numVertices); // Constructor que inicializa el n�mero de v�rtices
    void addEdge(int src, int dest, int weight); // A�adir una arista con peso
    void addTransfer(int src, int dest, int extraTime); // A�adir una transferencia con tiempo extra
    std::vector<int> dijkstra(int src); // Algoritmo de Dijkstra para encontrar el camino m�s corto desde src
    const std::vector<int>& getPrev() const; // Obtener el vector de predecesores
    void printPathWithNames(const std::vector<int>& prev, int dest, const std::unordered_map<int, std::string>& stationIDToName, int totalTime) const; // Imprimir el camino m�s corto con nombres de estaciones y tiempo total
    void printStationInfo(int stationID, const std::unordered_map<int, std::string>& stationIDToName) const; // Imprimir informaci�n de una estaci�n
    void printConnections(int stationID, const std::unordered_map<int, std::string>& stationIDToName) const; // Imprimir conexiones de una estaci�n

private:
    int numVertices; // N�mero de v�rtices en el grafo
    std::vector<std::vector<std::pair<int, int>>> adjList; // Lista de adyacencia
    std::vector<int> prev; // Vector de predecesores
    std::unordered_set<std::pair<int, int>, hash_pair> edgeSet; // Conjunto para almacenar las aristas y evitar duplicados
};

#endif // GRAPH_H
