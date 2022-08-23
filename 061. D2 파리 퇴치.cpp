#include <iostream>
#include <vector>

using namespace std;

int main() {
	int t;
	cin >> t;
	for (int tc = 1; tc <= t; tc++) {
		int kill = 0, n, m;
		cin >> n >> m;

		vector<vector<int>> map;
		for (int i = 0; i < n; i++) {
			vector<int> temp(n);
			for (int j = 0; j < n; j++) {
				cin >> temp[j];
			}
			map.push_back(temp);
		}

		pair<int, int> pivot = { 0, 0 };
		while (true) {
			int temp = 0;
			for (int i = pivot.first; i < pivot.first + m; i++) {
				for (int j = pivot.second; j < pivot.second + m; j++) {
					temp += map[i][j];
				}
			}
			if (kill < temp) kill = temp;

			pivot.second += 1;
			if (pivot.second + m - 1 == n) {
				pivot.first += 1;
				pivot.second = 0;
			}
			if (pivot.first + m - 1 == n) break;
		}

		cout << "#" << tc << " " << kill << endl;
	}
}