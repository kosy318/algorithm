#include <iostream>
#include <vector>

using namespace std;

int main() {
	int N, K;
	cin >> N >> K;

	vector<vector<long long>> dp(K + 1, vector<long long>(N + 1));

	for (int j = 1; j <= N; j++)
		dp[1][j] = 1;

	for (int i = 1; i <= K; i++)
		dp[i][1] = i;

	for (int i = 2; i <= K; i++) {
		for (int j = 2; j <= N; j++) {
			dp[i][j] = (dp[i - 1][j] + dp[i][j - 1])%1000000000;
		}
	}

	cout << dp[K][N];
}