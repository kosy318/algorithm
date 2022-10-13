#include <iostream>
#include <queue>
#include <string>

using namespace std;

int N, M, K;
vector<int> horizontal = { 4, 1, 3, 6 };
vector<int> vertical = { 2, 1, 5, 6 };
int x = 1, y = 1;
int answer = 0;
vector<vector<int>> map;

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

void calc_score() {
	vector<vector<bool>> visited(N+1, vector<bool>(M+1));
	queue<pair<int, int>> que;
	
	int num = map[x][y];
	visited[x][y] = true;
	que.push({ x, y });

	int cnt = 1;
	while (!que.empty()) {
		int i = que.front().first;
		int j = que.front().second;
		que.pop();

		for (int d = 0; d < 4; d++) {
			int nx = i + dx[d];
			int ny = j + dy[d];

			if (nx <= 0 || ny <= 0 || nx > N || ny > M || visited[nx][ny] || map[nx][ny] != num) continue;

			visited[nx][ny] = true;
			cnt += 1;
			que.push({ nx, ny });
		}
	}

	answer += num * cnt;
}

void move(vector<int>& vec1, vector<int>& vec2, int add) {
	vector<int> temp(4);
	for (int i = 0; i < 4; i++) {
		temp[(4 + i + add) % 4] = vec1[i];
	}
	vec1 = temp;

	vec2[1] = vec1[1]; // 상단
	vec2[3] = vec1[3]; // 하단

	calc_score();
}

// 0: 동, 1: 남, 2: 서, 3: 북
void select_direction() {
	int dir = 0;
	for (int k = 0; k < K; k++) {
		switch (dir) {
		case 0: // 동쪽
			if (y + 1 <= M) {
				y += 1;
				move(horizontal, vertical, 1);
			}
			else {
				dir = 2;
				k -= 1;
				continue;
			}
			break;
		case 1: // 남쪽
			if (x + 1 <= N) {
				x += 1;
				move(vertical, horizontal, 1);
			}
			else {
				dir = 3;
				k -= 1;
				continue;
			}
			break;
		case 2: // 서쪽
			if (y - 1 > 0) {
				y -= 1;
				move(horizontal, vertical, -1);
			}
			else {
				dir = 0;
				k -= 1;
				continue;
			}
			break;
		case 3: // 북쪽
			if (x - 1 > 0) {
				x -= 1;
				move(vertical, horizontal, -1);
			}
			else {
				dir = 1;
				k -= 1;
				continue;
			}
			break;
		default:
			break;
		}
	
		if (horizontal[3] > map[x][y]) {
			dir += 1;
			if (dir >= 4) dir = 0;
		}
		else if (horizontal[3] < map[x][y]) {
			dir -= 1;
			if (dir < 0) dir = 3;
		}
	}
}

int main(){
	cin >> N >> M >> K;

	map = vector<vector<int>>(N+1, vector<int>(M+1));
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> map[i][j];
		}
	}

	select_direction();

	 cout << answer;
}