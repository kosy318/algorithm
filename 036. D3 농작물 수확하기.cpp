// https://jolly-note.tistory.com/73

// i = 0부터 시작해서
// 중간 column을 찾은 뒤(index기준 N/2)
// i를 1씩 증가시켜가며 앞뒤로 i번째까지 더한다.
// row가 N/2를 넘어가면 i를 1씩 감소하기 시작해서
// 데이터를 다 받아오면 끝난다.

#include<iostream>

using namespace std;

int main() {
	int tc;
	cin >> tc;
	for (int t = 0; t < tc; t++) {
		int N, answer = 0;
		cin >> N;
		int i = 0, add = 1, mid = N / 2;

		for (int j = 0; j < N; j++) {
			int start = mid - i, end = mid + i, num;
			for (int k = 0; k < N; k++) {
				scanf("%1d", &num);
				if (k >= start && k <= end) {
					answer += num;
				}
			}
			if (j == mid) add = -1;
			i += add;
		}
		cout << "#" << t + 1 << " " << answer << endl;
	}
}