#include <iostream>
#include <vector>

using namespace std;

int main() {
	int N;
	cin >> N;
	vector<int> dp(N + 1);
	if(N >= 2)dp[2] = 3;
	if (N % 2 == 1) cout << "0";
	else if (N == 2) cout << "3";
	else {
		for (int i = 4; i <= N; i += 2) {
			dp[i] += dp[i - 2] * dp[2];

			for (int j = i - 4; j >= 2 && j<=N; j -= 2) {
				dp[i] += dp[j] * 2;
			}

			dp[i] += 2;
		}
		cout << dp[N];
	}
}