#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int N = 4;

struct Fish{
	int x, y;
	int dir;
	int num;

	Fish(int x=0, int y=0, int dir = 0, int num = 0) : x{ x }, y{ y }, dir{ dir }, num{ num }{}
};

int dx[] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
int answer = -1;

void moves(vector<vector<Fish>> board, map<int, Fish> fish_map, Fish shark=Fish(), int x = 0, int y = 0) {
	Fish dead = board[x][y];
	shark.x = x;
	shark.y = y;
	shark.dir = dead.dir;
	shark.num += dead.num;
	fish_map.erase(dead.num);
	board[x][y] = Fish();

	for (auto m : fish_map) {
		int ndir = m.second.dir;
		int nx = m.second.x + dx[ndir];
		int ny = m.second.y + dy[ndir];

		bool skip = false;
		while (nx < 0 || ny < 0 || nx >= N || ny >= N || (nx == shark.x && ny == shark.y)) {
			ndir += 1;
			if (ndir > 8)ndir -= 8;
			nx = m.second.x + dx[ndir];
			ny = m.second.y + dy[ndir];

			if (ndir == m.second.dir) {
				skip = true;
				break;
			}
		}
		if (skip) continue;
		
		if (board[nx][ny].num != 0) {
			Fish temp = board[nx][ny];
			temp.x = m.second.x;
			temp.y = m.second.y;

			board[nx][ny] = Fish(nx, ny, ndir, m.second.num);
			fish_map[m.second.num] = board[nx][ny];
			board[temp.x][temp.y] = temp;
			fish_map[temp.num] = temp;
		}
		else {
			board[nx][ny] = Fish(nx, ny, ndir, m.second.num);
			board[m.second.x][m.second.y] = Fish();
			fish_map[m.second.num] = board[nx][ny];
		}
	}
	int nx = shark.x + dx[shark.dir];
	int ny = shark.y + dy[shark.dir];
	bool end = true;
	while (nx >= 0 && ny >= 0 && nx < N && ny < N) {
		if (board[nx][ny].num != 0) {
			end = false;
			moves(board, fish_map, shark, nx, ny);
		}

		nx += dx[shark.dir];
		ny += dy[shark.dir];
	}
	if (end) {
		answer = max(answer, shark.num);
	}
}

int main() {
	vector<vector<Fish>> board(N, vector<Fish>(N));
	map<int, Fish> fish_map;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int dir, num;
			cin >> num >> dir;
			board[i][j] = Fish(i, j, dir, num);
			fish_map[num] = board[i][j];
		}
	}

	moves(board, fish_map);

	cout << answer;
}