#include <iostream>
#include <list>

using namespace std;

int N; // 수열의 길이
int M; // 추가 횟수
int L; // 출력할 인덱스 번호

struct NODE {
	int value;
	NODE* prev;
	NODE* next;
	NODE() {}
	NODE(int value, NODE* prev, NODE* next) : value(value), prev(prev), next(next) {}
}*head;

int cnt; // linked list node 개수

void print() {
	NODE* cur = head;
	for (int i = 0; i < cnt; i++) {
		cout << cur->value << " ";
		cur = cur->next;
	}
	cout << endl;
}

void print(int idx) {
	if (idx > cnt) {
		cout << "-1";
	}
	else {
		NODE* cur = head;
		while (idx--) cur = cur->next;
		cout << cur->value;
	}
}

void add(int x) { // 맨 뒤에 추가
	NODE* cur = head;;
	if (cnt == 0) { // 아직 하나도 없음
		head = new NODE(x, 0, 0);
		cur = head;
	}
	else {
		for (int i = 1; i < cnt; i++) // 맨 뒤 node로 이동
			cur = cur->next;
		cur->next = new NODE(x, cur, 0);
		cur = cur->next; // 현재 위치를 다음 위치로 입력
	}

	cnt++;
}

void insertData(int idx, int x) { // idx 위치에 x 삽입
	if (idx == 0) { // head에 삽입하는 경우
		if (cnt != 0) { // 값이 존재한다면
			NODE* newNode = new NODE(x, 0, head); // 새 노드의 다음 노드는 head
			head->prev = newNode;
			head = newNode;
		}
		else head = new NODE(x, 0, 0);
	}
	else {
		NODE* cur = head;
		while (--idx) cur = cur->next;
		NODE* newNode = new NODE(x, cur, cur->next);
		if (cur->next) cur->next->prev = newNode;
		cur->next = newNode;
	}

	cnt++;
}

void deleteData(int idx) {
	NODE* cur = head;
	while (idx--) cur = cur->next;
	NODE* prev = cur->prev, *next = cur->next; // 지울 노드의 전과 다음 node
	if (prev) prev->next = next;
	else head = next;

	if (next) next->prev = prev;

	cnt--;
}

void setData(int idx, int x) {
	NODE* cur = head;
	while (idx--) cur = cur->next;
	cur->value = x;
}

void input() {
	for (int i = 0; i < N; i++) {
		int x;
		cin >> x;
		add(x);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cnt = 0; // linked list node 개수 초기화

		cin >> N >> M >> L;

		input(); // 수열의 정보 입력

		for (int i = 0; i < M; i++) { // CUD
			char order;
			cin >> order;

			int idx, x;
			switch (order) {
			case 'I':
				cin >> idx >> x;
				insertData(idx, x);
				break;
			case 'D':
				cin >> idx;
				deleteData(idx);
				break;
			case 'C':
				cin >> idx >> x;
				setData(idx, x);
				break;
			}
		}
		
		cout << "#" << t << " ";
		print(L);
		cout << "\n";
	}
}