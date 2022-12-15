#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// N을 1로 만들때 필요한 최소 연산 횟수를 저장할 배열
vector<int> dp;
int main() {
	int N;
	cin >> N;

	dp = vector<int>(N + 1, -1);
	dp[1] = 0;

	for (int i = 2; i <= N; i++) {
		// 1. N-1 연산의 경우
		dp[i] = dp[i - 1] + 1;

		// 2. N/2 연산의 경우
		if (i % 2 == 0 && dp[i / 2] + 1 < dp[i]) dp[i] = dp[i / 2] + 1;

		// 3. N/3 연산의 경우
		if (i % 3 == 0 && dp[i / 3] + 1 < dp[i]) dp[i] = dp[i / 3] + 1;
	}

	cout << dp[N];
}