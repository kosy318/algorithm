#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
	int N, answer = INT_MAX;
	cin >> N;

	vector<vector<int>> cost(N, vector<int>(3));

	for (int i = 0; i < N; i++) 
		cin >> cost[i][0] >> cost[i][1] >> cost[i][2];
	
	vector<vector<int>> dp(N, vector<int>(3));
	for (int i = 0; i < 3; i++) { // 첫번째 집이 i번 색을 선택했을 때
		dp[0][i] = cost[0][i];
		for (int j = 0; j < 3; j++)
			if (j != i) dp[0][j] = INT_MAX;
		
		for (int j = 1; j < N; j++) { // 나머지 집 색 선택
			if((dp[j][0] = cost[j][0] + min(dp[j - 1][1], dp[j - 1][2])) < 0)
				dp[j][0] = INT_MAX;
			if ((dp[j][1] = cost[j][1] + min(dp[j - 1][0], dp[j - 1][2])) < 0)
				dp[j][1] = INT_MAX;
			if ((dp[j][2] = cost[j][2] + min(dp[j - 1][1], dp[j - 1][0])) < 0)
				dp[j][2] = INT_MAX;
		}

		for (int j = 0; j < 3; j++) {
			if (j != i) answer = min(answer, dp[N - 1][j]);
		}
	}

	cout << answer;
}