#include <iostream>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

struct Point {
	int x, y;
	int cnt;
	int keys;
	Point(int x = 0, int y = 0, int cnt = 0, int keys = 1 << 6) :x{ x }, y{ y }, cnt{ cnt }, keys{ keys }{}
};

int N, M;
int answer;
Point start = Point();

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };
vector<string> map;

void move() {
	vector<vector<vector<bool>>> visited(N, vector<vector<bool>>(M, vector<bool>(1<<7)));
	queue<Point> que;
	que.push(start);

	while (!que.empty()) {
		Point cur = que.front(); que.pop();

		for (int d = 0; d < 4; d++) {
			int nx = cur.x + dx[d];
			int ny = cur.y + dy[d];

			if (nx < 0 || ny < 0 || nx >= N || ny >= M) {
				//cout << endl << nx << ", " << ny << " outofbound\n";
				continue;
			}
			// 벽이거나 열쇠가 없는 문이면
			if (map[nx][ny] == '#' || (map[nx][ny] >= 'A' && map[nx][ny] <= 'F' && ((cur.keys & 1<<map[nx][ny] - 'A') == 0))) {
				//cout << endl << nx << ", " << ny << " 벽이거나 열쇠없는 문\n";
				continue;
			}
			else if (map[nx][ny] == '1') {
				//cout << endl << nx << ", " << ny << endl;
				answer = cur.cnt + 1;
				return;
			}


			Point next = Point(nx, ny, cur.cnt + 1, cur.keys);

			if (map[nx][ny] >= 'a' && map[nx][ny] <= 'f') { // 열쇠면
				next.keys |= 1 << (map[nx][ny] - 'a'); // 줍줍
			}
			
			if (visited[nx][ny][next.keys]) continue;
			visited[nx][ny][next.keys] = true;
			que.push(next);
		}
	}

	answer = -1;
}

int main() {
	cin >> N >> M;
	answer = N * M;

	for (int i = 0; i < N; i++) {
		string str;
		cin >> str;
		map.push_back(str);
		for (int j = 0; j < M; j++) {
			if (map[i][j] == '0') {
				start = Point(i, j);
				map[i][j] = '.';
			}
		}
	}

	move();

	cout << answer << endl;
}