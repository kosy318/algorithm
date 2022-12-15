#include <iostream>
#include <queue>
#include <climits>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
	int x, y;
	int total;

	Node(int x = 0, int y = 0, int total = 0) : x{ x }, y{ y }, total{ total }{}
};

struct comp {
	bool operator()(Node& n1, Node& n2) {
		return n1.total > n2.total;
	}
};

int main() {
	int tc;
	cin >> tc;

	int dx[] = { -1, 1, 0, 0 };
	int dy[] = { 0, 0, -1, 1 };
	for (int t = 1; t <= tc; t++) {
		int N;
		cin >> N;
		vector<vector<int>> map(N, vector<int>(N));
		vector<vector<bool>> visited(N, vector<bool>(N));
		for (int i = 0; i < N; i++) {
			string str;
			cin >> str;
			for (int j = 0; j < N; j++) {
				map[i][j] = str[j] - '0';
			}
		}

		int ans = INT_MAX;
		priority_queue<Node, vector<Node>, comp> que;
		que.push(Node());

		while (!que.empty()) {
			Node cur = que.top(); que.pop();
			if (cur.x == N - 1 && cur.y == N - 1) {
				ans = min(ans, cur.total);
				continue;
			}

			for (int i = 0; i < 4; i++) {
				int nx = cur.x + dx[i];
				int ny = cur.y + dy[i];

				if (nx < 0 || ny < 0 || nx >= N || ny >= N || visited[nx][ny]) continue;
				visited[nx][ny] = true;
				que.push(Node(nx, ny, cur.total + map[nx][ny]));
			}
		}
		cout << "#" << t << " " << ans << endl;
	}
}
