// https://jolly-note.tistory.com/64?category=1025701

#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

int answer = -1;

void dfs(string res, int ch) {
	if (is_sorted(res.rbegin(), res.rend())) {
		string u_res(res);
		auto it = unique(u_res.begin(), u_res.end());

		if (ch % 2 == 0 || distance(u_res.begin(), it) < res.length()) {
			answer = stoi(res);
			return;
		}
		else {
			char temp = res[res.length() - 1];
			res[res.length() - 1] = res[res.length() - 2];
			res[res.length() - 2] = temp;
			answer = stoi(res);
			return;
		}
	}

	for (int i = 0; i < res.length(); i++) {
		char temp = res[i];
		auto iter = max_element(res.begin() + i, res.end());
		for (int j = i + 1; j < res.length(); j++) {
			if (*iter > res[j]) continue;
			res[i] = res[j];
			res[j] = temp;

			if (ch - 1 == 0) {
				if (stoi(res) > answer) answer = stoi(res);
			}
			else if (ch - 1 > 0) dfs(res, ch - 1);
			res[j] = res[i];
			res[i] = temp;
		}
	}
}

int main() {
	int tc, num, change;
	cin >> tc;

	string str;
	for (int i = 0; i < tc; i++) {
		cin >> num >> change;
		if (change == 0) {
			cout << "#" << i + 1 << " " << answer << endl;
		}
		answer = -1;
		str = to_string(num);

		dfs(str, change);

		cout << "#" << i + 1 << " " << answer << endl;
	}
}