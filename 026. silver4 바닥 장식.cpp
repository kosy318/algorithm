// https://jolly-note.tistory.com/61

#include<iostream>
#include<vector>

using namespace std;

int x, y;
vector<vector<char>> map;
vector<vector<bool>> visited;
int dfs(int i, int j) {
	visited[i][j] = true;
	if (map[i][j] == '|') {
		if (i + 1 == x || map[i + 1][j] != '|') return 1;
		return dfs(i + 1, j);
	}
	else if (map[i][j] == '-') {
		if (j + 1 == y || map[i][j + 1] != '-') return 1;
		return dfs(i, j + 1);
	}
	return 0;
}

int main() {
	cin >> x >> y;
	char tile;
	map = vector<vector<char>>(x, vector<char>(y, 'o'));
	visited = vector<vector<bool>>(x, vector<bool>(y, false));
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			cin >> tile;
			map[i][j] = tile;
		}
	}

	int cnt = 0;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (!visited[i][j]) cnt += dfs(i, j);
		}
	}

	cout << cnt << endl;
}