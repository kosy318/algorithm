#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
	int x, y;
	int time;
	bool sword;
	Node(int x, int y, int time = 0, bool sword = false) : x{ x }, y{ y }, time{ time }, sword{sword}{}
};

vector<int> dx = { -1, 1, 0, 0 };
vector<int> dy = { 0, 0, -1, 1 };

int main() {
	int N, M, T;
	cin >> N >> M >> T;

	vector<vector<int>> map(N, vector<int>(M));
	vector<vector<bool>> visited(N, vector<bool>(M));
	vector<vector<bool>> visit_with_sword(N, vector<bool>(M));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	queue<Node*> que;
	Node* cur = new Node(0, 0);
	visited[0][0] = true;
	visit_with_sword[0][0] = true;
	que.push(cur);
	bool end = false;
	while (!que.empty()) {
		cur = que.front();
		que.pop();

		for (int i = 0; i < 4; i++) {
			int nx = cur->x + dx[i];
			int ny = cur->y + dy[i];

			if (nx == N-1 && ny == M-1) {
				end = true;
				break;
			}
			
			if (nx < 0 || ny < 0 || nx >= N || ny >= M ) continue;
			
			if ((map[nx][ny] == 2 || cur->sword) && (!visit_with_sword[nx][ny])) {
				visit_with_sword[nx][ny] = true;
				que.push(new Node(nx, ny, cur->time + 1, true));
			}
			else if(!visited[nx][ny] && map[nx][ny]!=1){
				visited[nx][ny] = true;
				que.push(new Node(nx, ny, cur->time + 1, false));
			}
		}
		if (end) break;
	}

	if (end && cur->time+1 <= T)
			cout << cur->time + 1<< endl;
	else cout << "Fail\n";
}