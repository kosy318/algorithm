#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	int N; // ��ǰ�� ��
	int weight_limit; // ��ƿ �� �ִ� ����
	cin >> N >> weight_limit;

	int weight[101];
	int value[101];
	for (int i = 1; i <= N; i++) {
		cin >> weight[i];
		cin >> value[i];
	}


	int dp[101][100001];
	// dp[i][j] = max(dp[i-1][j], dp[i-1][j-weight[i]] + value[i]); j���Ա��� ��ƿ �� ���� ��, (i�� �ȳ��� ��) vs (i�� ���� ��)

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= weight_limit; j++) {
			if (j - weight[i] >= 0) dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
			else dp[i][j] = dp[i - 1][j]; // i��° ������ ���ſ��� �� �� ���ٸ�
		}
	}

	cout << dp[N][weight_limit];
}