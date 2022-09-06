#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;

int melt(vector<vector<int>>& map, vector<pair<int, int>>& icebergs);
bool is_split(vector<vector<int>>& map);

int main() {
	cin >> N >> M;
	vector<vector<int>> map(N, vector<int>(M, 0));
	vector<pair<int, int>> icebergs;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] != 0) icebergs.push_back({ i, j });
		}
	}

	cout << melt(map, icebergs) << endl;
}

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

int melt(vector<vector<int>>& map, vector<pair<int, int>>& icebergs) {
	int time = 0;
	vector<vector<int>> new_map(N, vector<int>(M, 0));
	while (true) {
		int cnt = 0;
		for (auto iceberg : icebergs) {
			int x = iceberg.first;
			int y = iceberg.second;
			if (map[x][y] == 0) continue;
			cnt += 1;
			new_map[x][y] = map[x][y];

			for (int d = 0; d < 4; d++) {
				int nx = x + dx[d];
				int ny = y + dy[d];
				if (nx < 0 || ny < 0 || nx >= N || ny >= M || new_map[x][y] == 0 || map[nx][ny] != 0) continue;
				new_map[x][y] -= 1;
				if (new_map[x][y] == 0) cnt -= 1;
			}
		}
		if (cnt == 0) return 0;

		time += 1;

		copy(new_map.begin(), new_map.end(), map.begin());
		if (is_split(map)) return time;
	}
}

bool is_split(vector<vector<int>>& map) {
	int cnt = 0;
	vector<vector<bool>> visited(N, vector<bool>(M, false));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] != 0 && !visited[i][j]) {
				visited[i][j] = true;
				cnt += 1;
				queue<pair<int, int>> que;
				que.push({ i, j });

				while (!que.empty()) {
					int x = que.front().first;
					int y = que.front().second;
					que.pop();

					for (int d = 0; d < 4; d++) {
						int nx = x + dx[d];
						int ny = y + dy[d];
						if (nx < 0 || ny < 0 || nx >= N || ny >= M || map[nx][ny] == 0 || visited[nx][ny]) continue;
						visited[nx][ny] = true;
						que.push({ nx, ny });
					}
				}
			}
		}
	}

	return cnt >= 2;
}