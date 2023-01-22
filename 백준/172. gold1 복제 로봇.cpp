#include<iostream>
#include<string>
#include<queue>
#include<climits>

using namespace std;

int N, key;
vector<string> maze;
vector<vector<int>> adj_matrix;
vector<pair<int, int>> nodes;

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };
int calc_distance(int start, int end) {
	int dis = 0;
	queue<pair<int, int>> que;
	vector<vector<bool>> visited(N, vector<bool>(N));
	que.push(nodes[start]);
	visited[nodes[start].first][nodes[start].second] = true;

	while (!que.empty()) {
		dis += 1;
		for (int i = 0, size = que.size(); i < size; i++) {
			int x = que.front().first;
			int y = que.front().second;
			que.pop();

			for (int d = 0; d < 4; d++) {
				int nx = x + dx[d];
				int ny = y + dy[d];

				if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
				if (maze[nx][ny] == '1' || visited[nx][ny]) continue;
				if (nx == nodes[end].first && ny == nodes[end].second) return dis;

				que.push({ nx, ny });
				visited[nx][ny] = true;
			}
		}
	}
	return 0;
}

bool find_edges() {
	for (int i = 0; i <= key; i++) { // nodes[i]와 나머지 nodes[j]와의 거리 구하기
		for (int j = 0; j <= key; j++) {
			if (i == j || adj_matrix[i][j] != 0) continue;
			int dis = calc_distance(i, j);
			if (dis == 0) return false;
			//cout << i << " -- " << j << " : " << dis << endl;
			adj_matrix[i][j] = dis;
			adj_matrix[j][i] = dis;
		}
	}
	return true;
}

struct Comp {
	bool operator()(pair<int, int> p1, pair<int, int> p2) {
		return p1.second > p2.second;
	}
};

int prim() {
	vector<int> min_edge(key+1, INT_MAX); // 각 정점 입장에서 신장트리에 포함된 정점과의 간선 비용중 최소 바용
	vector<bool> visited(key+1); // 신장트리에 포함여부

	// 시작점 처리
	min_edge[0] = 0; 
	int result = 0; // 최소 신장트리 비용 누적

	priority_queue<pair<int, int>, vector<pair<int, int>>, Comp> que;
	que.push({ 0, 0 });

	int cnt = 0;
	while (true) {
		int cur = que.top().first;
		int cost = que.top().second;
		que.pop();

		if (visited[cur]) continue;
		visited[cur] = true;
		result += cost;

		if (++cnt == key + 1) break; // key+1개의 정점을 다 추가했음

		for (int i = 0; i <= key; i++) {
			if (!visited[i] && min_edge[i] > adj_matrix[i][cur]) {
				min_edge[i] = adj_matrix[i][cur];
				que.push({ i, min_edge[i] });
			}
		}
	}

	return result;
}

int main() {
	cin >> N >> key;

	maze = vector<string>(N);
	adj_matrix = vector<vector<int>>(key + 1, vector<int>(key + 1));
	nodes = vector<pair<int, int>>(key + 1);
	int cnt = 1;
	for (int i = 0; i < N; i++) {
		cin >> maze[i];
		for (int j = 0; j < N; j++) {
			if (maze[i][j] == 'K') {
				nodes[cnt] = { i, j };
				cnt += 1;
			}
			else if (maze[i][j] == 'S') {
				nodes[0] = { i, j };
			}
		}
	}

	if (!find_edges()) {
		cout << "-1";
		return 0;
	}
	cout << prim();
}