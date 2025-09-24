#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// BFS function
void bfs(int start, vector<vector<int>> &graph) {
	vector<bool> visited(graph.size(), false);
	queue<int> q;

	visited[start] = true;
	q.push(start);

	while (!q.empty()) {
		int node = q.front();
		q.pop();
		cout << node << " "; // Output visited node

		for (int neighbor : graph[node]) {
			if (!visited[neighbor]) {
				visited[neighbor] = true;
				q.push(neighbor);
			}
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

	cout << "BFS: ";
	bfs(startNode, graph);

	return 0;
}
