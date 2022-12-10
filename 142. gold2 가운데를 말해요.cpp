#include <iostream>
#include <set>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;

	multiset<int> nums;
	int num;
	cin >> num;
	nums.insert(num);

	auto it = nums.begin();
	cout << *it << "\n";
	for (int i = 0; i < N - 1; i++) {
		int cur = *it;
		cin >> num;
		nums.insert(num);

		if (nums.size() % 2 == 1 && cur <= num) {
			++it;
		}
		else if (nums.size() % 2 == 0 && cur > num) {
			--it;
		}

		cout << *it << "\n";
	}
}