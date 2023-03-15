#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

void do_command(list<int>& cryp, char command) {
	int x, y, s;
	list<int>::iterator iter = cryp.begin();

	switch (command) {
	case 'I':
		// x := �߰��ϴ� ��ġ
		// y := �߰� �� ������ ����
		cin >> x >> y;
		advance(iter, x);
		for (int i = 0; i < y; i++) {
			cin >> s;
			cryp.insert(iter, s);
		}
		break;
	case 'D':
		// x := �����ϴ� ��ġ
		// y := ���� �� ������ ����
		cin >> x >> y;
		advance(iter, x);
		for (int i = 0; i < y; i++) {
			cryp.erase(iter++);
		}
		break;
	case 'A':
		// y := �߰� �� ������ ����
		cin >> y;
		for (int i = 0; i < y; i++) {
			cin >> s;
			cryp.push_back(s);
		}
		break;
	default:
		break;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	for (int t = 1; t <= 10; t++) {
		int N; // ���� ��ȣ���� ����
		cin >> N;

		list<int> cryp; // ��ü ������ �����ϴ� ��ũ�帮��Ʈ
		for (int i = 0; i < N; i++) {
			int num;
			cin >> num;
			cryp.push_back(num);
		}

		int M; // ��ɾ��� ����
		cin >> M;
		for (int i = 0; i < M; i++) {
			char command; // ��ɾ�
			cin >> command;
			do_command(cryp, command); // ��� ����
		}

		cout << "#" << t << " ";
		for (int i = 0; i < 10; i++) {
			cout << cryp.front() << " ";
			cryp.pop_front();
		}
		cout << "\n";
	}
}