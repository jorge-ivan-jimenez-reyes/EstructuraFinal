// main.cpp
#include "Graph.h"
#include <iostream>
#include <fstream>
#include "json.hpp"

void loadGraphFromJSON(Graph& g, const std::string& filename) {
    std::ifstream inFile(filename);
    nlohmann::json j;
    inFile >> j;

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

    for (int i = 0; i < minDistances.size(); i++) {
        std::cout << "Minimum distance from station " << sourceStation + 1 << " to station " << i + 1 << " is " << minDistances[i] << std::endl;
    }

    return 0;
}
