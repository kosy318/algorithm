#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<vector<int>> green(6, vector<int>(4));
vector<vector<int>> blue(6, vector<int>(4));

int score = 0;

void organize(vector<vector<int>>& vec) {
	int target = 5;
	int move = 5;
	while (true) {
		for (int i = target; i >= 0; i--) {
			if (vec[i][0] == -1) {
				target = i;
				break;
			}
		}
		for (int i = target - 1; i >= 0; i--) {
			if (vec[i][0] != -1) {
				move = i;
				break;
			}
		}
		if (vec[target][0] != -1 || vec[move][0] == -1 || target == move) break;

		for (int j = 0; j < 4; j++) {
			vec[target][j] = vec[move][j];
			vec[move][0] = -1;
		}
	}
	if (vec[target][0] == -1) {
		for (int j = 0; j < 4; j++)
			vec[target][j] = 0;
	}
	if (vec[move][0] == -1) {
		for (int j = 0; j < 4; j++)
			vec[move][j] = 0;
	}
}

void delete_overflow(vector<vector<int>>& vec) {
	int height = -1;
	for (int i = 0; i <= 1; i++) {
		for (int j = 0; j < 4; j++) {
			if (vec[i][j] > 0) {
				height = i;
				break;
			}
		}
		if (height != -1) break;
	}
	if (height == -1) return;

	for (int i = 5; i >= 4 + height; i--) {
		vec[i][0] = -1;
	}
	organize(vec);
}

void get_score(vector<vector<int>>& vec) {
	for (int i = 0; i < 6; i++) {
		int cnt = 0;
		for (int j = 0; j < 4; j++) {
			if (vec[i][j] != 0) cnt += 1;
		}
		if (cnt == 4) {
			score += 1;
			vec[i][0] = -1; // 지워야하는 칸임을 표시
		}
	}

	organize(vec);
}

// y좌표가 같으면 위로 쌓고, 다르면 오른쪽으로 쌓으면 됨
void put(vector<vector<int>>& vec, int x1, int y1, int y2 = -1) {
	int height = 5;
	for (int i = 0; i < 6; i++) {
		if (vec[i][y1] == 0) {
			if (y2 != -1 && vec[i][y2] == 0)
				height = i;
			else if (y2 == -1) height = i;
		}
		if (vec[i][y1] != 0 || (y2 != -1 && vec[i][y2] != 0)) break;
	}

	vec[height][y1] = 1;
	if (y2 != -1) {
		if (y1 == y2) vec[height - 1][y2] = 1;
		else vec[height][y2] = 1;
	}
}

void shape(int b, int x, int y) {
	if (b == 1) {
		put(green, x, y);
		put(blue, y, x);
	}
	else if (b == 2) {
		put(green, x, y, y + 1);
		put(blue, y + 1, x, x);
	}
	else if (b == 3) {
		put(green, x + 1, y, y);
		put(blue, y, x, x + 1);
	}

}

void get_order(int N) {
	for (int i = 0; i < N; i++) {
		int block, x, y;
		cin >> block >> x >> y;

		shape(block, x, y);
		get_score(green);
		get_score(blue);

		delete_overflow(green);
		delete_overflow(blue);
	}
}

int count_blocks(vector<vector<int>>& vec) {
	int cnt = 0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			if (vec[i][j] > 0) cnt += 1;
		}
	}
	return cnt;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;

	get_order(N);

	cout << score << "\n" << count_blocks(green) + count_blocks(blue);
}