#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	string str1, str2;
	cin >> str1 >> str2;

	vector<vector<int>> dp(str2.length(), vector<int>(str1.length()));

	int max = 0;
	for (int i = 0; i < str2.length(); i++) {
		for (int j = 0; j < str1.length(); j++) {
			if (str2[i] == str1[j]) {
				if (i - 1 < 0 || j - 1 < 0) dp[i][j] = 1;
				else dp[i][j] = dp[i - 1][j - 1] + 1;

				if (max < dp[i][j]) max = dp[i][j];
			}
		}
	}

	cout << max;
}