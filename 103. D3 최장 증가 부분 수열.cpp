#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int tc;
	cin >> tc;
	for (int t = 1; t <= tc; t++) {
		int N;
		cin >> N;
		vector<int> nums(N);
		for (int i = 0; i < N; i++) {
			cin >> nums[i];
		}

		vector<int> dp(N, 1);
		for (int i = 1; i < N; i++) {
			for (int j = 0; j < i; j++) {
				if (nums[i] >= nums[j] && dp[j] + 1 > dp[i]) dp[i] = dp[j] + 1;
			}
		}

		cout << "#" << t << " " << *max_element(dp.begin(), dp.end()) << endl;
	}
}