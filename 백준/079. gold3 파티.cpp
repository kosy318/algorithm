#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

struct comp {
	bool operator()(pair<int, int>& a, pair<int, int>& b) {
		return a.second > b.second;
	}
};

int num_student, num_roads, party;
vector<vector<pair<int, int>>> adj_list;

vector<int> dijkstra(int start = party) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, comp> que;
	vector<int> dis(num_student + 1, INT_MAX);
	vector<bool> visited(num_student + 1);

	dis[start] = 0;
	que.push({ start, 0 });

	while (!que.empty()) {
		int cur = que.top().first;
		int time = que.top().second;
		que.pop();
		if (visited[cur]) continue;
		visited[cur] = true;

		if (start != party && cur == party) return dis;

		for (auto adj : adj_list[cur]) {
			int next = adj.first;
			int next_time = adj.second;

			if (!visited[next] && dis[next] > time + next_time) {
				dis[next] = time + next_time;
				que.push({ next, dis[next] });
			}
		}
	}
	return dis;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> num_student >> num_roads >> party;

	adj_list = vector<vector<pair<int, int>>>(num_student + 1);
	for (int i = 0; i < num_roads; i++) {
		int from, to, time;
		cin >> from >> to >> time;
		adj_list[from].push_back({ to, time });
	}

	vector<int> dis = dijkstra();

	for (int i = 1; i <= num_student; i++) {
		dis[i] += dijkstra(i)[party];
	}

	dis[0] = -1;

	cout << *max_element(dis.begin(), dis.end()) << "\n";
}