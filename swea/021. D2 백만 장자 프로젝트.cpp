// https://jolly-note.tistory.com/54

#include <iostream>
#include <set>
#include <map>
#include <vector>

using namespace std;

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		int day, price;
		cin >> day;
		vector<int> days;
		map<int, int> price_cnt;
		for (int j = 0; j < day; j++) {
			cin >> price;
			price_cnt[price] += 1;
			days.push_back(price);
		}

		set<int> prices(days.begin(), days.end());
		long long result = 0;
		for (auto d : days) {
			price_cnt[d] -= 1;

			result += (*prices.rbegin() - d);
			if (price_cnt[d] == 0) prices.erase(d);
		}
		cout << "#" << i + 1 << " " << result << '\n';
	}

	return 0;
}