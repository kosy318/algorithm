#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int topology_sort(vector<int>& times, vector<int>& in_degree, vector<vector<int>>& adj_list, int N, int target);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int tc;
	cin >> tc;
	for (int t = 0; t < tc; t++) {
		int N, K; // N: �ǹ� ����, K: ��Ģ ����
		cin >> N >> K;

		vector<int> times(N+1); // �� �ǹ��� ���� �� �ɸ��� �ð�
		for (int i = 1; i <= N; i++)
			cin >> times[i];

		// X �ǹ��� ���� ���� Y �ǹ��� ���� ���� �����ϴ�
		vector<int> in_degree(N + 1);
		vector<vector<int>> adj_list(N + 1);
		for (int i = 0; i < K; i++) {
			int X, Y;
			cin >> X >> Y;
			in_degree[Y] += 1;
			adj_list[X].push_back(Y);
		}

		// �Ǽ��ؾ��� �ǹ� ��ȣ
		int target;
		cin >> target;

		cout << topology_sort(times, in_degree, adj_list, N, target) << "\n";
	}
}

int topology_sort(vector<int>& times, vector<int>& in_degree, vector<vector<int>>& adj_list, int N, int target) {
	vector<int> sum_delay(N + 1); // �Ǽ��ϴµ� �ɸ��� �� �ð�
	queue<int> que;

	for (int i = 1; i <= N; i++) {
		if (in_degree[i] == 0) {
			que.push(i);
			sum_delay[i] = times[i];
			if (i == target) return times[i];
		}
	}

	while (!que.empty()) {
		int cur = que.front(); que.pop();

		for (int i : adj_list[cur]) {
			in_degree[i] -= 1;
			sum_delay[i] = max(sum_delay[i], sum_delay[cur]);

			if (in_degree[i] == 0) {
				sum_delay[i] += times[i];
				if (i == target) break;
				que.push(i);
			}
		}
	}

	return sum_delay[target];
}