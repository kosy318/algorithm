#include <iostream>
#include <map>

using namespace std;

struct Node {
	int num;
	Node* front;
	Node* back;

	Node(int num = -1, Node* front = nullptr, Node* back = nullptr) : num(num), front(front), back(back) {}
};

int n; // 벨트의 개수
int m; // 선물의 개수
map<int, Node*> node_info; // 각 물건의 번호에 따른 Node 주소값
Node* heads[100001] = { nullptr, }; // 각 벨트의 head 정보를 담고있음
Node* tails[100001] = { nullptr, }; // 각 벨트의 tail 정보를 담고있음
int cnt[100001] = { 0, }; // 각 벨트에 있는 물건의 수

/*
void enter() {
	cout << endl;
}

void print_heads() {
	cout << "heads 정보" << endl;
	for (int i = 1; i <= n; i++) {
		if (heads[i] == nullptr) cout << "- ";
		else cout << heads[i]->num << " ";
	}
	cout << endl;
}

void print_tails() {
	cout << "tails 정보" << endl;
	for (int i = 1; i <= n; i++) {
		if (tails[i] == nullptr) cout << "- ";
		else cout << tails[i]->num << " ";
	}
	cout << endl;
}

void print_all() {
	cout << "벨트 전체 정보" << endl;
	for (int i = 1; i <= n; i++) {
		cout << i << " : ";
		Node* head = heads[i];
		for (int j = 0; j < cnt[i]; j++) {
			cout << head->num;
			head = head->back;
			if(head != nullptr) cout << " -> ";
		}
		enter();
	}
}

void print_back() {
	cout << "벨트 전체 정보 reverse" << endl;
	for (int i = 1; i <= n; i++) {
		cout << i << " : ";
		Node* tail = tails[i];
		for (int j = 0; j < cnt[i]; j++) {
			cout << tail->num;
			tail = tail->front;
			if (tail != nullptr) cout << " <- ";
		}
		enter();
	}
}

void print_cnt() {
	cout << "개수 정보" << endl;
	for (int i = 1; i <= n; i++) {
		cout << cnt[i] << " ";
	}
	cout << endl;
}
*/

void make_factory() {
	cin >> n >> m;

	int num; // 몇번 벨트에 물건을 넣을건지
	for (int i = 1; i <= m; i++) { // 물건번호 1부터 시작
		cin >> num;// 넣을 벨트 번호

		if (heads[num] == nullptr) { // 해당 벨트가 비어있으면
			heads[num] = new Node(i);
			tails[num] = heads[num];
		}
		else { // 해당 벨트가 비어있지 않음
			// 벨트 뒤쪽에 있는 node를 front에 추가
			Node* new_node = new Node(i, tails[num]);

			// 뒤쪽에 추가
			tails[num]->back = new_node;
			tails[num] = new_node;
		}

		// 정보 입력
		node_info[i] = tails[num];
		// 벨트에 물건 개수 증가
		cnt[num] += 1;
	}

	/*
	enter();
	print_heads();
	print_tails();
	print_cnt();
	print_all();
	print_back();
	*/
}

int move_all() {
	int src, dst;
	cin >> src >> dst;

	// src에 물건이 있을때만 옮김
	if (cnt[src] != 0) {
		// src번째 벨트에 있는 물건들을 dst 맨 앞쪽으로 옮김
		
		// dst head의 front에 src tail을 연결
		//////////////// 틀린 부분 : nullptr인 경우를 생각 안함
		if (heads[dst] != nullptr) {
			heads[dst]->front = tails[src];
		}
		else { // dst에 아무것도 없으면
			///////////////////// 틀린 부분 : tails 세팅을 까먹음
			tails[dst] = tails[src];
		}

		// src tail의 back에 dst head를 연결
		tails[src]->back = heads[dst];

		// src head 정보를 dst head로 옮김
		heads[dst] = heads[src];

		// src head와 tail 정보를 없앰
		heads[src] = nullptr;
		tails[src] = nullptr;

		// dst 개수에 src 개수 추가
		cnt[dst] += cnt[src];
		// src 개수 0으로 초기화
		cnt[src] = 0;
	}

	/*
	enter();
	print_heads();
	print_tails();
	print_cnt();
	print_all();
	print_back();
	*/

	// dst 벨트에 있는 선물의 개수 출력
	return cnt[dst];
}

