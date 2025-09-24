#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Step 1: DFS to fill stack with finishing times
void fillOrder(int node, vector<vector<int>> &graph, vector<bool> &visited, stack<int> &s) {
    visited[node] = true;
    for (int neighbor : graph[node])
        if (!visited[neighbor])
            fillOrder(neighbor, graph, visited, s);
    s.push(node);
}

// Step 2: DFS on transposed graph
void dfsTranspose(int node, vector<vector<int>> &transposeGraph, vector<bool> &visited, vector<int> &component) {
    visited[node] = true;
    component.push_back(node);
    for (int neighbor : transposeGraph[node])
        if (!visited[neighbor])
            dfsTranspose(neighbor, transposeGraph, visited, component);
}

// Kosaraju's Algorithm
void kosarajuSCC(vector<vector<int>> &graph, int n) {
    vector<bool> visited(n, false);
    stack<int> s;

    // Step 1: Fill stack according to finishing times
    for (int i = 0; i < n; i++)
        if (!visited[i])
            fillOrder(i, graph, visited, s);

    // Step 2: Transpose the graph
    vector<vector<int>> transposeGraph(n);
    for (int u = 0; u < n; u++) {
        for (int v : graph[u])
            transposeGraph[v].push_back(u);
    }

    // Step 3: DFS on transposed graph
    fill(visited.begin(), visited.end(), false);
    cout << "Strongly Connected Components:\n";
    while (!s.empty()) {
        int node = s.top(); s.pop();
        if (!visited[node]) {
            vector<int> component;
            dfsTranspose(node, transposeGraph, visited, component);
            for (int v : component)
                cout << v << " ";
            cout << endl;
        }
    }
}

int main() {
    int n = 5; // Number of vertices (0-indexed)
    vector<vector<int>> graph(n);

    // Example directed graph
    graph[0] = {2, 3};
    graph[1] = {0};
    graph[2] = {1};
    graph[3] = {4};
    graph[4] = {};

    kosarajuSCC(graph, n);

    return 0;
}
