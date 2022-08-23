#include <iostream>
#include <vector>

using namespace std;

int N;
vector<vector<int>> palin_dp;
vector<int> numbers;

int is_palin(int i, int j) {
	if (numbers[i] != numbers[j]) {
		palin_dp[i][j] = 0;
	} else if ((i == j) || (j == i+1 && numbers[i] == numbers[j])) {
		palin_dp[i][j] = 1;
	} else if(palin_dp[i][j] == -1) {
		palin_dp[i][j] = is_palin(i + 1, j - 1);
	}
	return palin_dp[i][j];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N;
	numbers = vector<int>(N+1);
	for (int i = 1; i <= N; i++)
		cin >> numbers[i];

	palin_dp = vector<vector<int>>(N + 1, vector<int>(N + 1, -1));

	int M;
	cin >> M;
	for (int i = 0; i < M; i++) {
		int x, y;
		cin >> x >> y;
		cout << is_palin(x, y) << "\n";
	}
}