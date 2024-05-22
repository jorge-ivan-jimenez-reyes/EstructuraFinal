#include "Graph.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

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
    }

    if (!j.contains("transferencias") || !j["transferencias"].is_array()) {
        std::cerr << "Invalid JSON structure: 'transferencias' not found or is not an array" << std::endl;
        return;
    }

    for (const auto& transfer : j["transferencias"]) {
        int src = transfer["origen"];
        int dest = transfer["destino"];
        int extraTime = transfer["tiempo_extra"];
        g.addTransfer(src - 1, dest - 1, extraTime);
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
void printRoute(const std::vector<int>& path) {
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
    loadGraphFromJSON(metrobus, "metrobus_data_corrected.json");

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

        auto allRoutes = metrobus.getAllRoutes(sourceID - 1, destinationID - 1);

        if (allRoutes.empty()) {
            std::cout << "No route found from " << sourceStationName << " to " << destinationStationName << "." << std::endl;
        }
        else {
            std::cout << "All possible routes from " << sourceStationName << " to " << destinationStationName << ":\n";
            for (const auto& route : allRoutes) {
                printRoute(route);
            }
        }
    }

    return 0;
}
