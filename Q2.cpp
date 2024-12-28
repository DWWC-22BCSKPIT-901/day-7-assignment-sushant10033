Q2.Find if Path Exists in Graph
There is a bi-directional graph with n vertices, where each vertex is labeled from 0 to n - 1 (inclusive). The edges in the graph are represented as a 2D integer array edges, where each edges[i] = [ui, vi] denotes a bi-directional edge between vertex ui and vertex vi. Every vertex pair is connected by at most one edge, and no vertex has an edge to itself.

You want to determine if there is a valid path that exists from vertex source to vertex destination.

Given edges and the integers n, source, and destination, return true if there is a valid path from source to destination, or false otherwise.

  #include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

void dfs(int node, const vector<vector<int>>& graph, unordered_set<int>& visited, int destination, bool& found) {
    // If we find the destination, set found to true
    if (node == destination) {
        found = true;
        return;
    }

    // Mark the node as visited
    visited.insert(node);

    // Visit all the neighbors
    for (int neighbor : graph[node]) {
        if (visited.find(neighbor) == visited.end()) {
            dfs(neighbor, graph, visited, destination, found);
            if (found) return; // If destination found, stop the recursion
        }
    }
}

bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
    // Step 1: Create the adjacency list
    vector<vector<int>> graph(n);
    for (const auto& edge : edges) {
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]); // bi-directional
    }

    // Step 2: Perform DFS
    unordered_set<int> visited;
    bool found = false;
    dfs(source, graph, visited, destination, found);
    return found;
}

int main() {
    // Example usage
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 3}, {4, 5}};
    int n = 6, source = 0, destination = 3;

    cout << "Path exists: " << (validPath(n, edges, source, destination) ? "True" : "False") << endl;
    // Output: Path exists: True

    return 0;
}
