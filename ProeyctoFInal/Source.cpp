#include "Graph.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

// Mapa para almacenar el mapeo de ID a nombre de estación
std::unordered_map<int, std::string> stationIDToName;

// Función para cargar el grafo y los nombres de estaciones desde un archivo JSON
void loadGraphFromJSON(Graph& g, const std::string& filename) {
    std::ifstream inFile(filename); // Abre el archivo JSON
    if (!inFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    nlohmann::json j;
    try {
        inFile >> j; // Lee el archivo JSON
    }
    catch (const nlohmann::json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        return;
    }

    if (!j.contains("conexiones") || !j["conexiones"].is_array()) { // Verifica la existencia y el formato del campo 'conexiones'
        std::cerr << "Invalid JSON structure: 'conexiones' not found or is not an array" << std::endl;
        return;
    }

    // Carga las conexiones
    for (const auto& connection : j["conexiones"]) {
        int src = connection["origen"];
        int dest = connection["destino"];
        int time = connection["tiempo"];
        g.addEdge(src - 1, dest - 1, time); // Ajusta para índice basado en 0
    }

    if (!j.contains("transferencias") || !j["transferencias"].is_array()) { // Verifica la existencia y el formato del campo 'transferencias'
        std::cerr << "Invalid JSON structure: 'transferencias' not found or is not an array" << std::endl;
        return;
    }

    // Carga las transferencias
    for (const auto& transfer : j["transferencias"]) {
        int src = transfer["origen"];
        int dest = transfer["destino"];
        int extraTime = transfer["tiempo_extra"];
        g.addTransfer(src - 1, dest - 1, extraTime); // Ajusta para índice basado en 0
    }

    if (!j.contains("estaciones") || !j["estaciones"].is_array()) { // Verifica la existencia y el formato del campo 'estaciones'
        std::cerr << "Invalid JSON structure: 'estaciones' not found or is not an array" << std::endl;
        return;
    }

    // Carga las estaciones
    for (const auto& station : j["estaciones"]) {
        int id = station["id"];
        std::string name = station["nombre"];
        stationIDToName[id] = name; // Almacena el mapeo de ID a nombre
    }
}

// Función principal
int main() {
    int numStations = 272; // Ajusta según el número real de estaciones
    Graph metrobus(numStations);

    // Carga el grafo y los nombres de las estaciones desde el archivo JSON
    loadGraphFromJSON(metrobus, "metrobus_data_corrected.json");

    while (true) {
        int sourceID, destinationID;
        std::cout << "Enter source station ID: ";
        std::cin >> sourceID;
        std::cout << "Enter destination station ID: ";
        std::cin >> destinationID;

        if (sourceID <= 0 || destinationID <= 0 || sourceID > numStations || destinationID > numStations) {
            std::cerr << "Error: Invalid station IDs. Please try again." << std::endl;
            continue;
        }

        std::vector<int> minDistances = metrobus.dijkstra(sourceID - 1); // Ejecuta Dijkstra desde la estación de origen
        std::vector<int> prev = metrobus.getPrev(); // Obtiene el vector de predecesores

        if (minDistances[destinationID - 1] == std::numeric_limits<int>::max()) {
            std::cout << "No route found from " << stationIDToName[sourceID] << " to " << stationIDToName[destinationID] << "." << std::endl;
        }
        else {
            std::cout << "Minimum distance from " << stationIDToName[sourceID] << " to " << stationIDToName[destinationID] << " is "
                << minDistances[destinationID - 1] << " units." << std::endl;
            metrobus.printPathWithNames(prev, destinationID - 1, stationIDToName); // Imprime la ruta más corta con nombres de estaciones
        }
    }

    return 0;
}
