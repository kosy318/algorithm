#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;

struct Block {
	// input에 띄어쓰기가 없음을 주의!!!!!ㅠㅠ
	char ch;
	int x, y;
	vector<int> cnt;

	Block(int x = 0, int y = 0, vector<int> cnt = { INT_MAX, INT_MAX }) :
		x(x), y(y), cnt(cnt) {};
};

int N, M;
vector<vector<Block>> map;

void bfs();


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;

	map = vector<vector<Block>>(N, vector<Block>(M));

	string str;
	for (int i = 0; i < N; i++) {
		cin >> str;
		for(int j=0; j<M; j++)
			map[i][j].ch = str[j]; 
	}

	bfs();
	int answer = min(map[N - 1][M - 1].cnt[0], map[N - 1][M - 1].cnt[1]);
	if (answer == INT_MAX) cout << "-1";
	else cout << answer;
}


void bfs() {
	int dx[] = { -1, 1, 0, 0 };
	int dy[] = { 0, 0, -1, 1 };
	
	queue<pair<Block, bool>> que;
	map[0][0].cnt[false] = 1;
	que.push({ map[0][0], false });

	while (!que.empty()) {
		pair<Block, bool> cur = que.front();
		que.pop();
		int x = cur.first.x;
		int y = cur.first.y;
		bool broke = cur.second;

		for (int d = 0; d < 4; d++) {
			int nx = x + dx[d];
			int ny = y + dy[d];
			if (nx < 0 || ny < 0 || nx >= N || ny >= M || map[nx][ny].cnt[broke] != INT_MAX) continue;

			Block next = map[nx][ny];
			if (map[nx][ny].ch == '1' && broke) continue;

			next.x = nx;
			next.y = ny;

			if (map[nx][ny].ch == '0') {
				next.cnt[broke] = cur.first.cnt[broke] + 1;
				que.push({ next, broke });
			}
			else if (map[nx][ny].ch == '1') {
				next.cnt[true] = cur.first.cnt[broke] + 1;
				que.push({ next, true });
			}

			map[nx][ny] = next;
		}
	}	
}