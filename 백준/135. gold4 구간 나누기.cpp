#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
	int N, M;
	cin >> N >> M;

	vector<int> nums(N + 1);
	vector<int> sum(N + 1, 0);
	for (int i = 1; i <= N; i++) {
		cin >> nums[i];
		sum[i] = sum[i - 1] + nums[i];
	}

	vector<vector<int>> dp(N + 1, vector<int>(M + 1, INT_MIN));
	dp[1][1] = nums[1];

	for (int i = 1; i <= N; i++) {
		dp[i][1] = max(dp[i][1], dp[i - 1][1]);
		for (int k = 0; k <= i - 1; k++) {
			dp[i][1] = max(dp[i][1], sum[i] - sum[k]);
		}
	}

	for (int j = 2; j <= M; j++) {
		for (int i = 1; i <= N; i++) {
			if (j > (int)ceil((double)i / 2)) continue;
			dp[i][j] = max(dp[i][j], dp[i - 1][j]);
			for (int k = 0; k <= i - 2; k++) {
				if (dp[k][j - 1] == INT_MIN) continue;
				for (int l = k + 1; l < i; l++) { // 여러칸을 띄는 경우도 가능
					dp[i][j] = max(dp[i][j], dp[k][j - 1] + sum[i] - sum[l]);
				}
			}
		}
	}

	/*for (auto ii : dp) {
		for (int i : ii) { 
			if (i == INT_MIN) cout << "- ";
			else cout << i << " ";
		}
		cout << endl;
	}*/

	cout << dp[N][M];
}