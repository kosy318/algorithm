#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

long long answer = 0;

void calc(vector<int>& nums) {
	int N = nums.size();
	int idx1 = 0;
	int idx2 = 1;
	while (true) {
		if (idx2 >= N) {
			if (idx1 == N - 1) {
				answer += nums[idx1];
			}
			break;
		}
		if (nums[idx1] == 1 || nums[idx2] == 1 || nums[idx1] * nums[idx2] < 0 || nums[idx1] >= 0 && nums[idx2] == 0) {
			answer += nums[idx1];
			idx1 = idx2;
			idx2 += 1;
			continue;
		}

		answer += nums[idx1] * nums[idx2];
		idx1 += 2;
		idx2 += 2;
	}
}

int main() {
	int N;
	cin >> N;

	vector<int> positive;
	vector<int> negative;
	int num;
	for (int i = 0; i < N; i++) {
		cin >> num;
		if (num > 0) positive.push_back(num);
		else negative.push_back(num);
	}

	sort(positive.rbegin(), positive.rend());
	sort(negative.begin(), negative.end());

	calc(positive);
	calc(negative);

	cout << answer << endl;
}