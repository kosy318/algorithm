#include <iostream>
#include <list>

using namespace std;

int N; // ������ ����
int M; // �߰� Ƚ��
int L; // ����� �ε��� ��ȣ

struct NODE {
	int value;
	NODE* prev;
	NODE* next;
	NODE() {}
	NODE(int value, NODE* prev, NODE* next) : value(value), prev(prev), next(next) {}
}*head;

int cnt; // linked list node ����

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

void add(int x) { // �� �ڿ� �߰�
	NODE* cur = head;;
	if (cnt == 0) { // ���� �ϳ��� ����
		head = new NODE(x, 0, 0);
		cur = head;
	}
	else {
		for (int i = 1; i < cnt; i++) // �� �� node�� �̵�
			cur = cur->next;
		cur->next = new NODE(x, cur, 0);
		cur = cur->next; // ���� ��ġ�� ���� ��ġ�� �Է�
	}

	cnt++;
}

void insertData(int idx, int x) { // idx ��ġ�� x ����
	if (idx == 0) { // head�� �����ϴ� ���
		if (cnt != 0) { // ���� �����Ѵٸ�
			NODE* newNode = new NODE(x, 0, head); // �� ����� ���� ���� head
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
	NODE* prev = cur->prev, *next = cur->next; // ���� ����� ���� ���� node
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
		cnt = 0; // linked list node ���� �ʱ�ȭ

		cin >> N >> M >> L;

		input(); // ������ ���� �Է�

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