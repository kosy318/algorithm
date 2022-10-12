#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int map[101][101];
int max_x, max_y;

// 오른쪽 위 왼쪽 아래(반시계)
int dx[] = { 0, -1, 0, 1 };
int dy[] = { 1, 0, -1, 0 };

int find_squares() {
	int answer = 0;
	for (int i = 0; i <= max_x; i++) {
		for (int j = 0; j <= max_y; j++) {
			int up = 0, left = 0, di = 0;
			if (map[i][j] == 1) {
				if (i - 1 >= 0) up = map[i - 1][j];
				if (j - 1 >= 0) left = map[i][j - 1];
				if (i - 1 >= 0 && j - 1 >= 0) di = map[i - 1][j - 1];

				map[i][j] = min(di, min(up, left)) + 1;

				if (map[i][j] >= 2) answer += 1;
			}
		}
	}
	return answer;
}

void draw(int x, int y, int dir, int gen) {
	vector<int> directions;
	directions.push_back(dir);
	map[x][y] = 1;
	x += dx[dir];
	y += dy[dir];
	map[x][y] = 1;
	if (max_x < x) max_x = x;
	if (max_y < y) max_y = y;

	while (directions.size() < pow(2, gen)) {
		for (int i = directions.size()-1; i >= 0; i--) {
			int ndir = (directions[i] + 1)%4;
			directions.push_back(ndir);

			x += dx[ndir];
			y += dy[ndir];
			if (x < 0 || y < 0 || x > 100 || y>100) continue;
			map[x][y] = 1;

			if (max_x < x) max_x = x;
			if (max_y < y) max_y = y;
		}
	}
}

int main() {
	int N;
	cin >> N;
	
	int x, y, dir, gen;
	for (int i = 0; i < N; i++) {
		cin >> y >> x >> dir >> gen;

		draw(x, y, dir, gen);
	}

	cout<<find_squares();
}