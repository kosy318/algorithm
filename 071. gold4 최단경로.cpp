#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<string>
#include<map>
#include<climits>

using namespace std;

struct Node {
	int nb;
	int weight;
	Node(int nb, int weight) : nb{ nb }, weight{ weight }{}

	bool operator<(const Node n) const{
		return this->weight > n.weight;
	}
};

int main() {
	int V, E;
	cin >> V >> E;

	int start;
	cin >> start;

	vector<map<int, int>> edge(V+1);
	for (int i = 0; i < E; i++) {
		int from, to, weight;
		cin >> from >> to >> weight;
		if(edge[from][to] == 0) edge[from][to] = weight;
		else edge[from][to] = min(edge[from][to], weight);
	}

	vector<int> weights(V+1, INT_MAX);
	priority_queue<Node> que;
	que.push(Node(start, 0));
	weights[start] = 0;

	while (!que.empty()) {
		int cur_cost= que.top().weight;
		int cur_node = que.top().nb;
		que.pop();

		for (auto e : edge[cur_node]) {
			int next_node = e.first;
			int next_cost = e.second;
			if (weights[next_node] > cur_cost + next_cost) {
				weights[next_node] = cur_cost + next_cost;
				que.push(Node(next_node, weights[next_node]));
			}
		}
	}

	for (int i = 1; i <= V; i++) {
		if (weights[i] == INT_MAX) cout << "INF\n";
		else cout << weights[i] << "\n";
	}
	
}