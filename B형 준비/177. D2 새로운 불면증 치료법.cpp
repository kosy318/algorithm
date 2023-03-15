#include <iostream>
#include <string>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int testcase;
	cin >> testcase;
	int total = (1 << 10) - 1; // ��� ���ڰ� �������� ���� ��

	for (int i = 1; i <= testcase; i++) {
		int N; // �Էµ� ��
		cin >> N;

		int visited = 0; // ������� �� ���ڵ��� bit�� ǥ���� �� ex) 3, 7, 9 => 1010001000(2)
		int count = 0; // �̶����� �� ���� ����((N*count)���� �ô�)
		for (count = 1; ; count++) {
			string arr = to_string(N * count);

			for (char c : arr) {
				visited |= (1 << (c - '0')); // �� ���ڿ� ���� �����ߴٴ� �ǹ̷� bit�� 1�� ����
			}
			if (visited == total) break; // ��� ���ڰ� �����ߴٸ�, ����
		}
		cout << "#" << i << " " << N * count << "\n";
	}
}