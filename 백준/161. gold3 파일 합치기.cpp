#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

// dp[i][j] : i~j ������ �������� ��� �ּ� ���
int dp[501][501];

int main() {
	int T;
	cin >> T;
	while(T--) {
		int N; // ���� ��
		cin >> N;

		int* nums = new int[N + 1];
		int* sum = new int[N + 1]; // ���� ��
		for (int i = 1; i <= N; i++) {
			cin >> nums[i];
			sum[i] = sum[i - 1] + nums[i];
		}

		for (int range = 1; range <= N; range++) {
			for (int start = 1; start + range <= N; start++) {
				dp[start][start + range] = INT_MAX;
				int total = sum[start + range] - sum[start - 1];
				for (int div = start; div < start + range; div++) {
					dp[start][start + range] = min(dp[start][start + range], dp[start][div] + dp[div + 1][start + range] + total);
				}
			}
		}

		cout << dp[1][N] << "\n";
	}
}