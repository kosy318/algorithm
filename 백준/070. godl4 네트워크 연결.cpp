#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
	int to;
	int weight;
	Node(int to, int weight) : to{ to }, weight{ weight }{}

	bool operator<(const Node n) const {
		return this->weight > n.weight;
	}
};

int prim(vector<vector<Node>>& edge, int N);

int main() {
	int N, M;
	cin >> N >> M;

	vector<vector<Node>> edge(N+1);

	for (int i = 0; i < M; i++) {
		int a, b, c;
		cin >> a >> b >> c;

		edge[a].push_back(Node(b, c));
		edge[b].push_back(Node(a, c));
	}

	cout << prim(edge, N) << "\n";
}

int prim(vector<vector<Node>>& edge, int N) {
	priority_queue<Node> node_pq;
	vector<bool> visited(N+1);
	int answer = 0;

	Node cur(1, 0);

	node_pq.push(cur);

	while (!node_pq.empty()) {
		int to = node_pq.top().to;
		int weight = node_pq.top().weight;
		node_pq.pop();;

		if (visited[to]) continue;
		visited[to] = true;
		answer += weight;

		for (int i = 0, size = edge[to].size(); i < size; i++) {
			cur = edge[to][i];
			 
			if (visited[cur.to]) continue;
			node_pq.push(cur);
		}
	}

	return answer;
}