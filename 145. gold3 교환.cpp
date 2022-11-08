#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <set>

using namespace std;

int main() {
	string str;
	int K;
	cin >> str >> K;

	queue<pair<string, int>> que;
	que.push({ str, 0 });

	while (!que.empty()) {
		int size = que.size();
		int count = que.front().second;
		set<string> visited;
		for (int n = 0; n < size; n++) {
			pair<string, int> cur = que.front();
			que.pop();

			for (int i = 0; i < str.length() - 1; i++) {
				for (int j = i + 1; j < str.length(); j++) {
					if (i == 0 && cur.first[j] == '0') continue;
					string new_str = cur.first;
					char temp = new_str[j];
					new_str[j] = new_str[i];
					new_str[i] = temp;
					if (visited.find(new_str) != visited.end()) continue;

					que.push({ new_str, cur.second + 1 });
					visited.insert(new_str);
				}
			}
		}
		if (count == K - 1) break;
	}

	int answer = -1;
	while (!que.empty()) {
		answer = max(answer, stoi(que.front().first));
		que.pop();
	}

	cout << answer;
}