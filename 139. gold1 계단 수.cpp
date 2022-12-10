#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<vector<vector<long long>>> dp(101, vector<vector<long long>>(10, vector<long long>(1 << 10, 0)));
	for(int k=1; k<10; k++)
		dp[1][k][1 << k] = 1;

	int N;
	cin >> N;

	for (int i = 2; i <= N; i++) {
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < (1 << 10); k++) {
				if (j - 1 >= 0)dp[i][j][k | 1<<j] += dp[i - 1][j - 1][k] % 1000000000;
				if (j + 1 < 10)dp[i][j][k | 1<<j] += dp[i - 1][j + 1][k] % 1000000000;
			}
		}
	}

	long long answer = 0;
	for (int j = 0; j < 10; j++)
		answer = (answer + dp[N][j][(1 << 10) -1]) % 1000000000;
	cout << answer;
}