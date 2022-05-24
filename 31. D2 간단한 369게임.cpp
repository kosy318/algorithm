#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main() {
	// string으로 만들어서 한자리수씩 확인하는 동시에 '-' 출력
	// 3, 6, 9가 들어있는지 확인하는 bool필요
	// 3, 6, 9가 아니면 숫자 그대로 출력
	// 3, 6, 9인지는 %3이 0인지 확인하면 된다.

	int N;
	cin >> N;

	for (int i = 1; i <= N; i++) {
		bool clap = false;
		string num = to_string(i);

		for (auto n : num) {
			if ((n - '0') % 3 == 0 && (n - '0') != 0) {
				clap = true;
				cout << '-';
			}
		}
		(!clap) ? cout << num << " " : cout << " ";
	}
}