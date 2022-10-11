#include <iostream>
#include <vector>

using namespace std;

struct {
	int x, y;
	int dir;
} robot;

// 시계 반대방향으로 탐색
// (0 : 서, 1 : 남, 2 : 동, 3 : 북) 를 바라볼때 치워야할 곳의 위치 : dx, dy
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };
int N, M;

int clean_up(vector<vector<int>>& map) {
	vector<vector<bool>> visited(N, vector<bool>(M));
	int cnt = 0;

	while (true) {
		bool clean = false;
		if (!visited[robot.x][robot.y]) {
			visited[robot.x][robot.y] = true;
			cnt += 1;
		}

		for (int d = 0; d < 4; d++) {
			int ndir = (robot.dir + d) % 4;
			int nx = robot.x + dx[ndir];
			int ny = robot.y + dy[ndir];

			if (nx < 0 || ny < 0 || nx >= N || ny >= M || map[nx][ny] == 1) continue;
			else if (map[nx][ny] == 0 && !visited[nx][ny]) {
				robot.dir = (ndir + 1) % 4;
				robot.x = nx;
				robot.y = ny;
				clean = true;
				break;
			}
		}
		if (clean) continue;

		int ndir = (robot.dir + 1) % 4;
		int nx = robot.x + dx[ndir];
		int ny = robot.y + dy[ndir];
		if (nx < 0 || ny < 0 || nx >= N || ny >= M || map[nx][ny] == 1) break;
		else {
			robot.x = nx;
			robot.y = ny;
		}
	}

	return cnt;
}

int main() {
	cin >> N >> M;

	cin >> robot.x >> robot.y >> robot.dir;
	robot.dir = 3 - robot.dir;

	vector<vector<int>> map(N, vector<int>(M));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	cout << clean_up(map);
}