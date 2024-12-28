Q3.BFS of graph link

Given a connected undirected graph represented by an adjacency list adj, which is a vector of vectors where each adj[i] represents the list of vertices connected to vertex i. Perform a Breadth First Traversal (BFS) starting from vertex 0, visiting vertices from left to right according to the adjacency list, and return a list containing the BFS traversal of the graph.

Note: Do traverse in the same order as they are in the adjacency list.

  #include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> bfsOfGraph(int V, vector<vector<int>>& adj) {
    vector<int> result;  // To store the BFS traversal
    vector<bool> visited(V, false);  // To track visited nodes

    // Create a queue for BFS and start from vertex 0
    queue<int> q;
    q.push(0);
    visited[0] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        result.push_back(node);  // Add the node to the BFS result

        // Visit all unvisited neighbors of the current node
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return result;
}

int main() {
    // Example usage
    int V = 5;  // Number of vertices
    vector<vector<int>> adj = {
        {1, 2, 3},  // neighbors of vertex 0
        {0, 4},     // neighbors of vertex 1
        {0},        // neighbors of vertex 2
        {0},        // neighbors of vertex 3
        {1}         // neighbors of vertex 4
    };

    vector<int> bfsResult = bfsOfGraph(V, adj);
    
    // Print the BFS traversal
    cout << "BFS Traversal: ";
    for (int node : bfsResult) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}

