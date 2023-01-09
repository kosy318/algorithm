#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	int N; // 물품의 수
	int weight_limit; // 버틸 수 있는 무게
	cin >> N >> weight_limit;

	int weight[101];
	int value[101];
	for (int i = 1; i <= N; i++) {
		cin >> weight[i];
		cin >> value[i];
	}


	int dp[101][100001];
	// dp[i][j] = max(dp[i-1][j], dp[i-1][j-weight[i]] + value[i]); j무게까지 버틸 수 있을 때, (i를 안넣은 것) vs (i를 넣은 것)

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= weight_limit; j++) {
			if (j - weight[i] >= 0) dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
			else dp[i][j] = dp[i - 1][j]; // i번째 물건이 무거워서 들어갈 수 없다면
		}
	}

	cout << dp[N][weight_limit];
}