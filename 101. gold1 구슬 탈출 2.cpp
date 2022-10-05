#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int N, M, answer = 11;
const int CNT = 10;
pair<int, int> hole;
vector<string> board;

// 상 하 좌 우
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

void move(pair<int, int> red, pair<int, int> blue, int cnt) { // cnt번 움직임
	if (blue == hole) return;
	else if (red == hole) {
		answer = min(answer, cnt);
		return;
	}
	else if (cnt == 10)
		return;

	for (int d = 0; d < 4; d++) {
		int rx = red.first, ry = red.second;
		int bx = blue.first, by = blue.second;

		bool red_stop = false, blue_stop = false;

		while (!red_stop || !blue_stop) {
			if (!red_stop) {
				rx += dx[d];
				ry += dy[d];
				if (board[rx][ry] == 'O') {
					red_stop = true;
				}
				else if (rx <= 0 || ry <= 0 || rx >= N - 1 || ry >= M - 1 || board[rx][ry] == '#') {
					red_stop = true;
					rx -= dx[d];
					ry -= dy[d];
				}
			}

			if (!blue_stop) {
				bx += dx[d];
				by += dy[d];
				if (board[bx][by] == 'O') {
					blue_stop = true;
				}
				else if (bx <= 0 || by <= 0 || bx >= N - 1 || by >= M - 1 || board[bx][by] == '#') {
					blue_stop = true;
					bx -= dx[d];
					by -= dy[d];
				}
			}

			if (!red_stop && make_pair(bx, by) != hole && rx == bx && ry == by) {
				rx -= dx[d];
				ry -= dy[d];
				if (blue_stop) red_stop = true;
			}
			if (!blue_stop && make_pair(rx, ry) != hole && rx == bx && ry == by) {
				bx -= dx[d];
				by -= dy[d];
				if (red_stop) blue_stop = true;
			}
		}

		move({ rx, ry }, { bx, by }, cnt + 1);
	}
}

int main() {
	cin >> N >> M;

	pair<int, int> red, blue;
	for (int i = 0; i < N; i++) {
		string str;
		cin >> str;
		board.push_back(str);

		for (int j = 0; j < M; j++) {
			if (board[i][j] == 'R') {
				board[i][j] = '.';
				red = { i, j };
			}
			else if (board[i][j] == 'B') {
				board[i][j] = '.';
				blue = { i, j };
			}
			else if (board[i][j] == 'O') hole = { i, j };
		}
	}

	move(red, blue, 0);

	if(answer <= 10) cout << answer;
	else cout << "-1";
}