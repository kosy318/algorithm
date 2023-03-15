#include <iostream>
#include <string>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int testcase;
	cin >> testcase;
	int total = (1 << 10) - 1; // 모든 숫자가 등장했을 때의 값

	for (int i = 1; i <= testcase; i++) {
		int N; // 입력된 수
		cin >> N;

		int visited = 0; // 현재까지 본 숫자들을 bit로 표현한 수 ex) 3, 7, 9 => 1010001000(2)
		int count = 0; // 이때까지 본 수의 개수((N*count)까지 봤다)
		for (count = 1; ; count++) {
			string arr = to_string(N * count);

			for (char c : arr) {
				visited |= (1 << (c - '0')); // 각 숫자에 대해 등장했다는 의미로 bit를 1로 변경
			}
			if (visited == total) break; // 모든 숫자가 등장했다면, 종료
		}
		cout << "#" << i << " " << N * count << "\n";
	}
}