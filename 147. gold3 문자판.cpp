#include <iostream>
#include <string>
#include <vector>

using namespace std;

string map[100];
int N, M, K;
string target;

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

vector<vector<vector<int>>> cnt;

int find(int idx, int x, int y) { // idx번째 단어 찾기
	if (idx == target.length()) return 1;

	if (cnt[x][y][idx] != -1) return cnt[x][y][idx];
	else cnt[x][y][idx] = 0;

	for (int d = 0; d < 4; d++) {
		int nx = x;
		int ny = y;
		for (int n = 0; n < K; n++) {
			nx += dx[d];
			ny += dy[d];

			if (nx < 0 || ny < 0 || nx >= N || ny >= M || map[nx][ny] != target[idx]) continue;
			cnt[x][y][idx] += find(idx + 1, nx, ny);
		}
	}

	return cnt[x][y][idx];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		cin >> map[i];
	}

	cin >> target;
	cnt = vector<vector<vector<int>>>(N, vector<vector<int>>(M, vector<int>(target.length() + 1, -1)));

	int answer = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == target[0]) {
				answer += find(1, i, j);
			}
		}
	}

	cout << answer;
}