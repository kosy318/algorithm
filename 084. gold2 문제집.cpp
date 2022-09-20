#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;
vector<vector<int>> adj_list;
vector<int> in_degree;

void topology_sort() {
	vector<bool> visited(N + 1);
	priority_queue<int, vector<int>, greater<int>> prob_nb;
	for (int i = 1; i <= N; i++) {
		if (!visited[i] && in_degree[i] == 0) {
			prob_nb.push(i);
			visited[i] = true;
		}
	}

	while (!prob_nb.empty()) {
		int nb = prob_nb.top();
		prob_nb.pop();

		cout << nb << " ";
		for (int i : adj_list[nb]) {
			if (visited[i]) continue;
			in_degree[i] -= 1;

			if (in_degree[i] == 0) {
				prob_nb.push(i);
				visited[i] = true;
			}
		}
	}
}

int main() {
	cin >> N >> M;
	adj_list = vector<vector<int>>(N + 1);
	in_degree = vector<int>(N + 1);

	int A, B;
	for (int i = 0; i < M; i++) {
		cin >> A >> B; // A -> B
		adj_list[A].push_back(B);
		in_degree[B]++;
	}

	topology_sort();
}