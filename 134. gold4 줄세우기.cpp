#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int N;
	cin >> N;
	vector<int> nums(N);

	for (int i = 0; i < N; i++) {
		cin >> nums[i];
	}

	vector<int> cnt(N, 1);
	int max_cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < i; j++) {
			if (nums[i] > nums[j] && cnt[i] < cnt[j] + 1) cnt[i] = cnt[j] + 1;
			max_cnt = max(max_cnt, cnt[i]);
		}
	}

	cout << N - max_cnt;
}