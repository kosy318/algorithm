#include <iostream>
#include <vector>

using namespace std;

int N, M, T;
vector<vector<int>> board;
vector<pair<int, int>> dust;
vector<pair<int, int>> air_cleaner;

// ¹Ý½Ã°è
int dx[] = { 0, -1, 0, 1 };
int dy[] = { 1, 0, -1, 0 };

void air_cleaning() {
	vector<vector<int>> new_board(board);
	int add = 1;
	for (auto c : air_cleaner) {
		int x = c.first;
		int y = c.second;

		int d = 0;
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[d];
			int ny = y + dy[d];

			while (!(nx < 0 || ny < 0 || nx >= N || ny >= M)) {
				if (i == 3 && board[nx][ny] == -1) break;
				if (new_board[nx][ny] != -1) {
					// cout << x << ", " << y << " to " << nx << ", " << ny << endl;
					if (board[x][y] == -1) new_board[nx][ny] = 0;
					else new_board[nx][ny] = board[x][y];
				}

				x = nx;
				y = ny;

				nx += dx[d];
				ny += dy[d];
			}
			d += add;
			if (d < 0) d = 3;
			else if (d == 4) d = 0;
		}
		add = -1;
	}

	board = vector<vector<int>>(new_board);
}

void diffusing() {
	vector<vector<int>> move(N, vector<int>(M));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j] > 0) {
				int num = board[i][j] / 5;
				int cnt = 0;
				for (int d = 0; d < 4; d++) {
					int nx = i + dx[d];
					int ny = j + dy[d];

					if (nx < 0 || ny < 0 || nx >= N || ny >= M) continue;
					if (board[nx][ny] == -1) continue;

					move[nx][ny] += num;
					cnt += 1;
				}
				move[i][j] -= num * cnt;
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			board[i][j] += move[i][j];
		}
	}
}

void start() {
	for (int i = 0; i < T; i++) {
		diffusing();
		air_cleaning();
	}
}

int main() {
	cin >> N >> M >> T;

	board = vector<vector<int>>(N, vector<int>(M));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
			if (board[i][j] == -1) air_cleaner.push_back({ i, j });
		}
	}

	start();

	int total = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j] > 0) total += board[i][j];
		}
	}

	cout << total;
}