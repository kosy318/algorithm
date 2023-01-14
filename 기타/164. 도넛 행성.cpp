#include <iostream>
#include <queue>

using namespace std;

int N, M; // 행, 열
vector<vector<int>> planet; // 행성 모양

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

int adventure() {
	int res = 0;

	queue<pair<int, int>> que; // 좌표 값을 들고있는 queue

	// 비어있는 위치 찾기
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (planet[i][j] == 0) {
				res += 1;
				que.push({ i, j });
				planet[i][j] = 2; // visited 대신 planet에 2로 표시해서 처리

				// bfs 시작
				while (!que.empty()) {
					pair<int, int> cur = que.front(); que.pop();

					for (int d = 0; d < 4; d++) { // 4방탐색
						int nx = cur.first + dx[d];
						int ny = cur.second + dy[d];

						if (nx < 0) {
							nx = N - 1;
						}
						if (ny < 0) {
							ny = M - 1;
						}
						if (nx >= N) {
							nx = 0;
						}
						if (ny >= M) {
							ny = 0;
						}

						if (planet[nx][ny] != 0) continue; // 이미 방문했거나 비어있지 않은 곳이면 지나감

						que.push({ nx, ny });
						planet[nx][ny] = 2; // visited 대신 planet에 2로 표시해서 처리
					}
				}

				// check
				/*cout << endl;
				for (auto vv : planet) {
					for (auto v : vv)
						cout << v << " ";
					cout << endl;
				}*/
			}
		}
	}

	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	planet = vector<vector<int>>(N, vector<int>(M)); // 행성 크기 초기화

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> planet[i][j];
		}
	}

	cout << adventure();
}