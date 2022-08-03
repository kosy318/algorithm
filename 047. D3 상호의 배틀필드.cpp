#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	int tc;
	cin >> tc;

	for (int t = 1; t <= tc; t++) {
		int H, W;
		cin >> H >> W;

		vector<string> map;

		char heading = '^';
		vector<int> cur(2, 0);

		for (int i = 0; i < H; i++) { // map 입력
			string row;
			cin >> row;
			map.push_back(row);

			for (int j = 0; j < W; j++) {
				if (map[i][j] == '^' || map[i][j] == 'v' || map[i][j] == '<' || map[i][j] == '>') {
					heading = map[i][j];
					map[i][j] = '.';
					cur[0] = i; cur[1] = j;
				}
			}
		}

		int num;
		cin >> num;
		string inputs;
		cin >> inputs;
		int shoot = 0;

		for (char ch : inputs) {
			switch (ch) {
			case 'U':
				heading = '^';
				if (cur[0] - 1 >= 0 && map[cur[0] - 1][cur[1]] == '.') {
					cur[0] -= 1;
				}
				break;
			case 'D':
				heading = 'v';
				if (cur[0] + 1 < H && map[cur[0] + 1][cur[1]] == '.') {
					cur[0] += 1;
				}
				break;
			case 'L':
				heading = '<';
				if (cur[1] - 1 >= 0 && map[cur[0]][cur[1] - 1] == '.') {
					cur[1] -= 1;
				}
				break;
			case 'R':
				heading = '>';
				if (cur[1] + 1 < W && map[cur[0]][cur[1] + 1] == '.') {
					cur[1] += 1;
				}
				break;
			case 'S':
				switch (heading) {
				case '^':
					shoot = cur[0];
					while (shoot >= 0) {
						if (map[shoot][cur[1]] == '*') {
							map[shoot][cur[1]] = '.';
							break;
						}
						else if (map[shoot][cur[1]] == '#') break;
						shoot -= 1;
					}
					break;
				case 'v':
					shoot = cur[0];
					while (shoot < H) {
						if (map[shoot][cur[1]] == '*') {
							map[shoot][cur[1]] = '.';
							break;
						}
						else if (map[shoot][cur[1]] == '#') break;
						shoot += 1;
					}
					break;
				case '<':
					shoot = cur[1];
					while (shoot >= 0) {
						if (map[cur[0]][shoot] == '*') {
							map[cur[0]][shoot] = '.';
							break;
						}
						else if (map[cur[0]][shoot] == '#') break;
						shoot -= 1;
					}
					break;
				case '>':
					shoot = cur[1];
					while (shoot < W) {
						if (map[cur[0]][shoot] == '*') {
							map[cur[0]][shoot] = '.';
							break;
						}
						else if (map[cur[0]][shoot] == '#') break;
						shoot += 1;
					}
					break;
				}
				break;
			}
		} // 사용자 입력에 따른 상태 변화 완료

		map[cur[0]][cur[1]] = heading;

		cout << "#" << t << " ";
		for (string str : map) {
			for (char ch : str) {
				cout << ch;
			}
			cout << endl;
		}
	}
}