#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void topology_sort(int N, vector<vector<int>>& adj_list, vector<int>& in_degree);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N, M;
	cin >> N >> M;

	vector<vector<int>> adj_list(N + 1);
	vector<int> in_degree(N + 1);

	for (int i = 0; i < M; i++) {
		int A, B;
		cin >> A >> B;

		in_degree[B]++;
		adj_list[A].push_back(B);
	}

	topology_sort(N, adj_list, in_degree);
}

void topology_sort(int N, vector<vector<int>>& adj_list, vector<int>& in_degree){
	queue<int> que;

	for (int i = 1; i <= N; i++) {
		if (in_degree[i] == 0) {
			que.push(i);
		}
	}

	while (!que.empty()) {
		int cur = que.front(); que.pop();
		cout << cur << " ";

		for (auto n : adj_list[cur]) {
			in_degree[n] -= 1;
			if (in_degree[n] == 0) que.push(n);
		}
	}
}