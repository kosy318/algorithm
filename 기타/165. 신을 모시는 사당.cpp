#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N; // 돌상의 개수
	cin >> N;


	vector<int> statue(N + 1); // 돌상이 바라보고 있는 방향; 왼쪽: 1, 오른쪽 2
	vector<int> dp(N + 1);
	vector<int> sum(N + 1); // 누적합
	vector<int> minSum(N + 1);
	vector<int> maxSum(N + 1);

	for (int i = 1; i <= N; i++) {
		cin >> statue[i];
		if (statue[i] == 2) statue[i] = -1; // 왼쪽은 1, 오른쪽은 -1로 저장
		sum[i] = sum[i - 1] + statue[i];
		minSum[i] = min(minSum[i - 1], sum[i]);
		maxSum[i] = max(maxSum[i - 1], sum[i]);
	}

	for (int n = 1; n <= N; n++) {
		// dp[n]에 처음엔 n번째 돌상을 포함하지 않는 경우가 들어가있음
		// n번째 돌상을 포함하는 경우가 더 크거나 작은지를 확인해서 대입
		int max_value = max(abs(sum[n] - minSum[n]), abs(sum[n] - maxSum[n]));
		dp[n] = max(dp[n - 1], max_value);
	}

	// check
	/*for (int i = 1; i <= N; i++)
		cout << minDp[i] << " ";
	cout << endl;
	for (int i = 1; i <= N; i++)
		cout << maxDp[i] << " ";
	cout << endl;*/

	cout << dp[N];
}