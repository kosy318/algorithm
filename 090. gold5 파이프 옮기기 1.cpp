#include<iostream>
#include<vector>

using namespace std;

vector<vector<vector<int>>> dp;
vector<vector<int>> map;
int N;

enum {
	HORI, VERTI, DI
};

int main() {
	cin >> N;
	map = vector<vector<int>>(N + 1, vector<int>(N + 1));
	dp = vector<vector<vector<int>>>(N + 1, vector<vector<int>>(N + 1, vector<int>(3, 0)));

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 2; i <= N; i++) {
		if (map[1][i] == 1) break;
		dp[1][i][HORI] = 1;
	}


	for (int i = 2; i <= N; i++) {
		for (int j = 2; j <= N; j++) {
			if (map[i][j] == 1)continue;
			dp[i][j][HORI] = dp[i][j - 1][HORI] + dp[i][j - 1][DI];
			dp[i][j][VERTI] = dp[i - 1][j][VERTI] + dp[i - 1][j][DI];

			if (map[i - 1][j] == 1 || map[i][j - 1] == 1) continue;
			dp[i][j][DI] = dp[i - 1][j - 1][HORI] + dp[i - 1][j - 1][VERTI] + dp[i - 1][j - 1][DI];
		}
	}

	cout << dp[N][N][VERTI] + dp[N][N][HORI] + dp[N][N][DI];
}