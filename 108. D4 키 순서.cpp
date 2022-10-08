#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

int N, M, total;
bool visited[501];

void dfs(vector<vector<int>>& adj, int cur) {
	visited[cur] = true;

	for (int i : adj[cur]) {
		if (visited[i]) continue;

		total += 1;
		dfs(adj, i);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int tc;
	cin >> tc;
	for (int t = 1; t <= tc; t++) {
		cin >> N >> M;

		vector<vector<int>> adj(N + 1);
		vector<vector<int>> adj_rev(N + 1);
		for (int i = 0; i < M; i++) {
			int a, b;
			cin >> a >> b;
			adj[a].push_back(b);
			adj_rev[b].push_back(a);
		}

		int answer = 0;
		for (int cur = 1; cur <= N; cur++) {
			total = 0;
			memset(visited, false, N + 1);
			dfs(adj, cur);
			memset(visited, false, N + 1);
			dfs(adj_rev, cur);
			if (total + 1 == N) answer += 1;
		}

		cout << "#" << t << " " << answer << "\n";
	}
}