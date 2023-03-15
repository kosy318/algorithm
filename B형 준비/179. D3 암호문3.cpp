#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

void do_command(list<int>& cryp, char command) {
	int x, y, s;
	list<int>::iterator iter = cryp.begin();

	switch (command) {
	case 'I':
		// x := 추가하는 위치
		// y := 추가 할 원소의 개수
		cin >> x >> y;
		advance(iter, x);
		for (int i = 0; i < y; i++) {
			cin >> s;
			cryp.insert(iter, s);
		}
		break;
	case 'D':
		// x := 삭제하는 위치
		// y := 삭제 할 원소의 개수
		cin >> x >> y;
		advance(iter, x);
		for (int i = 0; i < y; i++) {
			cryp.erase(iter++);
		}
		break;
	case 'A':
		// y := 추가 할 원소의 개수
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
		int N; // 원본 암호문의 길이
		cin >> N;

		list<int> cryp; // 전체 수열을 관리하는 링크드리스트
		for (int i = 0; i < N; i++) {
			int num;
			cin >> num;
			cryp.push_back(num);
		}

		int M; // 명령어의 개수
		cin >> M;
		for (int i = 0; i < M; i++) {
			char command; // 명령어
			cin >> command;
			do_command(cryp, command); // 명령 수행
		}

		cout << "#" << t << " ";
		for (int i = 0; i < 10; i++) {
			cout << cryp.front() << " ";
			cryp.pop_front();
		}
		cout << "\n";
	}
}