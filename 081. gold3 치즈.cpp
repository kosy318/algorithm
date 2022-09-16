#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M, cheese = 0;
vector<vector<bool>> board;

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

void melt(vector<vector<bool>> copied) {
	vector<vector<int>> visited(N, vector<int>(M));
	queue<pair<int, int>> que;

	que.push({ 0, 0 });
	visited[0][0] += 1;

	while (!que.empty()) {
		int x = que.front().first;
		int y = que.front().second;
		que.pop();

		for (int d = 0; d < 4; d++) {
			int nx = x + dx[d];
			int ny = y + dy[d];

			if (nx < 0 || ny < 0 || nx >= N || ny >= M) continue;
			if (board[nx][ny] == 0) {
				if (visited[nx][ny] > 0) continue;
				que.push({ nx, ny });
				visited[nx][ny] += 1;
			}
			else {
				visited[nx][ny] += 1;
				if (visited[nx][ny] == 2) {
					copied[nx][ny] = false;
					cheese -= 1;
				}
			}
		}
	}

	board = copied;
}

int main() {
	cin >> N >> M;
	board = vector<vector<bool>>(N, vector<bool>(M, false));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int inp;
			cin >> inp;
			if (inp == 1) {
				board[i][j] = true;
				cheese += 1;
			}
		}
	}

	int time = 0;
	while (cheese != 0) {
		melt(board);
		time += 1;
	}

	cout << time << "\n";
}