#include <iostream>

using namespace std;

int N, S;
int answer = 0;
int nums[100000];

void search() {
	int right = 0, sum = nums[0];
	for (int left = 0; left < N; left++) {
		while (right < N) {
			if (sum >= S) { // 조건을 만족하면
				if (left == right) {
					answer = 1;
					return;
				}
				else if (answer == 0 || (answer != 0 && answer > right - left + 1)) {
					answer = right - left + 1;
					break;
				}
			}
            // 조건을 만족하지 못했을 때
			if (answer != 0 && right - left + 1 >= answer) break; // 가지치기1
			right += 1;
			sum += nums[right];
		}
		sum -= nums[left];
		while (sum > S) {
			sum -= nums[right];
			right -= 1;
			if (left == right) break; // 가지치기2
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> S;

	for (int i = 0; i < N; i++) {
		cin >> nums[i];
	}

	search();

	cout << answer;
}