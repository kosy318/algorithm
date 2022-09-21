#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<bool> visited;
vector<vector<pair<int, int>>> tree;
int V, answer = -1;
int start_node;

void dfs(int cur, int total=0, int cnt=1) {
	bool end = true;

	for (auto vp : tree[cur]) {
		int node = vp.first;
		int dis = vp.second;

		if (visited[node]) continue;
		visited[node] = true;
		end = false;
		dfs(node, total + dis, cnt+1);
		visited[node] = false;
	}

	if (end && answer < total) {
		answer = total;
		start_node = cur;
	}
}

int main() {
	cin >> V;

	tree = vector<vector<pair<int, int>>>(V + 1);

	for (int i = 1; i <= V; i++) {
		int node, dis;
		int from;
		cin >> from;
		while (true) {
			cin >> node;
			if (node == -1) break;
			cin >> dis;

			tree[from].push_back({ node, dis });
		}
	}

	visited = vector<bool>(V + 1, false);
	visited[1] = true;
	dfs(1);
	visited[1] = false;

	visited[start_node] = true;
	answer = -1;
	dfs(start_node);

	cout << answer << endl;
}