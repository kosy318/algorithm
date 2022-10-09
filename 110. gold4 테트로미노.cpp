#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N, M, max_num;
int answer = -1;
vector<vector<int>> map;
vector<vector<bool>> visited;

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

struct Point {
	int x, y;
	int cnt;
	Point(int x, int y, int cnt) :x{ x }, y{ y }, cnt{ cnt }{}
};

void dfs(int x, int y, int total, int cnt = 1) {
	if (answer >= total + max_num * (4 - cnt)) return;
	if (cnt == 4) {
		answer = max(answer, total);
		return;
	}
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx < 0 || ny < 0 || nx >= N || ny >= M || visited[nx][ny]) continue;
		visited[nx][ny] = true;

		dfs(nx, ny, total + map[nx][ny], cnt + 1);

		visited[nx][ny] = false;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	map = vector<vector<int>>(N, vector<int>(M));
	visited = vector<vector<bool>>(N, vector<bool>(M));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (max_num < map[i][j]) max_num = map[i][j];
		}
	}


	for(int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			visited[i][j] = true;
			dfs(i, j, map[i][j]);
			visited[i][j] = false;

			int cnt = 0;
			int min = 1001;
			int total = map[i][j];
			for (int d = 0; d < 4; d++) {
				int nx = i + dx[d];
				int ny = j + dy[d];
				if (nx < 0 || ny < 0 || nx >= N || ny >= M) continue;

				cnt += 1;
				if (min > map[nx][ny]) min = map[nx][ny];
				total += map[nx][ny];
			}

			if (cnt == 4 && answer < total-min) {
				answer = total - min;
			}
			else if (cnt == 3 && answer < total) {
				answer = total;
			}
		}
	}

	cout << answer;
}