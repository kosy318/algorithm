#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main() {
	int m, n;
	cin >> m >> n;

	string answer = "";
	vector<bool> number(n + 1, true);

	for (int i = 2; i <= n; i++) {
		if (number[i]) {
			if (i >= m) answer += to_string(i) + "\n";
			for (int j = i * 2; j <= n; j += i) {
				number[j] = false;
			}
		}
	}

	cout << answer;
}