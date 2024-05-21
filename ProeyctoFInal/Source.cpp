#include "Graph.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

// Map to store station name to ID mapping
std::unordered_map<std::string, int> stationNameToID;
std::unordered_map<int, std::string> stationIDToName;

// Function to load graph and station names from JSON
void loadGraphFromJSON(Graph& g, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    nlohmann::json j;
    try {
        inFile >> j;
    }
    catch (const nlohmann::json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        return;
    }

    if (!j.contains("conexiones") || !j["conexiones"].is_array()) {
        std::cerr << "Invalid JSON structure: 'conexiones' not found or is not an array" << std::endl;
        return;
    }

    for (const auto& connection : j["conexiones"]) {
        int src = connection["origen"];
        int dest = connection["destino"];
        int time = connection["tiempo"];
        g.addEdge(src - 1, dest - 1, time);
        g.addEdge(dest - 1, src - 1, time); // Añadir la conexión en ambas direcciones si es bidireccional
    }

    if (!j.contains("estaciones") || !j["estaciones"].is_array()) {
        std::cerr << "Invalid JSON structure: 'estaciones' not found or is not an array" << std::endl;
        return;
    }

    for (const auto& station : j["estaciones"]) {
        int id = station["id"];
        std::string name = station["nombre"];
        stationNameToID[name] = id;
        stationIDToName[id] = name;
    }
}

// Function to get the station ID from name
int getStationID(const std::string& name) {
    auto it = stationNameToID.find(name);
    if (it != stationNameToID.end()) {
        return it->second;
    }
    else {
        std::cerr << "Error: Station name '" << name << "' not found." << std::endl;
        return -1;
    }
}

// Function to print the route from the source to destination
void printRoute(const std::vector<int>& prev, int dest) {
    if (dest < 0 || dest >= prev.size() || prev[dest] == -1) {
        std::cerr << "No route found to the destination." << std::endl;
        return;
    }

    std::vector<int> path;
    for (int at = dest; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    std::cout << "Shortest route:" << std::endl;
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << stationIDToName[path[i] + 1]; // Adjusting for 1-based indexing
        if (i < path.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
}

int main() {
    int numStations = 272; // Adjust according to the actual number of stations
    Graph metrobus(numStations);

    // Load the graph and station names from the JSON file
    loadGraphFromJSON(metrobus, "metrobus_data.json");

    while (true) {
        std::string sourceStationName, destinationStationName;

        std::cout << "Enter source station name: ";
        std::getline(std::cin, sourceStationName);
        std::cout << "Enter destination station name: ";
        std::getline(std::cin, destinationStationName);

        int sourceID = getStationID(sourceStationName);
        int destinationID = getStationID(destinationStationName);

        if (sourceID == -1 || destinationID == -1) {
            std::cerr << "Error: Invalid station names. Please try again." << std::endl;
            continue;
        }

        std::vector<int> minDistances = metrobus.dijkstra(sourceID - 1);
        std::vector<int> prev = metrobus.getPrev(); // Assuming you have a method to get the previous nodes

        if (minDistances[destinationID - 1] == std::numeric_limits<int>::max()) {
            std::cout << "No route found from " << sourceStationName << " to " << destinationStationName << "." << std::endl;
        }
        else {
            std::cout << "Minimum distance from " << sourceStationName << " to " << destinationStationName << " is "
                << metrobus.distanceToString(minDistances[destinationID - 1]) << " units." << std::endl;
            printRoute(prev, destinationID - 1);
        }
    }

    return 0;
}
