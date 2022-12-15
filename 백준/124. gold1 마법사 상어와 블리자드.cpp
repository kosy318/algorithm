#include <iostream>
#include <vector>

using namespace std;

int N, K;
int x, y;
int score[4] = { 0, };
vector<vector<int>> board;
vector<pair<int, int>> route;

// 1 : 위, 2 : 아래, 3 : 왼쪽, 4 : 오른쪽
int dx[] = { 0, -1, 1, 0, 0 };
int dy[] = { 0, 0, 0, -1, 1 };

vector<int> marble;
vector<int> new_marble;

void organize() {
	marble.clear();
	for (auto r : route) {
		if (board[r.first][r.second] != 0) marble.push_back(board[r.first][r.second]);
		board[r.first][r.second] = 0;
	}

	for (int i = 0; i < marble.size(); i++) {
		board[route[i].first][route[i].second] = marble[i];
	}
}

void change_marble() {
	new_marble.clear();
	int num = 0;
	int cnt = 0;
	for (int i = 0; i < route.size(); i++) {
		int x = route[i].first;
		int y = route[i].second;

		if (board[x][y] != num) {
			if (cnt != 0) {
				new_marble.push_back(cnt);
				new_marble.push_back(num);
			}
			num = board[x][y];
			cnt = 1;
		}
		else if (board[x][y] == num) {
			cnt += 1;
		}
		if (board[x][y] == 0) {
			num = 0;
			break;
		}
	}
	if (num != 0) {
		new_marble.push_back(cnt);
		new_marble.push_back(num);
	}

	for (int i = 0; i < route.size(); i++) {
		int x = route[i].first;
		int y = route[i].second;
		board[x][y] = 0;

		if (i < new_marble.size()) {
			board[x][y] = new_marble[i];
		}
	}
}

void explode() {
	bool exploded = true;
	while (exploded) {
		exploded = false;

		int num = 0;
		int cnt = 0;
		for (int i = 0; i < route.size(); i++) {
			int x = route[i].first;
			int y = route[i].second;

			if (cnt >= 4 && board[x][y] != num) {
				score[num] += cnt;
				exploded = true;
				for (int j = i - cnt; j < i; j++)
					board[route[j].first][route[j].second] = 0;
			}
			if (i == route.size() - 1 && board[x][y] == num && cnt + 1 >= 4) {
				score[num] += cnt + 1;
				exploded = true;
				for (int j = i - cnt + 1; j < route.size(); j++)
					board[route[j].first][route[j].second] = 0;
			}

			if (board[x][y] != num) {
				num = board[x][y];
				cnt = 1;
			}
			else if (board[x][y] == num) {
				cnt += 1;
			}
			if (board[x][y] == 0) break;
		}
		organize();
	}
}

void blizzard(int dir, int s) {
	for (int i = 0; i < K; i++) {
		int nx = x + dx[dir];
		int ny = y + dy[dir];
		for (int j = 0; j < s; j++) {
			if (nx <= 0 || ny <= 0 || nx > N || ny > N) break;
			board[nx][ny] = 0;
			nx += dx[dir];
			ny += dy[dir];
		}
	}
	organize();
}

void get_order() {
	for (int i = 0; i < K; i++) {
		int dir, s;
		cin >> dir >> s;
		blizzard(dir, s);
		explode();
		change_marble();
	}
}

void set_route() {
	vector<vector<int>> visited(N + 1, vector<int>(N + 1));

	int ddx[] = { 0, 1, 0, -1 };
	int ddy[] = { -1, 0, 1, 0 };

	visited[x][y] = -1;
	int cur_x = x + ddx[0];
	int cur_y = y + ddy[0];

	int d = 0;
	int cnt = 1;
	while (cur_x > 0 && cur_y > 0 && cur_x <= N && cur_y <= N) {
		visited[cur_x][cur_y] = cnt;
		cnt += 1;
		route.push_back({ cur_x, cur_y });

		if (visited[cur_x + ddx[(d + 1) % 4]][cur_y + ddy[(d + 1) % 4]] == 0) d = (d + 1) % 4;
		cur_x += ddx[d];
		cur_y += ddy[d];
	}
}

// 1, 1부터 시작!!!!
// 연속된 숫자가 아니면 벽이 세워져 있다.
int main() {
	cin >> N >> K;
	x = (N + 1) / 2;
	y = (N + 1) / 2;

	board = vector<vector<int>>(N + 1, vector<int>(N + 1));
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> board[i][j];
		}
	}

	set_route();
	get_order();

	cout << score[1] + 2 * score[2] + 3 * score[3];
}