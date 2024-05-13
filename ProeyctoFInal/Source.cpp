#include "Graph.h"

int main() {
    int numStations = 5; // Ejemplo: n�mero de estaciones
    Graph mb(numStations);

    // A�adir rutas como ejemplos (deber�an cargarse de datos reales)
    mb.addEdge(0, 1, 10);
    mb.addEdge(1, 2, 20);
    mb.addEdge(0, 2, 30);
    mb.addEdge(1, 3, 40);
    mb.addEdge(2, 4, 50);

    int startVertex = 0; // Iniciar la ruta desde la estaci�n 0
    mb.dijkstra(startVertex);

    return 0;
}
