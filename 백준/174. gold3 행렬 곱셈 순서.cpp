#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int main() {
	int N;
	cin >> N; // 행렬의 개수
	
	vector<pair<int, int>> matrix(N + 1);
	for (int i = 1; i <= N; i++) {
		int r, c;
		cin >> r >> c;

		matrix[i] = { r, c };
	}


	// dp[i][j]: i~j까지 곱했을 때 연산 수
	vector<vector<int>> dp(N + 1, vector<int>(N + 1));
	for (int range = 1; range <= N; range++) {
		for (int start = 1; start + range <= N; start++) {
			dp[start][start + range] = INT_MAX;
			for (int div = start; div < start + range; div++) {
				dp[start][start + range] = min(dp[start][start + range],
					dp[start][div] + dp[div + 1][start + range] + matrix[start].first*matrix[div].second*matrix[start + range].second);
			}
		}
	}

	cout << dp[1][N];
}