#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX_R = 1000000000;

struct Edge {
	int from, to;
	int relevance;

	Edge(int from, int to, int relevance) : from{ from }, to{ to }, relevance{ relevance }{}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N, Q;
	cin >> N >> Q;

	vector<vector<Edge>> adj_list(N+1);
	for (int i = 0; i < N - 1; i++) {
		int p, q, r;
		cin >> p >> q >> r;

		adj_list[p].push_back(Edge(p, q, r));
		adj_list[q].push_back(Edge(q, p, r));
	}

	while (Q--) {
		int k, v, answer = 0;
		cin >> k >> v;

		queue<pair<int, int>> que;
		vector<bool> visited(N + 1);

		visited[v] = true;
		que.push({ v, MAX_R });

		while (!que.empty()) {
			int cur = que.front().first;
			int rel = que.front().second;
			que.pop();

			for (Edge adj : adj_list[cur]) {
				if (visited[adj.to]) continue;
				visited[adj.to] = true;

				int next_rel = min(rel, adj.relevance);

				if (k <= next_rel) {
					answer += 1;
					que.push({ adj.to, next_rel });
				}
			}
		}

		cout << answer << "\n";
	}
}