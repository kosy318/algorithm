#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int N, K;
	cin >> N >> K;

	vector<int> cost(N);
	vector<int> dp(K + 1, -1);
	for (int i = 0; i < N; i++)
		cin >> cost[i];

	sort(cost.rbegin(), cost.rend());

	for (int c : cost) {
		int n = 1;
		while (c*n <= K) {
			if (dp[c*n] == -1) dp[c*n] = n;
			n += 1;
		}
	}


	for (int i = 1; i <= K; i++) {
		for (auto c : cost) {
			if (i - c < 0 || dp[i - c] == -1) continue;
			dp[i] = (dp[i] == -1) ? dp[i - c] + dp[c] : min(dp[i], dp[i - c] + dp[c]);
		}
	}

	cout << dp[K];
}