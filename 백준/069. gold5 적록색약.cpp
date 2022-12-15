#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct Point {
	int x, y;
	Point(int x, int y) : x{ x }, y{ y }{}
};

vector<int> dx = { -1, 1, 0, 0 };
vector<int> dy = { 0, 0, -1, 1 };

int main() {
	int N;
	cin >> N;
	vector<vector<char>> map(N, vector<char>(N));
	vector<vector<int>> visited(N, vector<int>(N));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i <= 1; i++) {
		int cnt = 0;
		int total = N * N;
		while (total != 0) {
			queue<Point*> que;
			for (int x = 0; x < N; x++) {
				for (int y = 0; y < N; y++) {
					if (visited[x][y] != i) continue;
					que.push(new Point(x, y));
					visited[x][y] = 1 - i;
					char color = map[x][y];
					if (i == 0 && color == 'R') map[x][y] = 'G';
					total -= 1;

					while (!que.empty()) {
						Point* cur = que.front();
						que.pop();
				
						for (int j = 0; j < 4; j++) {
							int nx = cur->x + dx[j];
							int ny = cur->y + dy[j];

							if (nx < 0 || ny < 0 || nx >= N || ny >= N || visited[nx][ny] != i) continue;
							if (map[nx][ny] == color) {
								que.push(new Point(nx, ny));
								visited[nx][ny] = 1 - i;
								if (i == 0 && map[nx][ny] == 'R') map[nx][ny] = 'G';
								total -= 1;
							}
						}
					}
					cnt += 1;
				}
			}

		}
		cout << cnt << " ";
	}
}
