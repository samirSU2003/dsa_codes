#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Union-Find (Disjoint Set Union)
class DSU {
    vector<int> parent, rank;
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for(int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if(parent[x] != x) parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }

    bool unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        if(px == py) return false; // Already connected

        // Union by rank
        if(rank[px] < rank[py]) parent[px] = py;
        else if(rank[px] > rank[py]) parent[py] = px;
        else {
            parent[py] = px;
            rank[px]++;
        }
        return true;
    }
};

// Kruskal's Algorithm
void kruskal(int n, vector<pair<int, pair<int,int>>> &edges) {
    // Sort edges by weight
    sort(edges.begin(), edges.end());

    DSU dsu(n);
    int mst_weight = 0;
    vector<pair<int,int>> mst_edges;

    for(auto &edge : edges) {
        int weight = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;

        if(dsu.unite(u, v)) { // If u and v are not connected
            mst_weight += weight;
            mst_edges.push_back({u, v});
        }
    }

    cout << "MST Weight: " << mst_weight << "\nEdges in MST:\n";
    for(auto &e : mst_edges) {
        cout << e.first << " - " << e.second << "\n";
    }
}

int main() {
    int n = 6; // Number of vertices (0-indexed or 1-indexed)
    vector<pair<int, pair<int,int>>> edges = {
        {3, {0, 1}},
        {1, {0, 2}},
        {6, {0, 3}},
        {5, {1, 3}},
        {2, {2, 3}},
        {4, {2, 4}},
        {7, {3, 4}}
    };

    kruskal(n, edges);

    return 0;
}
