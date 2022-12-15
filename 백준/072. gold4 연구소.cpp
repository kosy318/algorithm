#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;
int answer = 0;
vector<pair<int, int>> zeros;
int numbers[3];

void put(int cnt, int start, vector<vector<int>>& map);
void virus(vector<vector<int>> map);

int main() {
	cin >> N >> M;

	vector<vector<int>> map(N, vector<int>(M, 0));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 0) zeros.push_back({ i, j });
		}
	}

	put(0, 0, map);

	cout << answer << endl;
}

void put(int cnt, int start, vector<vector<int>>& map) {
	if (cnt == 3) {
		for (auto n : numbers) {
			int x = zeros[n].first;
			int y = zeros[n].second;

			map[x][y] = 1;
		}
		virus(map);
		for (auto n : numbers) {
			int x = zeros[n].first;
			int y = zeros[n].second;

			map[x][y] = 0;
		}
		return;
	}

	for (int i = start, size = zeros.size(); i < size; i++) {
		numbers[cnt] = i;
		put(cnt + 1, i + 1, map);
	}
}

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

void virus(vector<vector<int>> map) {
	int temp = 0;
	queue<pair<int, int>> que;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 2) {
				que.push({ i, j });
				while (!que.empty()) {
					int x = que.front().first;
					int y = que.front().second;
					que.pop();

					for (int d = 0; d < 4; d++) {
						int nx = x + dx[d];
						int ny = y + dy[d];
						if (nx < 0 || ny < 0 || nx >= N || ny >= M || map[nx][ny] == 1) continue;
						if (map[nx][ny] == 0) {
							que.push({ nx, ny });
							map[nx][ny] = 2;
							temp += 1;
						}
					}
				}
			}
		}
	}
	temp = zeros.size() - 3 - temp;
	answer = (answer > temp) ? answer : temp;
}