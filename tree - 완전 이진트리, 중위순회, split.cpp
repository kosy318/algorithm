#include <iostream>
#include <string>
#include <sstream>

using namespace std;

char* arr;
int n;

void dfs(int cur) {
	if (cur > n) return;

	dfs(cur * 2); // ���� �ڽ�
	cout << arr[cur]; // �θ�
	dfs(cur * 2 + 1); // ������ �ڽ�
}

char split(string inp) {
	stringstream ss(inp);
	string temp;
	int cnt = 1;

	while (getline(ss, temp, ' ')) {
		if (cnt == 2) return temp[0];
		cnt += 1;
	}

	return ' ';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	for (int t = 1; t <= 10; t++) {
		cout << "#" << t << " ";

		cin >> n;
		arr = new char[n + 1];

		string inp;
		cin.ignore(); // getline �ϱ� �� �Է¹��� ����
		for (int i = 1; i <= n; i++) {
			getline(cin, inp);
			arr[i] = split(inp);
		}

		dfs(1); // ���� ��ȸ
		cout << "\n";
	}
}