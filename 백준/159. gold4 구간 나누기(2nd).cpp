#include <stdio.h>

using namespace std;

#define MIN -4000000

int ceil(double d) {
	if ((int)d != d) return (int)d + 1;
	else return (int)d;
}

// DP
int main() {
	int N; // 숫자의 개수
	int nums[101]; // N개의 수로 이루어진 1차원 배열
	int sum[101]; // 누적 합
	int M; // M개의 구간을 선택
	int dp[101][51]; // DP[n][m]: n번째 숫자까지 고려했을 때 m개의 구간으로 나눈 최대 합

	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &nums[i]);
		sum[i] = sum[i - 1] + nums[i];
	}

	// dp 초기화
	dp[0][1] = nums[1];
	for (int n = 1; n <= N; n++) {
		dp[n][1] = dp[n - 1][1]; // n번째 숫자까지 한개의 구간으로 나눈 값은 일단 n-1 번째 숫자까지 1개의 구간으로 나눈 값으로 초기화

		// dp[n][1]에 처음엔 n번째 숫자를 포함하지 않는 경우가 들어가있음
		for (int k = 0; k < n; k++) { // 한개의 구간이 n번째 숫자를 포함하는 경우가 더 큰지 확인해서 대입
			if (dp[n][1] < sum[n] - sum[k])
				dp[n][1] = sum[n] - sum[k];
		}

		for (int m = 2; m <= M; m++) {
			dp[n][m] = MIN;
		}
	}

	// dp[n][m]을 구할 때, 
	for (int n = 2; n <= N; n++) {
		for (int m = 2; m <= ceil((double)n / 2); m++) {
			// n번째 숫자까지 고려하지만 n번째 숫자가 포함되지 않는 경우와 포함 되는 경우 중 큰 것을 대입
			if (dp[n][m] < dp[n - 1][m])
				dp[n][m] = dp[n - 1][m];

			// n번째 숫자가 포함되는 경우 n번째 숫자는 m번째 구간에 속하게 된다.
			// 어떤 숫자부터 m번째 구간에 속하는지 알 수 없으므로, k를 정해서 k번째 숫자까지 m-1 개의 구간을 나누고, k+2번째 숫자부터 n번째 숫자까지 m번째 구간으로 취급하면 된다.
			// 즉, k번째 숫자까지 포함하고 m-1 구간을 가지는 경우인 dp[k][m-1]에 m번째 구간에 속하는 k+1번째 숫자 이후의! 숫자부터 n번째 숫자까지의 합을 더하면 m개의 구간을 가지게 된다.
			// 이때 k번째 숫자는 m-1번째 구간에 속하므로 n번째 숫자와 연속해서 붙어있을 수 없으므로 최대 n-2번째 숫자를 가리킬 수 있다.
			for (int k = 1; k <= n - 2; k++) {
				if (dp[k][m - 1] == MIN) continue;
				for (int t = k + 1; t < n; t++) { // k번째 숫자 이후의 숫자들 중 몇번째(t번째) 숫자부터 n번째 숫자까지 m번째 구간으로 넣을건지
					if (dp[n][m] < dp[k][m - 1] + sum[n] - sum[t])
						dp[n][m] = dp[k][m - 1] + sum[n] - sum[t];
				}
			}
		}
	}

	printf("%d", dp[N][M]);
}