#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
};

void bellmanFord(int V, int E, int src, vector<Edge> &edges) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    // Relax edges V-1 times
    for (int i = 1; i <= V-1; i++) {
        for (auto edge : edges) {
            int u = edge.u;
            int v = edge.v;
            int w = edge.w;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    // Check for negative weight cycles
    for (auto edge : edges) {
        int u = edge.u;
        int v = edge.v;
        int w = edge.w;
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            cout << "Graph contains a negative weight cycle\n";
            return;
        }
    }

    // Print distances
    cout << "Vertex Distance from Source:\n";
    for (int i = 0; i < V; i++) {
        cout << i << " \t " << dist[i] << "\n";
    }
}

int main() {
    int V = 5; // Number of vertices
    int E = 8; // Number of edges
    vector<Edge> edges = {
        {0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2},
        {1, 4, 2}, {3, 2, 5}, {3, 1, 1}, {4, 3, -3}
    };

    bellmanFord(V, E, 0, edges);

    return 0;
}
