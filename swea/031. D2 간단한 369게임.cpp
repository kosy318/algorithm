#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main() {
	// string���� ���� ���ڸ����� Ȯ���ϴ� ���ÿ� '-' ���
	// 3, 6, 9�� ����ִ��� Ȯ���ϴ� bool�ʿ�
	// 3, 6, 9�� �ƴϸ� ���� �״�� ���
	// 3, 6, 9������ %3�� 0���� Ȯ���ϸ� �ȴ�.

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