int change_front() {
	int src, dst;
	cin >> src >> dst;

	// 선물이 존재하지 않으면 옮기기만 하면됨
	if (cnt[src] == 0 && cnt[dst] != 0) { // dst만 src로 옮기는 상황
		Node* dst_head = heads[dst];

		// 새로운 heads[src]는 dst_head가 됨
		heads[src] = dst_head;
		// 새로운 tails[src]는 dst_head가 됨
		tails[src] = dst_head;

		// dst_head의 back이 새로운 heads[dst]가 됨
		heads[dst] = dst_head->back;

		// dst_head의 back은 nullptr이 됨; src 벨트가 비어있기 때문
		dst_head->back = nullptr;
		// heads[dst]의 front는 nullptr이 됨; src 벨트에서 옮겨온 것이 없기 때문
		//////////////// 틀린 부분 : nullptr인 경우를 생각 안함
		if (heads[dst] != nullptr) heads[dst]->front = nullptr;

		// cnt[dst]는 1이 빠지고
		cnt[dst] -= 1;
		// cnt[src]는 1이 더해짐
		cnt[src] += 1;
	}
	else if (cnt[dst] == 0 && cnt[src] != 0) {
		Node* src_head = heads[src];

		// 새로운 heads[dst]는 src_head가 됨
		heads[dst] = src_head;
		// 새로운 tails[dst]는 src_head가 됨
		tails[dst] = src_head;

		// src_head의 back이 새로운 heads[src]가 됨
		heads[src] = src_head->back;

		// src_head의 back은 nullptr이 됨; dst 벨트가 비어있기 때문
		src_head->back = nullptr;
		// heads[src]의 front는 nullptr이 됨; dst 벨트에서 옮겨온 것이 없기 때문
		//////////////// 틀린 부분 : nullptr인 경우를 생각 안함
		if (heads[src] != nullptr) heads[src]->front = nullptr;

		// cnt[src]는 1이 빠지고
		cnt[src] -= 1;
		// cnt[dst]는 1이 더해짐
		cnt[dst] += 1;

	}
	else if(cnt[dst] != 0 && cnt[src] != 0) { // 둘 다 선물 존재
		Node* src_head = heads[src];
		Node* dst_head = heads[dst];

		Node* dst_head_back = dst_head->back;
		Node* src_head_back = src_head->back;

		// dst, src head의 back의 front는 각각 src, dst head를 가리킴
		//////////////// 틀린 부분 : nullptr인 경우를 생각 안함
		if (dst_head_back != nullptr) dst_head_back->front = src_head;
		if (src_head_back != nullptr) src_head_back->front = dst_head;

		// dst, src head의 back은 각각 src, dst head의 back을 가리킴
		src_head->back = dst_head_back;
		dst_head->back = src_head_back;

		// 새로운 heads[src]는 dst_head가 됨
		heads[src] = dst_head;
		// 새로운 heads[dst]는 src_head가 됨
		heads[dst] = src_head;

		//////////////////// 틀린 부분 : tails 세팅을 까먹음....
		if (cnt[src] == 1) tails[src] = heads[src];
		if (cnt[dst] == 1) tails[dst] = heads[dst];

		// 서로 교환했기 때문에 개수 변화는 없음
	}

	/*
	enter();
	print_heads();
	print_tails();
	print_cnt();
	print_all();
	print_back();
	*/

	return cnt[dst];
}

int divide() { // 최대 100번!! 느려도 된다~
	int src, dst;

	cin >> src >> dst;

	if (cnt[src] > 1) { // 1보다 클 때만 옮김
		int move_cnt = cnt[src] / 2;

		Node* dst_head = heads[dst]; // 전 dst head
		Node* head = heads[src]; // 움직일 물건의 맨 앞
		Node* tail = head; // 움직일 물건의 맨 뒤
		Node* new_head = tail->back; // 새롭게 src의 head가 될 애

		for (int i = 1; i < move_cnt; i++) {
			tail = tail->back;
			new_head = tail->back;
		}
		
		// 새로운 src head 설정
		heads[src] = new_head;
		// 새로운 src head의 front는 nullptr
		if(heads[src] != nullptr) heads[src]->front = nullptr;

		// 새로운 dst head 설정
		heads[dst] = head;
		// 기존 dst_head의 front가 새로 들어온 리스트의 tail
		if (dst_head != nullptr) dst_head->front = tail;
		// 새로 들어온 리스트의 tail의 back이 기존 dst_head
		tail->back = dst_head;
		// 기존에 dst에 아무것도 없었으면, tails도 설정해줌
		if (cnt[dst] == 0) tails[dst] = tail;
		
		// 개수 설정
		cnt[src] -= move_cnt;
		cnt[dst] += move_cnt;
	}

	/*
	enter();
	print_heads();
	print_tails();
	print_cnt();
	print_all();
	print_back();
	*/

	return cnt[dst];
}

int get_gift_info() {
	int num;

	cin >> num;

	Node* gift = node_info[num];

	int front = -1;
	int back = -1;

	if (gift->front != nullptr) front = gift->front->num;
	if (gift->back != nullptr) back = gift->back->num;

	return front + 2 * back;
}

int get_belt_info() {
	int num;

	cin >> num;

	int head = -1;
	int tail = -1;
	int cnt_val = cnt[num];

	if (cnt_val != 0) {
		head = heads[num]->num;
		tail = tails[num]->num;
	}

	return head + 2 * tail + 3 * cnt_val;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int q; // 명령의 수
	cin >> q;

	while (q--) {
		int order;
		cin >> order;

		switch (order) {
		case 100: // 공장 설립
			make_factory();
			break;
		case 200: // 물건 모두 옮기기
			cout << move_all() << "\n";
			break;
		case 300: // 앞 물건만 교체하기
			cout << change_front() << "\n";
			break;
		case 400: // 물건 나누기
			cout << divide() << "\n";
			break;
		case 500: // 선물 정보 얻기
			cout << get_gift_info() << "\n";
			break;
		case 600: // 벨트 정보 얻기
			cout << get_belt_info() << "\n";
			break;
		}
	}
}