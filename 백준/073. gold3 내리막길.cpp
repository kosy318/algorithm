#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> cnt;
int M, N;
vector<vector<int>> map;

int dfs(int x = 0, int y = 0);

int main() {
	cin >> M >> N;

	map = vector<vector<int>>(M, vector<int>(N));
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	cnt = vector<vector<int>>(M, vector<int>(N, -1));
	dfs();

	cout << cnt[0][0] << endl;
}

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

int dfs(int x, int y) {
	if (x == M-1 && y == N-1)
		return 1;

	if (cnt[x][y] != -1)
		return cnt[x][y];

	cnt[x][y] += 1;
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx < 0 || ny < 0 || nx >= M || ny >= N || map[x][y] <= map[nx][ny]) continue;
		cnt[x][y] += dfs(nx, ny);
	}

	return cnt[x][y];
}