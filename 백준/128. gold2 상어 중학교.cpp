#include <iostream>
#include <queue>

using namespace std;

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

vector<vector<int>> board;
int score = 0;
int N, M;
bool end_game = false;

void gravity() {
	for (int j = 0; j < N; j++) {
		int deleted = N - 1;
		int move = N - 1;
		while (true) {
			for (int i = deleted; i >= 0; i--) {
				if (board[i][j] == -100) {
					deleted = i;
					break;
				}
			}
			for (int i = deleted - 1; i >= 0; i--) {
				if (board[i][j] != -100) {
					move = i;
					break;
				}
			}
			if (deleted <= move || board[move][j] == -100 || board[deleted][j] != -100) break;
			if (board[move][j] == -1) {
				deleted = move - 1;
				if (deleted < 0) break;
				continue;
			}
			board[deleted][j] = board[move][j];
			board[move][j] = -100;
		}
	}
}

void turn() {
	vector<vector<int>> new_board(N, vector<int>(N));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			new_board[i][j] = board[j][N-1-i];
		}
	}

	board = new_board;
}

void organize() {
	gravity();
	turn();
	gravity();
}

pair<int, int> find_block() {
	pair<int, int> best;
	int blocks = 0;
	int rainbows = 0;
	queue<pair<int, int>> que;

	vector<vector<int>> visited(N, vector<int>(N));
	int num = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int cnt = 1;
			int rb = 0;
			pair<int, int> point = { i, j };
			if (board[i][j] > 0 && visited[i][j] == 0) {
				num += 1;
				int color = board[i][j];
				que.push({ i, j });
				visited[i][j] += 1;

				while (!que.empty()) {
					int x = que.front().first;
					int y = que.front().second;
					que.pop();

					for (int d = 0; d < 4; d++) {
						int nx = x + dx[d];
						int ny = y + dy[d];

						if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
						if ((board[nx][ny] > 0 && board[nx][ny] != color) || board[nx][ny] < 0) continue;
						if (board[nx][ny] > 0 && visited[nx][ny] > 0) continue;
						if (board[nx][ny] == 0 && visited[nx][ny] == num) continue;

						if(board[nx][ny] != 0 && (nx < x || (nx==point.first && ny < point.second))) point = {nx, ny};
						que.push({ nx, ny });
						if(board[nx][ny] > 0) visited[nx][ny] = 1;
						else {
							visited[nx][ny] = num;
							rb += 1;
						}
						cnt += 1;
					}
				}
			}

			if (cnt > blocks) {
				best = point;
				blocks = cnt;
				rainbows = rb;
			}
			else if (cnt == blocks) {
				if (rainbows < rb) {
					best = point;
					blocks = cnt;
					rainbows = rb;
				}
				else if (rainbows == rb && (best.first < point.first || (best.first == point.first && best.second < point.second))) {
					best = point;
					blocks = cnt;
					rainbows = rb;
				}
			}

		}
	}

	if (blocks < 2) end_game = true;
	return best;
}

int destroy_block(pair<int, int> point) {
	queue<pair<int, int>> que;
	int color = board[point.first][point.second];

	que.push(point);
	board[point.first][point.second] = -100;
	int blocks = 1;

	while (!que.empty()) {
		int x = que.front().first;
		int y = que.front().second;
		que.pop();

		for (int d = 0; d < 4; d++) {
			int nx = x + dx[d];
			int ny = y + dy[d];

			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
			if ((board[nx][ny] > 0 && board[nx][ny] != color) || board[nx][ny] < 0) continue;

			que.push({ nx, ny });
			board[nx][ny] = -100;
			blocks += 1;
		}
	}

	return blocks;
}

void start_game() {
	while (true) {
		pair<int, int> block = find_block();
		if (end_game) break;
		int num = destroy_block(block);
		score += num * num;
		organize();
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	board = vector<vector<int>>(N, vector<int>(N));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}

	start_game();
	cout << score;
}