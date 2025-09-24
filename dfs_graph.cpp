#include <iostream>
#include <vector>
#include <stack>
#include <set>
using namespace std;

// Recursive DFS
void dfsRecursive(int node, vector<vector<int>> &graph, vector<bool> &visited) {
    visited[node] = true;
    cout << node << " "; // Output visited node

    for (int neighbor : graph[node]) {
        if (!visited[neighbor])
            dfsRecursive(neighbor, graph, visited);
    }
}

// Iterative DFS using stack
void dfsIterative(int start, vector<vector<int>> &graph) {
    vector<bool> visited(graph.size(), false);
    stack<int> s;
    s.push(start);

    while (!s.empty()) {
        int node = s.top();
        s.pop();

        if (!visited[node]) {
            visited[node] = true;
            cout << node << " "; // Output visited node

            // Push neighbors to stack
            for (auto it = graph[node].rbegin(); it != graph[node].rend(); ++it)
                if (!visited[*it])
                    s.push(*it);
        }
    }
}

int main() {
    int n = 7; // Number of vertices (1-indexed)
    vector<vector<int>> graph(n);

    // Example graph (Adjacency List)
    graph[1] = {2, 3};
    graph[2] = {4, 5};
    graph[3] = {6};
    graph[4] = {};
    graph[5] = {};
    graph[6] = {};

    int startNode = 1;

    cout << "DFS Recursive: ";
    vector<bool> visited(n, false);
    dfsRecursive(startNode, graph, visited);

    cout << "\nDFS Iterative: ";
    dfsIterative(startNode, graph);

    return 0;
}
