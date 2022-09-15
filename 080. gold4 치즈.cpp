#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;
vector<vector<bool>> board;
int cheese;

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

void melt(vector<vector<bool>> copied) {
	vector<vector<bool>> visited(N, vector<bool>(M));
	queue<pair<int, int>> que;
	visited[0][0] = true;
	que.push({ 0, 0 });

	while (!que.empty()) {
		int x = que.front().first;
		int y = que.front().second;
		que.pop();

		for (int d = 0; d < 4; d++) {
			int nx = x + dx[d];
			int ny = y + dy[d];

			if (nx < 0 || ny < 0 || nx >= N || ny >= M || visited[nx][ny]) continue;
			visited[nx][ny] = true;
			if (board[nx][ny]) {
				copied[nx][ny] = false;
				cheese -= 1;
			}
			else 
				que.push({ nx, ny });
		}
	}
	board = copied;
}

int main() {
	cin >> N >> M;
	board = vector<vector<bool>>(N, vector<bool>(M));

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
	int cheese_before;
	while (cheese != 0) {
		cheese_before = cheese;
		melt(board);
		time += 1;
	}

	cout << time << "\n" << cheese_before;
}