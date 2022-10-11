#include <iostream>
#include <vector>

using namespace std;

int main() {
	int N, sushi, k, coupon;
	int answer = 1, total = 1;
	cin >> N >> sushi >> k >> coupon;

	vector<int> belt(N);

	for (int i = 0; i < N; i++) {
		cin >> belt[i];
	}

	int set[3001] = { 0, };
	set[coupon] = 1;
	for (int i = 0; i < k; i++) {
		if (set[belt[i]] == 0) total += 1;
		set[belt[i]] += 1;
	}

	answer = total;

	int start = 1;
	for (; start < N; start++) {
		int end = (start + k - 1) % N;

		set[belt[start - 1]] -= 1;
		if (set[belt[start - 1]] == 0) total -= 1;

		if (set[belt[end]] == 0) total += 1;
		set[belt[end]] += 1;

		if (answer < total) answer = total;
		if (answer == k + 1) break;
	}

	cout << answer;
}