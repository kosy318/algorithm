#include <iostream>
#include <vector>

using namespace std;

int main() {
	int N;
	cin >> N;
	vector<int> num(N);
	for (int i = 0; i < N; i++)
		cin >> num[i];

	vector<int> dp(N, 1);
	dp[0] = 1;

	int ans = 1;
	for (int i = 1; i < N; i++) {
		for (int j = 0; j < i; j++) {
			if (num[j] < num[i] && dp[i] < dp[j] + 1)  dp[i] = dp[j] + 1;
		}
		if (ans < dp[i]) ans = dp[i];
	}

	cout << ans;
}