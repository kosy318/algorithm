#include <iostream>
#include <queue>
#include <map>
#include <set>

using namespace std;

struct Heater{
	int x, y;
	int dir;
	int cnt;

	Heater(int x, int y, int dir, int cnt = 0) : x{ x }, y{ y }, dir{ dir }, cnt{ cnt }{}
};

int N, M, K;
vector<pair<int, int>> target;
vector<Heater> heater;
vector<vector<int>> temperature;
map<pair<int, int>, set<pair<int, int>>> wall;

// 오른쪽, 왼쪽, 위, 아래
int dx[] = { 0, 0, 0, -1, 1 };
int dy[] = { 0, 1, -1, 0, 0 };
// 1, 2는 위-직진 아래-직진 직진 방향으로 퍼짐
// 3, 4는 왼-직진 오-직진 직진 방향으로 퍼짐
vector<vector<int>> bx = { {0}, {-1, 1}, {-1, 1}, {0, 0}, {0, 0} };
vector<vector<int>> by = { {0},{0, 0}, {0, 0}, {-1, 1}, {-1, 1} };

bool check() {
	for (auto t : target) {
		int x = t.first;
		int y = t.second;

		if (temperature[x][y] < K) return false;
	}

	return true;
}

void cooling() {
	vector<vector<int>> move(N+1, vector<int>(M+1));
	for (int x = 1; x <= N; x++) {
		for (int y = 1; y <= M; y++) {
			int total = 0;
			for (int d = 1; d <= 4; d++) {
				int nx = x + dx[d];
				int ny = y + dy[d];
				if (nx <= 0 || ny <= 0 || nx > N || ny > M) continue;
				if ((wall.find({ x, y }) == wall.end() || wall[{x, y}].find({ nx, ny }) == wall[{x, y}].end())) {
					if (temperature[x][y] > temperature[nx][ny]) {
						move[nx][ny] += (temperature[x][y] - temperature[nx][ny])/4;
						total += (temperature[x][y] - temperature[nx][ny]) / 4;
					}
				}
			}
			move[x][y] -= total;
		}
	}

	for (int x = 1; x <= N; x++) {
		for (int y = 1; y <= M; y++) {
			temperature[x][y] += move[x][y];
			if ((temperature[x][y] > 0 ) && (x == 1 || y == 1 || x == N || y == M)) temperature[x][y] -= 1;
		}
	}
}

void warming() {
	for (Heater h : heater) {
		vector<vector<bool>> visited(N+1, vector<bool>(M+1));
		int dir = h.dir;
		queue<Heater> que;

		int x = h.x;
		int y = h.y;
		int nx = h.x + dx[dir];
		int ny = h.y + dy[dir];
		if (nx <= 0 || ny <= 0 || nx > N || ny > M) continue;
		
		if ((wall.find({ x, y }) == wall.end() || wall[{x, y}].find({ nx, ny }) == wall[{x, y}].end()) && !visited[nx][ny]) {
			temperature[nx][ny] += h.cnt;

			visited[nx][ny] = true;
			if (h.cnt - 1 != 0) {
				que.push(Heater(nx, ny, dir, h.cnt - 1));
			}
		}

		while (!que.empty()) {
			int x = que.front().x;
			int y = que.front().y;
			int cnt = que.front().cnt;
			que.pop();

			int nx = x + dx[dir];
			int ny = y + dy[dir];
			if (!(nx <= 0 || ny <= 0 || nx > N || ny > M)) {
				// 사이에 벽이 있음
				if ((wall.find({ x, y }) == wall.end() || wall[{x, y}].find({ nx, ny }) == wall[{x, y}].end()) && !visited[nx][ny]) {
					temperature[nx][ny] += cnt;

					visited[nx][ny] = true;
					if (cnt - 1 != 0) {
						que.push(Heater(nx, ny, dir, cnt - 1));
					}
				}
			}

			for (int d = 0; d < 2; d++) {
				int temp_x = x + bx[dir][d];
				int temp_y = y + by[dir][d];

				nx = temp_x + dx[dir];
				ny = temp_y + dy[dir];
				if (!(nx <= 0 || ny <= 0 || nx > N || ny > M)) {
					
					if ((wall.find({ temp_x, temp_y }) == wall.end() || wall[{temp_x, temp_y}].find({ x, y }) == wall[{temp_x, temp_y}].end())
						&& (wall.find({ temp_x, temp_y }) == wall.end() || wall[{temp_x, temp_y}].find({ nx, ny }) == wall[{temp_x, temp_y}].end()) && !visited[nx][ny]) {
						temperature[nx][ny] += cnt;

						visited[nx][ny] = true;
						if (cnt - 1 != 0) {
							que.push(Heater(nx, ny, dir, cnt - 1));
						}
					}
				}
			}
		}
	}
}

int start() {
	int cnt = 0;
	while (true) {
		warming();
		cooling();
		cnt += 1;
		if (cnt > 100) break;
		if (check()) break;
	}

	return cnt;
}

int main() {
	cin >> N >> M >> K;

	temperature = vector<vector<int>>(N+1, vector<int>(M+1));
	int num;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> num;
			// 온도를 조사해야하는 칸
			if (num == 5) target.push_back({ i, j });
			else if (num != 0) heater.push_back(Heater(i, j, num, 5));
		}
	}

	int W;
	cin >> W;
	// 0이면 위, 1이면 오른쪽에 벽이 있다는 의미
	int wx[] = { -1, 0 };
	int wy[] = { 0, 1 };
	for (int i = 0; i < W; i++) {
		int x, y, dir;
		cin >> x >> y >> dir;

		int nx = x + wx[dir];
		int ny = y + wy[dir];

		wall[{x, y}].insert({ nx, ny });
		wall[{nx, ny}].insert({ x, y });
	}

	int result = start();
	if (result > 100) cout << "101";
	else cout << result;
}