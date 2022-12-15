#include <iostream>
#include <queue>
#include <map>

using namespace std;

struct Point {
	int x, y;
	int fuel;

	Point(int x=0, int y=0, int fuel=0) : x{ x }, y{ y }, fuel{ fuel }{}
};

int x, y;
int N, P, fuel;
vector<vector<int>> board;
map<int, pair<int, int>> customers;

int dx[] = { -1, 0, 0, 1 };
int dy[] = { 0, -1, 1, 0 };

int to_dest(int num) {
	int dest_x = customers[num].first;
	int dest_y = customers[num].second;

	vector<vector<bool>> visited(N + 1, vector<bool>(N + 1));
	queue<Point> que;
	que.push(Point(x, y, fuel));

	while (!que.empty()) {
		Point cur = que.front();
		que.pop();

		if (cur.fuel < 0) return -1;
		if (cur.x == dest_x && cur.y == dest_y) {
			int diff = fuel - cur.fuel;
			fuel += diff;

			x = cur.x;
			y = cur.y;
			return fuel;
		}

		for (int d = 0; d < 4; d++) {
			int nx = cur.x + dx[d];
			int ny = cur.y + dy[d];

			if (nx <= 0 || ny <= 0 || nx > N || ny > N) continue;
			if (visited[nx][ny] || board[nx][ny] == -1) continue;

			que.push(Point(nx, ny, cur.fuel - 1));
			visited[nx][ny] = true;
		}
	}

	return -1;
}

int find_customer() {
	vector<vector<bool>> visited(N + 1, vector<bool>(N + 1));
	queue<Point> que;
	que.push(Point(x, y, fuel)); 
	visited[x][y] = true;

	while (!que.empty()) {
		Point customer = Point(21, 21);
		for (int i = 0, size = que.size(); i < size; i++) {
			Point cur = que.front();
			que.pop();

			if (board[cur.x][cur.y] > 0) {
				if ((cur.x < customer.x) || (cur.x == customer.x && cur.y < customer.y)) {
					customer = cur;
				}
			}

			for (int d = 0; d < 4; d++) {
				int nx = cur.x + dx[d];
				int ny = cur.y + dy[d];

				if (nx <= 0 || ny <= 0 || nx > N || ny > N) continue;
				if (visited[nx][ny] || board[nx][ny] == -1) continue;

				que.push(Point(nx, ny, cur.fuel - 1));
				visited[nx][ny] = true;
			}
		}
		if (customer.x != 21) {
			int num = board[customer.x][customer.y];
			x = customer.x;
			y = customer.y;
			fuel = customer.fuel;
			board[customer.x][customer.y] = 0;
			return num;
		}
	}

	return -1;
}

void go() {
	for(int i=0; i<P; i++){
		int num = find_customer();
		if (num == -1) {
			fuel = -1;
			return;
		}
		fuel = to_dest(num);
		if (fuel == -1) return;
	}
}

// 1, 1에서 시작
int main() {
	cin >> N >> P >> fuel;

	board = vector<vector<int>>(N + 1, vector<int>(N + 1));
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> board[i][j];
			if (board[i][j] == 1) board[i][j] = -1;
		}
	}

	cin >> x >> y;

	for (int p = 0; p < P; p++) {
		int i, j;
		cin >> i >> j;
		board[i][j] = p + 1;

		cin >> i >> j;
		customers[p + 1] = { i, j };
	}

	go();

	cout << fuel;
}