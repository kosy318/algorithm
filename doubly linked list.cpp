// doubly linked list
#include <iostream>

using namespace std;

struct NODE {
	int value;
	NODE* prev;
	NODE* next;
	NODE() {}
	NODE(int value, NODE* prev, NODE* next) : value(value), prev(prev), next(next) {}
}*head; // head node 만들어놓음

int cnt; // linked list node 개수

void add(int x) { // 맨 뒤에 추가
	NODE* cur = head;
	if (cnt == 0) { // 아직 하나도 없음
		head = new NODE(x, 0, 0); // head 초기화
		cur = head; // 현재 위치 head로 입력
	}
	else { // 한개 이상의 데이터가 들어있음
		cur->next = new NODE(x, cur, 0);
		cur = cur->next; // 현재 위치를 다음 위치로 입력
	}

	cnt++; // linked list node 개수 증가
}

void setData(int idx, int x) { // idx 위치의 값을 x로 바꾼다.
	NODE* cur = head;
	for (int i = 0; i < idx; i++) { // idx 위치까지 cur NODE를 이동
		cur = cur->next;
	}

	cur->value = x; // 값을 x로 바꿈
}

void insertData(int idx, int x) { // idx번 인덱스 앖에 x의 값을 추가, 즉 x의 값의 위치가 idx가 됨
	if (idx == 0) { // head에 넣어야함
		if (cnt != 0) { // 값이 존재한다면
			NODE* newNode = new NODE(x, 0, head); // newNode 다음 Node는 head node가 됨
			head->prev = newNode;
			head = newNode;
		}
		else head = new NODE(x, 0, 0); // 값이 없으면 입력 값이 head가 됨
	}
	else { // head가 아닌 곳에 넣음
		NODE* cur = head;
		while (--x) cur = cur->next; // 집어넣을 곳 전 노드로 이동
		NODE* newNode = new NODE(x, cur, cur->next); // cur node가 전 node고 cur node의 다음 node가 다음 node임
		if (cur->next) cur->next->prev = newNode; // cur이 맨 끝이 아니라면 연결해줌
		cur->next = newNode; // cur node의 다음 node를 newNode와 연결해줌
	}
	
	cnt++; // linked list node 개수 증가
}

void deleteData(int idx, int x) {
	NODE* cur = head;
	while (x--) cur = cur->next; // 지울 node로 이동
	NODE* prev = cur->prev, *next = cur->next;
	if (prev) prev->next = next; // 지울 node가 head가 아니어서 전 node가 존재한다면 prev node와 next node를 연결해줌
	else head = next; // 지울 node가 head여서 전 node가 존재하지 않는다면 head를 갱신해준다.

	if (next) next->prev = prev; // 지울 node가 tail이 아니어서 다음 node가 존재한다면 next node와 prev node를 연결해줌

	cnt--; // linked list node 개수 감소
}