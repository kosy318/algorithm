#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

struct comp {
	bool operator()(pair<int, int>& p1, pair<int, int>& p2) {
		return p1.first < p2.first;
	}
};

int R, C;
string cave[100];
map<int, int> bottom; // key: y, value: x
priority_queue<pair<int, int>, vector<pair<int, int>>, comp> cluster;

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

bool find_cluster(vector<vector<bool>>& visited, int x, int y) {
	bool drop = true;
	bottom = map<int, int>();
	cluster = priority_queue<pair<int, int>, vector<pair<int, int>>, comp>();
	queue<pair<int, int>> que;
	que.push({ x, y });
	cluster.push({ x, y });
	visited[x][y] = true;

	while (!que.empty()) {
		int cur_x = que.front().first;
		int cur_y = que.front().second;
		que.pop();

		for (int d = 0; d < 4; d++) {
			int nx = cur_x + dx[d];
			int ny = cur_y + dy[d];

			if (nx < 0 || ny < 0 || ny >= C) continue;
			if (nx >= R) { // cluster°¡ ¹Ù´Ú¿¡ ´ê¾ÆÀÖÀ¸¸é ¶³¾îÁöÁö ¾Ê´Â cluster
				drop = false;
				continue;
			}
			if (visited[nx][ny]) continue;

			if (cave[nx][ny] == 'x') {
				que.push({ nx, ny });
				cluster.push({ nx, ny });
				visited[nx][ny] = true;
			}
			else if (d == 1) {
				if(bottom[cur_y] < cur_x)bottom[cur_y] = cur_x;
			}
		}
	}
	return drop;
}

int find_height(map<int, int> bottom) {
	int min_height = R;
	for (auto b : bottom) {
		int x = b.second;
		int y = b.first;

		int cnt = 1;
		while (x + cnt < R) {
			if (cave[x+cnt][y] == 'x') {
				min_height = min(min_height, cnt - 1);
			}
			else if (x + cnt == R - 1) {
				min_height = min(min_height, cnt);
			}
			cnt += 1;
		}
	}

	// min_height check
	//cout << min_height << endl;
	return min_height;
}

void drop_cluster() {
	int height = find_height(bottom);

	while (!cluster.empty()) {
		int x = cluster.top().first;
		int y = cluster.top().second;
		cluster.pop();

		cave[x][y] = '.';
		cave[x + height][y] = 'x';
	}
	// cluster drop Àß µÆ´ÂÁö Ã¼Å©
	/*for (int i = 0; i < R; i++)
		cout << cave[i] << endl;
	cout << endl;*/
}

void throw_bar(int lr, int h){ // lr==0: ¿ÞÂÊ, lr==1: ¿À¸¥ÂÊ, h: ´øÁø ³ôÀÌ
	if (lr == 0) {
		for (int j = 0; j < C; j++) {
			if (cave[h][j] == 'x') {
				cave[h][j] = '.'; // ¹Ì³×¶ö ÆÄ±«
				// ¹Ì³×¶ö Àß ÆÄ±«µÆ´ÂÁö Ã¼Å©
				/*for (int i=0; i<R; i++)
					cout << cave[i] << endl;
				cout << endl;*/

				vector<vector<bool>> visited(R, vector<bool>(C));
				for (int d = 0; d < 4; d++) {
					int nx = h + dx[d];
					int ny = j + dy[d];
					if (nx < 0 || ny < 0 || nx >= R || ny >= C) continue;
					if (visited[nx][ny] || cave[nx][ny] == '.') continue;

					if (find_cluster(visited, nx, ny)) {
						drop_cluster();
						break;
					}
				}
				break;
			}
		}
	}
	else {
		for (int j = C-1; j >= 0; j--) {
			if (cave[h][j] == 'x') {
				cave[h][j] = '.'; // ¹Ì³×¶ö ÆÄ±«
				// ¹Ì³×¶ö Àß ÆÄ±«µÆ´ÂÁö Ã¼Å©
				/*for (int i = 0; i < R; i++)
					cout << cave[i] << endl;
				cout << endl;*/


				vector<vector<bool>> visited(R, vector<bool>(C));
				for (int d = 0; d < 4; d++) {
					int nx = h + dx[d];
					int ny = j + dy[d];
					if (nx < 0 || ny < 0 || nx >= R || ny >= C) continue;
					if (visited[nx][ny] || cave[nx][ny] == '.') continue;

					if (find_cluster(visited, nx, ny)) {
						drop_cluster();
						break;
					}
				}
				break;
			}
		}
	}
}

int main() {
	cin >> R >> C;

	for (int i = 0; i < R; i++) {
		cin >> cave[i];
	}

	int N; // ´øÁø È½¼ö
	cin >> N;

	for (int i = 0; i < N; i++) {
		int height; // ´øÁø ³ôÀÌ
		cin >> height;

		throw_bar(i%2, R - height);
	}

	for (int i = 0; i < R; i++)
		cout << cave[i] << endl;
	cout << endl;
}