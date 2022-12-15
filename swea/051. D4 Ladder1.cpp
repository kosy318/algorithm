#include <iostream>
#include <vector>

using namespace std;

int main() {
	for (int i = 0; i < 10; i++) {
		int tc;
		cin >> tc;
		
		vector<vector<int>> ladder_map;
		vector<int> start_idx;
		for (int i = 0; i < 100; i++) {
			vector<int> row(100);
			for (int j = 0; j < 100; j++) {
				cin >> row[j];
				if (i == 0 && row[j] == 1) start_idx.push_back(j);
			}
			ladder_map.push_back(row);
		}

		vector<int> dir_x = { 1, 0, 0 };
		vector<int> dir_y = { 0, -1, 1 };
		int answer = -1;
		for (int start : start_idx) {
			vector<int> cur = { 0, start };
			bool left = true, right = true;
			while (true) {
				if (left && cur[1] + dir_y[1] >= 0 && ladder_map[cur[0]][cur[1] + dir_y[1]] == 1) {
					right = false;
					cur[1] += dir_y[1];
				}
				else if (right && cur[1] + dir_y[2] < 100 && ladder_map[cur[0]][cur[1] + dir_y[2]] == 1) {
					left = false;
					cur[1] += dir_y[2];
				}
				else {
					left = true;
					right = true;
					if (cur[0] + dir_x[0] < 100) {
						if(ladder_map[cur[0] + dir_x[0]][cur[1]] == 1) cur[0] += dir_x[0];
						else if (ladder_map[cur[0] + dir_x[0]][cur[1]] == 2) {
							answer = start;
							break;
						}
					}
					else break;
				}
			}

			if (answer != -1) break;
		}

		cout << "#" << tc << " " << answer << endl;
	}
}