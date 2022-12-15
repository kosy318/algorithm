#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
	int from;
	int to;
	int weight;
	Node(int from, int to, int weight) : from{ from }, to { to }, weight{ weight } {}
};

bool comp(Node* n1, Node* n2) {
	return n1->weight > n2->weight;
}

int find(vector<int>& parents, int a) {
	if (parents[a] == a) return a;
	return(parents[a] = find(parents, parents[a]));
}

bool node_union(vector<int>& parents, int a, int b) {
	int aRoot = find(parents, a);
	int bRoot = find(parents, b);
	if (aRoot == bRoot) return false;
	
	parents[bRoot] = aRoot;
	return true;
}


int main() {
	// 0 : 오르막길
	int N, M;
	cin >> N >> M;

	vector<Node*> adjList;

	for (int i = 0; i < M+1; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		adjList.push_back(new Node(a, b, c));
		adjList.push_back(new Node(b, a, c));
	}


	vector<int> parents(N+1);
	for (int i = 0; i <= N; i++) {
		parents[i] = i;
	}


	int cnt = 0;
	sort(adjList.begin(), adjList.end(), comp);
	int ascent_cnt = 0;
	for (Node* cur : adjList) {
		if (node_union(parents, cur->from, cur->to)) {
			cnt += 1;
			if (cur->weight == 0) {
				ascent_cnt += 1;
			}
			if (cnt == N) break;
		}
	}

	int min_answer = ascent_cnt * ascent_cnt;

	for (int i = 0; i <= N; i++) {
		parents[i] = i;
	}
	cnt = 0;
	ascent_cnt = 0;
	reverse(adjList.begin(), adjList.end());
	for (Node* cur : adjList) {
		if (node_union(parents, cur->from, cur->to)) {
			cnt += 1;
			if (cur->weight == 0) {
				ascent_cnt += 1;
			}
			if (cnt == N) break;
		}
	}

	int max_answer = ascent_cnt * ascent_cnt;

	cout << max_answer - min_answer << endl;
}