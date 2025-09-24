#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Prim's Algorithm
void prim(int start, vector<vector<pair<int,int>>> &graph) {
    int n = graph.size();
    vector<int> key(n, INT_MAX);       // Minimum weight to include node in MST
    vector<int> parent(n, -1);         // Store MST edges
    vector<bool> inMST(n, false);      // Track included nodes

    // Min-heap: pair(weight, node)
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    key[start] = 0;
    pq.push({0, start});

    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if(inMST[u]) continue;
        inMST[u] = true;

        for(auto &edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            if(!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    // Output MST
    int mst_weight = 0;
    cout << "Edges in MST:\n";
    for(int i = 0; i < n; i++) {
        if(parent[i] != -1) {
            cout << parent[i] << " - " << i << " (Weight: " << key[i] << ")\n";
            mst_weight += key[i];
        }
    }
    cout << "Total MST Weight: " << mst_weight << endl;
}

int main() {
    int n = 6; // Number of vertices (0-indexed)
    vector<vector<pair<int,int>>> graph(n);

    // Example weighted graph (Adjacency List: node -> {neighbor, weight})
    graph[0] = {{1, 3}, {2, 1}, {3, 6}};
    graph[1] = {{0, 3}, {3, 5}};
    graph[2] = {{0, 1}, {3, 2}, {4, 4}};
    graph[3] = {{0, 6}, {1, 5}, {2, 2}, {4, 6}, {5, 2}};
    graph[4] = {{2, 4}, {3, 6}, {5, 3}};
    graph[5] = {{3, 2}, {4, 3}};

    int startNode = 0;
    prim(startNode, graph);

    return 0;
}
