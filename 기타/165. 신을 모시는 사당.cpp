#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N; // ������ ����
	cin >> N;


	vector<int> statue(N + 1); // ������ �ٶ󺸰� �ִ� ����; ����: 1, ������ 2
	vector<int> dp(N + 1);
	vector<int> sum(N + 1); // ������
	vector<int> minSum(N + 1);
	vector<int> maxSum(N + 1);

	for (int i = 1; i <= N; i++) {
		cin >> statue[i];
		if (statue[i] == 2) statue[i] = -1; // ������ 1, �������� -1�� ����
		sum[i] = sum[i - 1] + statue[i];
		minSum[i] = min(minSum[i - 1], sum[i]);
		maxSum[i] = max(maxSum[i - 1], sum[i]);
	}

	for (int n = 1; n <= N; n++) {
		// dp[n]�� ó���� n��° ������ �������� �ʴ� ��찡 ������
		// n��° ������ �����ϴ� ��찡 �� ũ�ų� �������� Ȯ���ؼ� ����
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