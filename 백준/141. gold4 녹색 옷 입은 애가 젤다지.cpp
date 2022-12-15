#include <iostream>
#include <queue>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int map[125][125];
	int memo[125][125];
	int visited[125][125];

	int dx[] = { -1, 1, 0, 0 };
	int dy[] = { 0, 0, -1, 1 };

	int N;
	int problem = 1;
	while (true) {
		cin >> N;
		if (N == 0) break;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
				memo[i][j] = 9999;
				visited[i][j] = false;
			}
		}

		priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int,int>>>, greater<pair<int, pair<int, int>>> > que;
		que.push({ map[0][0], { 0, 0 } });

		while (!que.empty()) {
			pair<int, int> cur = que.top().second;
			int cost = que.top().first;
			que.pop();

			if (visited[cur.first][cur.second]) continue;
			visited[cur.first][cur.second] = true;

			for (int d = 0; d < 4; d++) {
				int nx = cur.first + dx[d];
				int ny = cur.second + dy[d];

				if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
				if (visited[nx][ny] || cost + map[nx][ny] >= memo[nx][ny]) continue;

				que.push({ cost + map[nx][ny], { nx, ny } });
				memo[nx][ny] = cost + map[nx][ny];
			}
		}
		
		cout << "Problem " << problem << ": " << memo[N - 1][N - 1] << "\n";
		problem += 1;
	}
}