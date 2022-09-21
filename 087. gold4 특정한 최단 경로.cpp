#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

vector<vector<pair<int, int>>> adj_list;
int N, v_1, v_2;

struct comp {
	bool operator()(pair<int, int>& a, pair<int, int>& b) {
		return a.second > b.second;
	}
};

vector<int> dijkstra(int start, int end = -1) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, comp> que;
	vector<int> dis(N + 1, INT_MAX);
	vector<bool> visited(N + 1);

	dis[start] = 0;
	que.push({ start, 0 });

	while (!que.empty()) {
		int cur = que.top().first;
		int cost = que.top().second;
		que.pop();

		if (visited[cur]) continue;
		visited[cur] = true;

		if (cur == end) return dis;

		for (auto adj : adj_list[cur]) {
			int next = adj.first;
			int next_cost = adj.second;

			if (!visited[next] && dis[next] > cost + next_cost) {
				dis[next] = cost + next_cost;
				que.push({ next, dis[next] });
			}
		}
	}

	return dis;
}

int main() {
	int E;
	cin >> N >> E;

	adj_list = vector<vector<pair<int, int>>>(N + 1);

	for (int i = 0; i < E; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		adj_list[a].push_back({ b, c });
		adj_list[b].push_back({ a, c });
	}

	cin >> v_1 >> v_2;

	int answer_1 = INT_MAX, answer_2 = INT_MAX;
	int v1_v2 = dijkstra(v_1, v_2)[v_2];
	vector<int> from1 = dijkstra(1);
	vector<int> toN = dijkstra(N);
	if (v1_v2 == INT_MAX) {
		cout << -1 << endl;
	}
	else {
		if (from1[v_1] != INT_MAX && toN[v_2] != INT_MAX)
			answer_1 = from1[v_1] + v1_v2 + toN[v_2];

		if (from1[v_2] != INT_MAX && toN[v_1] != INT_MAX)
			answer_2 = from1[v_2] + v1_v2 + toN[v_1];

		int answer = min(answer_1, answer_2);
		if (answer == INT_MAX) cout << -1 << endl;
		else cout << answer << endl;
	}
}