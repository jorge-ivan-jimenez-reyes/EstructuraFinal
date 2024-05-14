
#include <vector>
#include <limits>
#include <queue>
#include <utility>

using namespace std;

class Graph {
private:
    int numVertices;
    vector<vector<pair<int, int>>> adjList;

public:
    Graph(int vertices);
    void addEdge(int start, int end, int weight);
    void dijkstra(int startVertex);
};
