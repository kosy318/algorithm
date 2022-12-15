#include <iostream>
#include <string>
#include <deque>

using namespace std;

int main() {
	int N, K;
	cin >> N >> K;

	string answer;
	cin >> answer;

	deque<char> st;
	int i = 0, cnt = 0;
	for (; i < N && cnt < K; i++) {
		while (!st.empty() && st.back() < answer[i]) {
			st.pop_back();
			cnt += 1;
			if (cnt == K) break;
		}

		st.push_back(answer[i]);
	}
	while (cnt != K) {
		st.pop_back();
		cnt += 1;
	}

	while (!st.empty()) {
		cout << st.front();
		st.pop_front();
	}
	for (int j = i; j < N; j++)
		cout << answer[j];
}