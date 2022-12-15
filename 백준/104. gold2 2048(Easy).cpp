#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_MOVE = 5;
int N;
int answer = -1;

vector<vector<int>> move_up_down(int up_down, vector<vector<int>> board, int cnt) {
	int add = (up_down == 0)? 1 : -1;

	int collapse = (up_down == 0)? -1 : N;
	bool collapsed;
	for (int j = 0; j < N; j++) {
		collapsed = false;
		int i = collapse + add;
		while(i >=0 && i < N){
			if (board[i][j] != 0) {
				if ((collapse != -1 && collapse != N) && board[collapse][j] == board[i][j]) {
					board[collapse][j] *= 2;
					board[i][j] = 0;
					if (cnt == MAX_MOVE) answer = max(answer, board[collapse][j]);
					collapse += add;
					collapsed = true;
				}
				else {
					if (!collapsed) {
						board[collapse + add][j] = board[i][j];
						if (i != collapse + add) board[i][j] = 0;
						collapse += add;
					}
					else {
						board[collapse][j] = board[i][j];
						if (i != collapse) board[i][j] = 0;
					}
					collapsed = false;
					if (cnt == MAX_MOVE) answer = max(answer, board[collapse][j]);
				}
			}
			i += add;
		}
		collapse = (up_down == 0)? -1 : N;
	}
	return board;
}

vector<vector<int>> move_left_right(int left_right, vector<vector<int>> board, int cnt) {
	int add = (left_right == 2) ? 1 : -1;

	int collapse = (left_right == 2) ? -1 : N;
	bool collapsed;
	for (int i = 0; i < N; i++) {
		collapsed = false;
		int j = collapse + add;
		while (j >= 0 && j < N) {
			if (board[i][j] != 0) {
				if ((collapse != -1 && collapse != N) && board[i][collapse] == board[i][j]) {
					board[i][collapse] *= 2;
					board[i][j] = 0;
					if (cnt == MAX_MOVE) answer = max(answer, board[i][collapse]);
					collapse += add;
					collapsed = true;
				}
				else {
					if (!collapsed) {
						board[i][collapse + add] = board[i][j];
						if (j != collapse + add) board[i][j] = 0;
						collapse += add;
					}
					else {
						board[i][collapse] = board[i][j];
						if (j != collapse) board[i][j] = 0;
					}
					collapsed = false;
					if (cnt == MAX_MOVE) answer = max(answer, board[i][collapse]);
				}
			}
			j += add;
		}
		collapse = (left_right == 2) ? -1 : N;
	}
	return board;
}

void move(vector<vector<int>> board, int cnt = 0, int moved = -1) {
	if (cnt == MAX_MOVE)
		return;

	// »óÇÏ
	move(move_up_down(0, board, cnt+1), cnt + 1, 0);
	move(move_up_down(1, board, cnt + 1), cnt + 1, 1);

	// ÁÂ¿ì
	move(move_left_right(2, board, cnt + 1), cnt + 1, 2);
	move(move_left_right(3, board, cnt + 1), cnt + 1, 3);
}

int main() {
	cin >> N;

	vector<vector<int>> board(N, vector<int>(N));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}

	move(board);

	cout << answer;
}