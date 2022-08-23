#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

struct Node {
	int idx;
	int dis;

	Node(int idx, int sad) : idx{ idx }, dis{ sad }{}
};

int main() {
	int N, K; // N : ป๙ลอ, K : มý
	cin >> N >> K;

	map<int, bool> visited;

	queue<Node*> que;
	for (int i = 0; i < N; i++) {
		int idx;
		cin >> idx;
		que.push(new Node(idx, 0));
		visited[idx] = true;
	}

	int cnt = 0;
	long long answer = 0;
	while (cnt < K) {
		Node* node = que.front();
		que.pop();
		if (node->dis != 0) {
			answer += node->dis;
			cnt += 1;
		}
		if (!visited[node->idx - 1]) {
			que.push(new Node(node->idx - 1, node->dis + 1));
			visited[node->idx - 1] = true;
		}
		if (!visited[node->idx + 1]) {
			que.push(new Node(node->idx + 1, node->dis + 1));
			visited[node->idx + 1] = true;
		}
	}
	
	cout << answer << endl;
}