#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

set<string> answer_set;

vector<int> dir_x = { 0, 0, 1, -1 };
vector<int> dir_y = { 1, -1, 0, 0 };

void go(int x, int y, vector<vector<string>>& map, string str="", int cnt=0) {
	if (cnt == 7) {
		answer_set.insert(str);
		return;
	}
	for (int i = 0; i < 4; i++) {
		int nx = x + dir_x[i];
		int ny = y + dir_y[i];
		if (nx < 0 || ny < 0 || nx >= 4 || ny >= 4) continue;

		go(nx, ny, map, str + map[x][y], cnt+1);
	}
}

int main() {
	int tc;
	cin >> tc;
	for (int t = 1; t <= tc; t++) {
		answer_set.clear();
		vector<vector<string>> map(4, vector<string>(4));
		vector<vector<bool>> visit(4, vector<bool>(4));

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cin >> map[i][j];
			}
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				go(i, j, map);
			}
		}

		cout << "#" << t << " " << answer_set.size() << "\n";
	}
}