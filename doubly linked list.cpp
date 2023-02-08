// doubly linked list
#include <iostream>

using namespace std;

struct NODE {
	int value;
	NODE* prev;
	NODE* next;
	NODE() {}
	NODE(int value, NODE* prev, NODE* next) : value(value), prev(prev), next(next) {}
}*head; // head node ��������

int cnt; // linked list node ����

void add(int x) { // �� �ڿ� �߰�
	NODE* cur = head;
	if (cnt == 0) { // ���� �ϳ��� ����
		head = new NODE(x, 0, 0); // head �ʱ�ȭ
		cur = head; // ���� ��ġ head�� �Է�
	}
	else { // �Ѱ� �̻��� �����Ͱ� �������
		cur->next = new NODE(x, cur, 0);
		cur = cur->next; // ���� ��ġ�� ���� ��ġ�� �Է�
	}

	cnt++; // linked list node ���� ����
}

void setData(int idx, int x) { // idx ��ġ�� ���� x�� �ٲ۴�.
	NODE* cur = head;
	for (int i = 0; i < idx; i++) { // idx ��ġ���� cur NODE�� �̵�
		cur = cur->next;
	}

	cur->value = x; // ���� x�� �ٲ�
}

void insertData(int idx, int x) { // idx�� �ε��� �׿� x�� ���� �߰�, �� x�� ���� ��ġ�� idx�� ��
	if (idx == 0) { // head�� �־����
		if (cnt != 0) { // ���� �����Ѵٸ�
			NODE* newNode = new NODE(x, 0, head); // newNode ���� Node�� head node�� ��
			head->prev = newNode;
			head = newNode;
		}
		else head = new NODE(x, 0, 0); // ���� ������ �Է� ���� head�� ��
	}
	else { // head�� �ƴ� ���� ����
		NODE* cur = head;
		while (--x) cur = cur->next; // ������� �� �� ���� �̵�
		NODE* newNode = new NODE(x, cur, cur->next); // cur node�� �� node�� cur node�� ���� node�� ���� node��
		if (cur->next) cur->next->prev = newNode; // cur�� �� ���� �ƴ϶�� ��������
		cur->next = newNode; // cur node�� ���� node�� newNode�� ��������
	}
	
	cnt++; // linked list node ���� ����
}

void deleteData(int idx, int x) {
	NODE* cur = head;
	while (x--) cur = cur->next; // ���� node�� �̵�
	NODE* prev = cur->prev, *next = cur->next;
	if (prev) prev->next = next; // ���� node�� head�� �ƴϾ �� node�� �����Ѵٸ� prev node�� next node�� ��������
	else head = next; // ���� node�� head���� �� node�� �������� �ʴ´ٸ� head�� �������ش�.

	if (next) next->prev = prev; // ���� node�� tail�� �ƴϾ ���� node�� �����Ѵٸ� next node�� prev node�� ��������

	cnt--; // linked list node ���� ����
}