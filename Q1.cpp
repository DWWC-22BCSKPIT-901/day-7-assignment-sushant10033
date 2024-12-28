Q1. Find Center of Star Graph
There is an undirected star graph consisting of n nodes labeled from 1 to n. A star graph is a graph where there is one center node and exactly n - 1 edges that connect the center node with every other node.

You are given a 2D integer array edges where each edges[i] = [ui, vi] indicates that there is an edge between the nodes ui and vi. Return the center of the given star graph.
#include <iostream>
#include <vector>
using namespace std;

int findCenter(vector<vector<int>>& edges) {
    // The center will be the common node between the first two edges
    int node1 = edges[0][0];
    int node2 = edges[0][1];
    
    // Check which node is common in the next edge
    if (edges[1][0] == node1 || edges[1][1] == node1) {
        return node1;
    } else {
        return node2;
    }
}

int main() {
    // Example usage
    vector<vector<int>> edges = {{1, 2}, {2, 3}, {4, 2}};
    cout << "Center of the star graph: " << findCenter(edges) << endl; // Output: 2
    
    return 0;
}
