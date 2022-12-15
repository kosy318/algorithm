#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> answer;

vector<bool> find_num(int x, int y, vector<string>& puzzle) {
	vector<bool> possible_num(10, true);
	// 가로
	for (int j = 0; j < 9; j++) {
		possible_num[puzzle[x][j]-'0'] = false;
	}

	// 세로
	for (int i = 0; i < 9; i++) {
		possible_num[puzzle[i][y] - '0'] = false;
	}

	// 네모
	x = 3 * (x / 3);
	y = 3 * (y / 3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			possible_num[puzzle[x + i][y + j] - '0'] = false;
		}
	}

	return possible_num;
}

void solve(vector<string> puzzle, int x = 0, int y = 0) {
	if (!answer.empty()) return;
	int j = y;
	for (; j < 9; j++) {
		if (puzzle[x][j] == '0') {
			y = j;
			break;
		} 
		else if (j == 8) {
			if (x == 8) {
				answer = puzzle;
			}
			else {
				x += 1;
				j = -1;
			}
		}
	}

	vector<bool> possible_num = find_num(x, y, puzzle);
	int cnt = 0;
	for (int n = 1; n <= 9; n++) {
		if (!possible_num[n]) continue;
		puzzle[x][y] = (char)(n+'0');
		solve(puzzle, x, y);
	}
}

int main() {
	vector<string> puzzle(9);
	vector<vector<bool>> rows(9, vector<bool>(10));

	for (int i = 0; i < 9; i++) {
		cin >> puzzle[i];
	}

	solve(puzzle);

	for (string ans : answer)
		cout << ans << "\n";
}