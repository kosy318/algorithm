#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int divide(int x, int y, int len);

vector<vector<int>> map;

int main() {
	int N;
	cin >> N;
	map = vector<vector<int>>(N, vector<int>(N));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	cout << divide(0, 0, N);
}

int divide(int x, int y, int len) {
	if (len == 1) return map[x][y];

	vector<int> nums = { divide(x, y, len / 2),
						divide(x, y + len / 2, len / 2),
						divide(x + len / 2, y, len / 2),
						divide(x + len / 2, y + len / 2, len / 2) };

	sort(nums.rbegin(), nums.rend());
	return nums[1];
}