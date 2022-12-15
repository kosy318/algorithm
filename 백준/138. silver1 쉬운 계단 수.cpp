#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<vector<long long>> dp(101, vector<long long>(10, 0));
	dp[1][0] = 0;
	for (int j = 1; j < 10; j++) {
		dp[1][j] = 1;
	}

	int N;
	cin >> N;

	for (int i = 2; i <= N; i++) {
		for (int j = 0; j < 10; j++) {
			if (j - 1 >= 0)dp[i][j] += dp[i - 1][j - 1] % 1000000000;
			if (j + 1 < 10)dp[i][j] += dp[i - 1][j + 1] % 1000000000;
		}
	}

	int answer = 0;
	for (int j = 0; j < 10; j++)
		answer = (answer + dp[N][j]) % 1000000000;
	cout << answer;
}