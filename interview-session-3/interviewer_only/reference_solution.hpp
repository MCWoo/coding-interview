#pragma once
#include <vector>
#include <queue>
using namespace std;

inline bool referenceSolution(int n, vector<vector<int>> edges, int source, int destination) {
    vector<vector<int>> adj(n);
    for (auto& e : edges) {
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);
    }
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(source);
    visited[source] = true;
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        for (int next : adj[cur]) {
            if (!visited[next]) {
                visited[next] = true;
                q.push(next);
            }
        }
    }
    return visited[destination];
}
