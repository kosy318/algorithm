#include <iostream>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int N, M;
		cin >> N >> M;
		int last_n_bit = (1 << N) - 1; // 111..1(���� N)
		
		// ((last_n_bit & M) == last_n_bit : last N bit�� ���� 1���� Ȯ��
		cout << "#" << t << " " << (((last_n_bit & M) == last_n_bit)?"ON":"OFF") << "\n";
	}
}