Q4. Minimum Height Trees

A tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.

Given a tree of n nodes labelled from 0 to n - 1, and an array of n - 1 edges where edges[i] = [ai, bi] indicates that there is an undirected edge between the two nodes ai and bi in the tree, you can choose any node of the tree as the root. When you select a node x as the root, the result tree has height h. Among all possible rooted trees, those with minimum height (i.e. min(h))  are called minimum height trees (MHTs).

Return a list of all MHTs' root labels. You can return the answer in any order.

The height of a rooted tree is the number of edges on the longest downward path between the root and a leaf.

  #include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
    if (n == 1) return {0};  // Special case: Single node tree

    // Step 1: Build the graph (adjacency list)
    vector<vector<int>> adj(n);
    for (const auto& edge : edges) {
        adj[edge[0]].push_back(edge[1]);
        adj[edge[1]].push_back(edge[0]);
    }

    // Step 2: BFS to find the farthest node from an arbitrary node (node 0)
    auto bfs = [&](int start) -> pair<int, vector<int>> {
        vector<int> dist(n, -1);
        queue<int> q;
        q.push(start);
        dist[start] = 0;
        int farthestNode = start;
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            for (int neighbor : adj[node]) {
                if (dist[neighbor] == -1) {
                    dist[neighbor] = dist[node] + 1;
                    q.push(neighbor);
                    if (dist[neighbor] > dist[farthestNode]) {
                        farthestNode = neighbor;
                    }
                }
            }
        }
        return {farthestNode, dist};  // Return the farthest node and distances
    };

    // Step 3: Find the farthest node from node 0
    auto [farthestFromStart, _] = bfs(0);

    // Step 4: Find the farthest node from farthestFromStart (this gives us the diameter)
    auto [farthestNode, distFromFarthest] = bfs(farthestFromStart);

    // Step 5: Find the centers (middle of the longest path)
    vector<int> result;
    int maxDist = distFromFarthest[farthestNode];
    int midDist = maxDist / 2;

    // Trace back from farthestNode to find the center(s)
    for (int i = 0; i < n; ++i) {
        if (distFromFarthest[i] == midDist || distFromFarthest[i] == midDist + 1) {
            result.push_back(i);
        }
    }

    return result;
}

int main() {
    // Example usage
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {0, 3}, {3, 4}};
    int n = 5;
    vector<int> result = findMinHeightTrees(n, edges);

    cout << "Minimum Height Trees roots: ";
    for (int root : result) {
        cout << root << " ";
    }
    cout << endl;

    return 0;
}
