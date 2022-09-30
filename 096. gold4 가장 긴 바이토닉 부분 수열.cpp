#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int N;
	cin >> N;
	vector<int> num(N);
	for (int i = 0; i < N; i++)
		cin >> num[i];
	
	vector<int> inc_dp(N, 1);
	vector<int> dec_dp(N, 1);
	vector<int> total(N);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < i; j++) {
			// increase
			if (num[i] > num[j] && inc_dp[i] < inc_dp[j] + 1) inc_dp[i] = inc_dp[j] + 1;

			// decrease
			if (num[N - i - 1] > num[N - j - 1] && dec_dp[N - i - 1] < dec_dp[N - j - 1] + 1) dec_dp[N - i - 1] = dec_dp[N - j - 1] + 1;
		}
		total[i] += inc_dp[i];
		total[N - i - 1] += dec_dp[N - i - 1];
	}

	cout << *max_element(total.begin(), total.end()) - 1;
}