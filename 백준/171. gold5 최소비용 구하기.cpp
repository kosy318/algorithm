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
			if (!visited[n.end] && cost[n.end] > cur_cost + n.cost) { // start -> cur -> n 이 지금 들어있는 값보다 작으면
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

	int N; // N개의 도시
	int M; // M개의 버스
	cin >> N >> M;

	// 간선의 개수가 적기 때문에 인접리스트 사용
	vector<vector<Node>> adj_list(N);
	for (int i = 0; i < M; i++) {
		int start, end, cost;
		cin >> start >> end >> cost;

		/// 주의::도시의 번호는 1번부터 N까지이므로 1씩 빼준다
		adj_list[start-1].push_back(Node(end-1, cost));
	}

	/// TODO::A번째 도시에서 B번째 도시까지 가는데 드는 최소 비용 -> 다익스트라
	int start, end;
	cin >> start >> end;
	cout << dijkstra(N, start-1, end-1, adj_list);
}