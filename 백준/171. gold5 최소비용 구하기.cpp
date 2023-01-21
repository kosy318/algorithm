#include <iostream>
#include <queue>
#include <climits>

using namespace std;

struct Node {
	int end, cost;

	Node(int end, int cost) : end{ end }, cost{ cost }{}
};

struct comp {
	bool operator()(pair<int, int> p1, pair<int, int> p2) {
		return p1.second > p2.second;
	}
};

int dijkstra(int N, int start, int end, vector<vector<Node>>& adj_list) {
	priority_queue<pair<int, int>, vector<pair<int ,int>>, comp> que;
	vector<int> cost(N, INT_MAX);
	vector<bool> visited(N);
	
	cost[start] = 0;
	que.push({ start, cost[start] });

	while (!que.empty()) {
		int cur = que.top().first;
		int cur_cost = que.top().second;
		que.pop();

		if (visited[cur]) continue;
		visited[cur] = true;

		if (cur == end) break;

		for (Node n : adj_list[cur]) { // cur -> n
			if (!visited[n.end] && cost[n.end] > cur_cost + n.cost) { // start -> cur -> n �� ���� ����ִ� ������ ������
				cost[n.end] = cur_cost + n.cost;
				que.push({ n.end, cost[n.end] });
			}
		}
	}

	return cost[end];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N; // N���� ����
	int M; // M���� ����
	cin >> N >> M;

	// ������ ������ ���� ������ ��������Ʈ ���
	vector<vector<Node>> adj_list(N);
	for (int i = 0; i < M; i++) {
		int start, end, cost;
		cin >> start >> end >> cost;

		/// ����::������ ��ȣ�� 1������ N�����̹Ƿ� 1�� ���ش�
		adj_list[start-1].push_back(Node(end-1, cost));
	}

	/// TODO::A��° ���ÿ��� B��° ���ñ��� ���µ� ��� �ּ� ��� -> ���ͽ�Ʈ��
	int start, end;
	cin >> start >> end;
	cout << dijkstra(N, start-1, end-1, adj_list);
}