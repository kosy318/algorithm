#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>

using namespace std;

int main() {
	int N; // 도시의 개수
	int M; // 버스의 개수
	cin >> N >> M;

	vector<vector<int>> cost(N+1, vector<int>(N+1, 0));

	for (int i = 0; i < M; i++) {
		// cost <= 100,000... long long?
		int from, to, c;
		cin >> from >> to >> c;

		if(cost[from][to] == 0 || cost[from][to] > c) cost[from][to] = c;
	}

	vector<vector<int>> dist(N+1, vector<int>(N+1));
	vector<vector<vector<int>>> nodes(N + 1, vector<vector<int>>(N + 1));
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (i == j) dist[i][j] = 0;
			else if (cost[i][j] != 0) {
				dist[i][j] = cost[i][j];
				nodes[i][j].insert(nodes[i][j].begin(), { i, j });
			}
			else dist[i][j] = INT_MAX;
		}
	}

	// folyd-warshall
	for (int k = 1; k <= N; k++) { // 중간 노드
		for (int i = 1; i <= N; i++) { // 시작 노드
			for (int j = 1; j <= N; j++) { // 도착 노드
				if (dist[i][k] == INT_MAX || dist[k][j] == INT_MAX) continue;
				else if (dist[i][j] == INT_MAX || dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					nodes[i][j] = nodes[i][k];
					nodes[i][j].insert(nodes[i][j].end(), nodes[k][j].begin() + 1, nodes[k][j].end());
				}
			}
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (dist[i][j] == INT_MAX) cout << "0 ";
			else cout << dist[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << nodes[i][j].size() << " ";
			for (auto node : nodes[i][j]) {
				cout << node << " ";
			}
			cout << endl;
		}
	}
}