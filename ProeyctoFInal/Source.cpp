#include "Graph.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

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

// Función para mostrar el menú de opciones
void showMenu() {
    std::cout << "1. Find shortest route between two stations" << std::endl;
    std::cout << "2. Display station information" << std::endl;
    std::cout << "3. Display station connections" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

// Función principal
int main() {
    int numStations = 272; // Ajusta según el número real de estaciones
    Graph metrobus(numStations);

    // Carga el grafo y los nombres de las estaciones desde el archivo JSON automáticamente
    loadGraphFromJSON(metrobus, "metrobus_data_corrected.json");

    bool exit = false;
    while (!exit) {
        showMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
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
            break;
        }
        case 2: {
            int stationID;
            std::cout << "Enter station ID: ";
            std::cin >> stationID;

            metrobus.printStationInfo(stationID - 1, stationIDToName); // Imprime información de la estación
            break;
        }
        case 3: {
            int stationID;
            std::cout << "Enter station ID: ";
            std::cin >> stationID;

            metrobus.printConnections(stationID - 1, stationIDToName); // Imprime conexiones de la estación
            break;
        }
        case 4:
            exit = true;
            std::cout << "Exiting program." << std::endl;
            break;
        default:
            std::cerr << "Invalid choice. Please try again." << std::endl;
            break;
        }
    }

    return 0;
}
