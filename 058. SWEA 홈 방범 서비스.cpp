#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int search(int range, int pay, vector<vector<int>> map, vector<vector<int>>& city_xy) {
	if (range == 1 && pay - 1 >= 0) return 1;
	int k_cost = range * range + (range - 1) * (range - 1);
	int maximum = -1;
	for (auto vec : city_xy) {
		map[vec[0]][vec[1]] -= 1;
		int cnt = 0, add = 1;
		for (int i = vec[0] - range + 1; i < vec[0] + range; i++) {
			cnt += add;
			if (i >= 0 && i < map.size())
				for (int j = 0; j < cnt; j++) {
					if (vec[1] - j >= 0) {
						map[i][vec[1] - j]++;
						maximum = max(maximum, map[i][vec[1] - j]);
					}
					if (vec[1] + j < map.size() && j != 0) {
						map[i][vec[1] + j]++;
						maximum = max(maximum, map[i][vec[1] + j]);
					}
				}
			if (i == vec[0]) add = -1;
		}
	}

	if (maximum*pay - k_cost >= 0) return maximum;
	else return -1;
}

int main() {
	int tc;
	cin >> tc;
	for (int t = 1; t <= tc; t++) {
		int city_size, pay;
		cin >> city_size >> pay;

		vector<vector<int>> map(city_size, vector<int>(city_size));
		vector<vector<int>> city_xy;
		for (int i = 0; i < city_size; i++) {
			for (int j = 0; j < city_size; j++) {
				cin >> map[i][j];
				if (map[i][j] == 1) city_xy.push_back({ i, j });
			}
		}

		int answer = -1;
		for (int i = 1; i <= city_size + 1; i++) {
			int result = search(i, pay, map, city_xy);
			answer = max(answer, result);
		}

		cout << "#" << t << " " << answer << "\n";
	}
}