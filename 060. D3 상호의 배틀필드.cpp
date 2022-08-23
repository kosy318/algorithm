#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

void move(vector<int>& cur, int heading);
bool is_in(int x, int y);

vector<string> game_map;
int H, W;
vector<int> dir_x = { -1, 1, 0, 0 };
vector<int> dir_y = { 0, 0, -1, 1 };
vector<char> heading_char = { '^', 'v', '<', '>' };

int main() {


	int tc;
	cin >> tc;
	for (int t = 1; t <= tc; t++) {
		vector<int> cur(2);
		int heading;
		cin >> H >> W;

		game_map = vector<string>(H);
		for (int i = 0; i < H; i++) {
			cin >> game_map[i];
			for (int j = 0; j < W; j++) {
				for (int h = 0; h < 4; h++)
					if (heading_char[h] == game_map[i][j]) {
						heading = h;
						cur = { i, j };
						game_map[i][j] = '.';
					}
			}
		}

		int N;
		string order;
		cin >> N >> order;

		for (auto ch : order) {
			switch (ch) {
			case 'U':
				heading = 0;
				break;
			case 'D':
				heading = 1;
				break;
			case 'L':
				heading = 2;
				break;
			case 'R':
				heading = 3;
				break;
			case 'S':
				int nx = cur[0] + dir_x[heading];
				int ny = cur[1] + dir_y[heading];
				while (is_in(nx, ny)) {
					if (game_map[nx][ny] == '*') {
						game_map[nx][ny] = '.';
						break;
					}
					else if (game_map[nx][ny] == '#') break;
					nx += dir_x[heading];
					ny += dir_y[heading];
				}
				break;
			}

			if (ch != 'S') move(cur, heading);
		}

		game_map[cur[0]][cur[1]] = heading_char[heading];
		cout << "#" << t << " ";
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				cout << game_map[i][j];
			}
			cout << "\n";
		}
	}
}

void move(vector<int>& cur, int heading) {
	int nx = cur[0] + dir_x[heading];
	int ny = cur[1] + dir_y[heading];

	if (is_in(nx, ny) && game_map[nx][ny]=='.') {
		cur = { nx, ny };
	}
}

bool is_in(int x, int y) {
	if (x < 0 || y < 0 || x >= H || y >= W) return false;
	return true;
}