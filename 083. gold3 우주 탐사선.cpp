#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int N, start, answer = INT_MAX;
vector<vector<int>> planets;
vector<vector<int>> dis;

vector<bool> visited;

void floyd_warshall() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j) continue;
			for (int k = 0; k < N; k++) {
				if (i == k || j == k) continue;
				dis[i][j] = min(dis[i][j], planets[i][k] + planets[k][j]);
			}
		}
	}
}

void dfs(int cur, int distance, int cnt) {
	if (N == cnt) {
		answer = min(answer, distance);
		return;
	}

	for (int i = 0; i < N; i++) {
		if (visited[i] || distance + dis[cur][i] > answer) continue;
		visited[i] = true;
		dfs(i, distance + dis[cur][i], cnt + 1);
		visited[i] = false;
	}
}

int main() {
	cin >> N >> start;

	planets = vector<vector<int>>(N, vector<int>(N));
	dis = vector<vector<int>>(N, vector<int>(N, 2001));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> planets[i][j];
			if (planets[i][j] != 0) dis[i][j] = planets[i][j];
		}
	}

	floyd_warshall();

	visited = vector<bool>(N);
	visited[start] = true;
	dfs(start, 0, 1);

	cout << answer << endl;
}