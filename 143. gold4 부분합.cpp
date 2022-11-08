#include <iostream>

using namespace std;

int N, S;
int answer = 0;
int nums[100000];

void bi_search() {
	int right = 0, sum = nums[0];
	for (int left = 0; left < N; left++) {
		while (right < N) {
			if (sum >= S) {
				if (left == right) {
					answer = 1;
					return;
				}
				else if (answer == 0 || (answer != 0 && answer > right - left + 1)) {
					answer = right - left + 1;
					break;
				}
			}
			if (answer != 0 && right - left + 1 >= answer) break;
			right += 1;
			sum += nums[right];
		}
		sum -= nums[left];
		while (sum > S) {
			sum -= nums[right];
			right -= 1;
			if (left + 1 == right) break;
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

	bi_search();

	cout << answer;
}