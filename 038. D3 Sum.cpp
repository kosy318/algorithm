// ���� �����͸� �޾ƿ��鼭 ���� �� �ִ�
// ���� ���ϸ鼭 �ִ밪�� Ȯ���Ѵ�.
// 0,0���� ��� ���� 1�� ������Ű�� ���Ѵ�.
// 0,99���� ���� +1 ���� -1���ϸ� ���Ѵ�.

#include <iostream>
#include <vector>

using namespace std;

int main() {
	int tc, num;
	// ��� ���ο� ���� "����"�Ұ��̱� ������ �Ź� ���͸� �ʱ�ȭ ���� �ʿ� ����.
	vector<vector<int>> vec(100, vector<int>(100, 0));
	for (int t = 0; t < 10; t++) {
		cin >> tc;
		int answer = 0;
		int temp = 0;
		for (int i = 0; i < 100; i++) {
			temp = 0;
			for (int j = 0; j < 100; j++) {
				cin >> num;
				vec[i][j] = num;
				temp += num;
			}
			if (answer < temp) answer = temp;
		}

		// column����
		for (int j = 0; j < 100; j++) {
			temp = 0;
			for (int i = 0; i < 100; i++) {
				temp += vec[i][j];
			}
			if (answer < temp) answer = temp;
		}

		// �밢�� ���������� ������ �Ʒ�
		temp = 0;
		int i = 0, j = 0;
		while (true) {
			temp += vec[i][j];
			i++; j++;
			if (i == 100) break;
		}
		if (answer < temp) answer = temp;

		// �밢�� ������������ ���� �Ʒ�
		temp = 0;
		i = 0; j = 99;
		while (true) {
			temp += vec[i][j];
			i++; j--;
			if (i == 100) break;
		}
		if (answer < temp) answer = temp;

		cout << "#" << tc << " " << answer << endl;
	}
}