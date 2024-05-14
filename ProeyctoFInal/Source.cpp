#include "Graph.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>

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
        g.addEdge(src - 1, dest - 1, time);  // Adjust index if necessary
    }
}

int main() {
    int numStations = 272; // Adjust according to the actual number of stations
    Graph metrobus(numStations);

    loadGraphFromJSON(metrobus, "metrobus_data.json");

    int sourceStation = 0; // Example: starting at station 1 (Index 0)
    std::vector<int> minDistances = metrobus.dijkstra(sourceStation);

    if (minDistances.empty()) {
        std::cerr << "Dijkstra's algorithm failed to compute distances." << std::endl;
        return -1;
    }

    for (size_t i = 0; i < minDistances.size(); i++) {
        std::cout << "Minimum distance from station " << sourceStation + 1 << " to station " << i + 1 << " is " << minDistances[i] << std::endl;
    }

    return 0;
}
