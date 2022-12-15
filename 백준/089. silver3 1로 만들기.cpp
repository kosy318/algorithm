#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// N�� 1�� ���鶧 �ʿ��� �ּ� ���� Ƚ���� ������ �迭
vector<int> dp;
int main() {
	int N;
	cin >> N;

	dp = vector<int>(N + 1, -1);
	dp[1] = 0;

	for (int i = 2; i <= N; i++) {
		// 1. N-1 ������ ���
		dp[i] = dp[i - 1] + 1;

		// 2. N/2 ������ ���
		if (i % 2 == 0 && dp[i / 2] + 1 < dp[i]) dp[i] = dp[i / 2] + 1;

		// 3. N/3 ������ ���
		if (i % 3 == 0 && dp[i / 3] + 1 < dp[i]) dp[i] = dp[i / 3] + 1;
	}

	cout << dp[N];
}