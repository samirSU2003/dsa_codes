#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Dijkstra's Algorithm
void dijkstra(int start, vector<vector<pair<int, int>>> &graph) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX); // Distance from start to each node
    dist[start] = 0;

    // Min-heap: pair(distance, node)
    priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int node = pq.top().second;
        int nodeDist = pq.top().first;
        pq.pop();

        // Skip if we already found a better path
        if (nodeDist > dist[node])
            continue;

        for (auto &edge : graph[node]) {
            int neighbor = edge.first;
            int weight = edge.second;

            if (dist[node] + weight < dist[neighbor]) {
                dist[neighbor] = dist[node] + weight;
                pq.push({dist[neighbor], neighbor});
            }
        }
    }

    // Output shortest distances
    cout << "Shortest distances from node " << start << ":\n";
    for (int i = 1; i < n; i++) {
        if (dist[i] == INT_MAX)
            cout << "Node " << i << ": INF\n";
        else
            cout << "Node " << i << ": " << dist[i] << "\n";
    }
}

int main() {
    int n = 6; // Number of vertices (1-indexed)
    vector<vector<pair<int,int>>> graph(n);

    // Example weighted graph (Adjacency List: node -> {neighbor, weight})
    graph[1] = {{2, 7}, {3, 9}, {6, 14}};
    graph[2] = {{1, 7}, {3, 10}, {4, 15}};
    graph[3] = {{1, 9}, {2, 10}, {4, 11}, {6, 2}};
    graph[4] = {{2, 15}, {3, 11}, {5, 6}};
    graph[5] = {{4, 6}, {6, 9}};
    graph[6] = {{1, 14}, {3, 2}, {5, 9}};

    int startNode = 1;
    dijkstra(startNode, graph);

    return 0;
}
