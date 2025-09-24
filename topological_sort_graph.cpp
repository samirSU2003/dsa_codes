#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

// DFS-based Topological Sort
void topoDFSUtil(int node, vector<vector<int>> &graph, vector<bool> &visited, stack<int> &s) {
    visited[node] = true;
    for (int neighbor : graph[node]) {
        if (!visited[neighbor])
            topoDFSUtil(neighbor, graph, visited, s);
    }
    s.push(node); // Add node after visiting all neighbors
}

void topoDFS(vector<vector<int>> &graph, int n) {
    vector<bool> visited(n, false);
    stack<int> s;

    for (int i = 0; i < n; i++) {
        if (!visited[i])
            topoDFSUtil(i, graph, visited, s);
    }

    cout << "Topological Sort (DFS): ";
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
}

// Kahn's Algorithm (BFS-based Topological Sort)
void topoKahn(vector<vector<int>> &graph, int n) {
    vector<int> indegree(n, 0);
    for (int u = 0; u < n; u++) {
        for (int v : graph[u])
            indegree[v]++;
    }

    queue<int> q;
    for (int i = 0; i < n; i++)
        if (indegree[i] == 0)
            q.push(i);

    cout << "Topological Sort (Kahn's): ";
    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << u << " ";
        for (int v : graph[u]) {
            indegree[v]--;
            if (indegree[v] == 0)
                q.push(v);
        }
    }
    cout << endl;
}

int main() {
    int n = 6; // Number of vertices (0-indexed)
    vector<vector<int>> graph(n);

    // Example DAG (Adjacency List)
    graph[5] = {2, 0};
    graph[4] = {0, 1};
    graph[2] = {3};
    graph[3] = {1};
    // graph[0], graph[1] remain empty

    topoDFS(graph, n);
    topoKahn(graph, n);

    return 0;
}
