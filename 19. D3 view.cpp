// https://jolly-note.tistory.com/52

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	for (int i = 0; i < 10; i++) {
		vector<int> buildings;
		vector<int> leftside;
		int n, building;
		cin >> n;
		pair<int, int> side = { 0, 0 };
		for (int j = 0; j < n; j++) {
			cin >> building;
			buildings.push_back(building);
			leftside.push_back(building - max(side.first, side.second));
			if (leftside.back() < 0) leftside.back() = 0;
			side.second = side.first;
			side.first = building;
		}

		int temp = 0, result = 0;
		side = { 0, 0 };
		for (int j = n - 1; j >= 0; j--) {
			temp = buildings[j] - max(side.first, side.second);
			side.second = side.first;
			side.first = buildings[j];
			if (temp < 0) continue;
			if (temp < leftside[j]) result += temp;
			else result += leftside[j];
		}

		cout << "#" << i + 1 << " " << result << '\n';
	}
	return 0;
}