#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

vector<int> top;
vector<vector<int>> magnetics;

void move(int m, int turn) {
	vector<int> turned(top);
	turned[m] -= turn;
	int turn_next = turn * (-1);
	for (int i = m; i <= 4; i++) {
		if (i + 1 <= 4) {
			int right = top[i] + 2;
			if (right > 7) right = right - 8;

			int left = top[i + 1] - 2;
			if (left < 0) left = 8 + left;

			if (magnetics[i][right] == magnetics[i + 1][left]) break;
			else {
				turned[i + 1] -= turn_next;
				turn_next *= -1;
			}
		}
	}

	turn_next = turn * (-1);
	for (int i = m; i >= 1; i--) {
		if (i - 1 >= 1) {
			int right = top[i - 1] + 2;
			if (right > 7) right = right - 8;

			int left = top[i] - 2;
			if (left < 0) left = 8 + left;

			if (magnetics[i][left] == magnetics[i - 1][right]) break;
			else {
				turned[i - 1] -= turn_next;
				turn_next *= -1;
			}
		}
	}

	for (int i = 1; i <= 4; i++) {
		if (turned[i] < 0) turned[i] = 7;
		else if (turned[i] > 7) turned[i] = 0;
	}
	top = turned;
}

int main() {
	top = vector<int>(5, 0);
	magnetics = vector<vector<int>>(5, vector<int>(8));
	// N극 0, S극 1
	for (int i = 1; i <= 4; i++) {
		string str;
		cin >> str;
		for (int j = 0; j < 8; j++) {
			magnetics[i][j] = (str[j] - '0');
		}
	}
	int K;
	cin >> K;

	// 시계방향 1, 반시계방향 -1
	int magnetic, turn;
	for (int i = 0; i < K; i++) {
		cin >> magnetic >> turn;
		move(magnetic, turn);
	}

	int answer = 0;
	for (int i = 1; i <= 4; i++) {
		answer += (magnetics[i][top[i]] == 0) ? 0 : pow(2, i - 1);
	}

	cout << answer << endl;
}