#include <iostream>
#include <queue>
#include <climits>

using namespace std;

bool is_connected(int start, int end, int N, vector<vector<pair<int, int>>>& cities) {
	vector<bool> visited(N);
	queue<int> que;
	
	que.push(start);
	visited[start] = true;
	while (!que.empty()) {
		int cur = que.front();
		que.pop();

		for (auto city : cities[cur]) {
			if (city.first == end) return true;
			if (!visited[city.first]) {
				que.push(city.first);
				visited[city.first] = true;
			}
		}
	}

	return false;
}

vector<long long> bellman_ford(int start, int end, int N, vector<vector<pair<int, int>>>& cities, vector<int>& earn) {
	vector<long long> cost(N, INT_MAX);
	cost[start] = (-1) * earn[start]; // ó�� ��ġ �ʱ�ȭ

	// v-1 �� �ݺ�, �ѹ� �� �����鼭 ����Ŭ Ȯ��
	for (int i = 0; i < N; i++) {
		// city �ϳ��� ��
		for (int j = 0; j < N; j++) {
			// cities[j]�� ������ ���õ��� ���鼭 ����
			for (auto city : cities[j]) {
				int next = city.first;
				long long next_cost = city.second;

				// start->city > start->j->city�̸� ����
				if (cost[j] != INT_MAX && cost[next] > cost[j] + next_cost - earn[next]) {
					cost[next] = cost[j] + next_cost - earn[next];
					if (i == N - 1 && is_connected(city.first, end, N, cities)) { // ����Ŭ������ �� �������� ����� ����Ŭ�̶��
						cout << "Gee";
						return vector<long long>();
					}
				}
			}

			/*cout << endl;
			for (int i : cost) {
				cout << i*-1 << " ";
			}*/
		}
	}

	return cost;
}

int main() {
	int N, M; // N: ������ ��, M: ���� ������ ����
	int start, end; // ���۵���, ���� ����

	cin >> N >> start >> end >> M;

	vector<vector<pair<int, int>>> cities(N); // 0������ ����
	vector<int> earn(N);
	for (int i = 0; i < M; i++) {
		int start, end, cost;
		cin >> start >> end >> cost;

		cities[start].push_back({ end, cost });
	}
	for (int i = 0; i < N; i++) {
		cin >> earn[i];
	}

	vector<long long> cost = bellman_ford(start, end, N, cities, earn);
	if(cost.size() != 0){
		/*cout << endl;
		for (int i : cost) {
			cout << i * -1 << " ";
		}*/
		if (cost[end] == INT_MAX) cout << "gg";
		else cout << cost[end] * (-1);
	}
}