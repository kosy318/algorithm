#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

enum {
	MAX, MIN
};

int main() {
	int N;
	cin >> N;
	vector<vector<int>> dp(3, vector<int>(2));
	vector<vector<int>> next_dp(3, vector<int>(2));
	int num;
	for (int i = 0; i < 3; i++) {
		cin >> dp[i][MAX];
		dp[i][MIN] = dp[i][MAX];
	}
	for (int i = 1; i < N; i++) {
		for (int j = 0; j < 3; j++) {
			// max
			int max_num = dp[j][MAX];
			if (j - 1 >= 0) max_num = max(max_num, dp[j - 1][MAX]);
			if (j + 1 < 3) max_num = max(max_num, dp[j + 1][MAX]);
			next_dp[j][MAX] = max_num;

			// min
			int min_num;
			min_num = dp[j][MIN];
			if (j - 1 >= 0) min_num = min(min_num, dp[j - 1][MIN]);
			if (j + 1 < 3) min_num = min(min_num, dp[j + 1][MIN]);
			next_dp[j][MIN] = min_num;
		}
		for (int k = 0; k < 3; k++) {
			cin >> num;
			dp[k][MAX] = next_dp[k][MAX] + num;
			dp[k][MIN] = next_dp[k][MIN] + num;
		}
	}

	cout << max(dp[0][MAX], max(dp[1][MAX], dp[2][MAX])) << " ";
	cout << min(dp[0][MIN], min(dp[1][MIN], dp[2][MIN]));
}