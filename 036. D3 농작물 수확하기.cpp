// https://jolly-note.tistory.com/73

// i = 0���� �����ؼ�
// �߰� column�� ã�� ��(index���� N/2)
// i�� 1�� �������Ѱ��� �յڷ� i��°���� ���Ѵ�.
// row�� N/2�� �Ѿ�� i�� 1�� �����ϱ� �����ؼ�
// �����͸� �� �޾ƿ��� ������.

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