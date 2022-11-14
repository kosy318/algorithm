#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

vector<vector<char>> map;
vector<vector<int>> info;
int R, C;

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

queue<pair<int, int>> que;
priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>> > swan_que;
bool visited[1500][1500]; // melt_info()를 거치면 전부 true 상태가 된다. met에서 재사용 가능

int met() {
	visited[swan_que.top().second.first][swan_que.top().second.second] = false;

	while (!swan_que.empty()) {
		pair<int, int> cur = swan_que.top().second;
		int cost = swan_que.top().first;
		swan_que.pop();

		for (int d = 0; d < 4; d++) {
			int nx = cur.first + dx[d];
			int ny = cur.second + dy[d];

			if (nx < 0 || ny < 0 || nx >= R || ny >= C || !visited[nx][ny]) continue;
			if (map[nx][ny] == 'L') return cost;

			visited[nx][ny] = false;
			swan_que.push({max(cost, info[nx][ny]), { nx, ny } });
		}
	}

	return 0;
}

void melt_info() { // 몇초가 지나면 해당 구역의 얼음이 녹을 지 기록
	int depth = 0;
	while(true){
		queue<pair<int, int>> next_que;
		while (!que.empty()) {
			pair<int, int> cur = que.front(); que.pop();
			info[cur.first][cur.second] = depth;

			for (int d = 0; d < 4; d++) {
				int nx = cur.first + dx[d];
				int ny = cur.second + dy[d];

				if (nx < 0 || ny < 0 || nx >= R || ny >= C || visited[nx][ny]) continue;
				visited[nx][ny] = true;
				next_que.push({ nx, ny });
			}
		}
		depth += 1;
		if (next_que.empty()) break;
		que = queue<pair<int, int>>(next_que);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> R >> C;
	map = vector<vector<char>>(R, vector<char>(C));
	info = vector<vector<int>>(R, vector<int>(C, 2000));
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'L' && swan_que.empty()) {
				swan_que.push({ 0, { i, j } });
			}
			if (map[i][j] != 'X') {
				que.push({ i, j });
				visited[i][j] = true;
			}
		}
	}

	melt_info();
	cout << met();
}