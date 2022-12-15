#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int answer = INT_MAX;
int V, E;
vector<vector<int>> graph(401, vector<int>(401, INT_MAX));

void floyd_warshall() {
	for (int i = 1; i <= V; i++) {
		for (int j = 1; j <= V; j++) {
			if (i == j) continue;
			for (int k = 1; k <= V; k++) {
				if (graph[i][k] == INT_MAX || graph[k][j] == INT_MAX) continue;
				graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
			}
		}
	}
}

void cycle() {
	for (int i = 1; i <= V; i++) {
		for (int j = 1; j <= V; j++) {
			if (i == j) continue;
			if (graph[i][j] != INT_MAX && graph[j][i] != INT_MAX) 
				answer = min(answer, graph[i][j] + graph[j][i]);
		}
	}
}

int main() {
	cin >> V >> E;

	for (int i = 0; i < E; i++) {
		int from, to, dist;
		cin >> from >> to >> dist;
		graph[from][to] = dist;
	}

	floyd_warshall();
	cycle();

	if(answer != INT_MAX) cout << answer;
	else cout << "-1";
}