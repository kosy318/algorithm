// https://jolly-note.tistory.com/72

// ���� ��� ���� �ϳ��� �� �� ����
// �밢�������� Ȯ���ϸ��. ���� x��ǥ������ ���̿� y��ǥ������ ���̰� ������ �밢���� ����
// ��� ���� ��á���� ��


#include<iostream>
#include<vector>

using namespace std;

int N, answer;
vector<int> chess(14); // �� ���Ҵ� n��° ���� ��� column�� chess�� �����ִ����� ��Ÿ�����ִ�.
vector<bool> columns(14, false);

void dfs(int row = 0) { // row��° �࿡ ���� ����
	if (row == N) {
		answer++;
		return;
	}
	for (int i = 0; i < N; i++) { // ��� column�� ������
		// ���� ���� �������
		if (columns[i]) continue;
		// �밢���� �������
		bool conti = false;
		for (int j = 0; j < row; j++) { // row�� �� ����� ���鼭
			if (abs(row - j) == abs(i - chess[j])) conti = true;
		}
		if (conti) continue;
		chess[row] = i;
		columns[i] = true;
		dfs(row + 1);
		columns[i] = false;
	}
}

int main() {
	int tc;
	cin >> tc;
	for (int i = 0; i < tc; i++) {
		answer = 0;
		cin >> N;

		dfs();
		cout << "#" << i + 1 << " " << answer << endl;
	}
}