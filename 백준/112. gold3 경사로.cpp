#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int N, L;
	cin >> N >> L;

	vector<vector<int>> map(N, vector<int>(N));
	int answer = 0;
	for (int i = 0; i < N; i++) {
		int cnt = 1;
		bool possible = true, rev = false;
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (j - 1 >= 0) {
				if (map[i][j - 1] == map[i][j]) cnt += 1;
				else if (map[i][j - 1] - 1 == map[i][j]) {
					if (rev && cnt < L) possible = false;
					cnt = 1;
					rev = true;
				}
				else if (map[i][j - 1] == map[i][j] - 1) {
					if (cnt < L) possible = false;
					if (rev && cnt < 2 * L) possible = false;
					cnt = 1;
					rev = false;

				}
				else if (abs(map[i][j - 1] - map[i][j]) >= 2) possible = false;
			}
		}
		if (rev && cnt < L) possible = false;
		if (possible) answer += 1;
	}

	for (int j = 0; j < N; j++) {
		int cnt = 1;
		bool possible = true, rev = false;
		for (int i = 0; i < N; i++) {
			if (i - 1 >= 0) {
				if (map[i - 1][j] == map[i][j]) cnt += 1;
				else if (map[i - 1][j] - 1 == map[i][j]) {
					if (rev && cnt < L) possible = false;
					cnt = 1;
					rev = true;
				}
				else if (map[i - 1][j] == map[i][j] - 1) {
					if (cnt < L) possible = false;
					if (rev && cnt < 2 * L) possible = false;
					cnt = 1;
					rev = false;

				}
				else if (abs(map[i - 1][j] - map[i][j]) >= 2) possible = false;
			}
		}
		if (rev && cnt < L) possible = false;
		if (possible) answer += 1;
	}

	cout << answer << "\n";
}