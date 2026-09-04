#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

// n: int -- number of nodes, labeled 0..n-1, 1 <= n <= 2*10^5
// edges: vector<vector<int>> -- undirected edges, each edges[i] = {a, b}, 0 <= a,b < n, no self-loops/duplicates
// source, destination: int -- 0 <= source, destination < n
// Returns: bool -- true if a path exists between source and destination
bool solution(int n, vector<vector<int>>& edges, int source, int destination) {
    if (source == destination) return true;

    std::vector<std::vector<int>> adjacencyList(n);

    for (const auto& edge : edges) {
        // Undirected graph means both ways need to be recorded
        adjacencyList[edge[0]].emplace_back(edge[1]);
        adjacencyList[edge[1]].emplace_back(edge[0]);
    }

    std::unordered_set<int> visitedNodes;
    std::queue<int> nextNodes;

    // Start our BFS search
    nextNodes.emplace(source);
    visitedNodes.emplace(source);
    
    while (!nextNodes.empty()) {
        int node = nextNodes.front();

        // Check adjacent nodes and add them to the queue if we haven't visited already
        const auto& adjacencies = adjacencyList[node];
        for (auto connectedNode : adjacencies) {
            if (connectedNode == destination) return true;

            if (visitedNodes.count(connectedNode) == 0) {
                nextNodes.emplace(connectedNode);
                visitedNodes.emplace(connectedNode);
            }
        }

        nextNodes.pop();
    }

    return false;
}
