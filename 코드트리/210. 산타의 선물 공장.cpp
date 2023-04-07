#include <iostream>
#include <map>

using namespace std;

struct Node { // doubly linked list
	long long id, weight;
	int belt;
	Node* front = nullptr;
	Node* back = nullptr;

	Node(int belt, long long id) : belt(belt), id(id) {}
};

Node* heads[11] = { nullptr, };
Node* tails[11] = { nullptr, }; // belt는 1부터 시작
int belt[11]; // belt 정보; default는 belt[i] = i;인데 고장되서 옮겨질 경우를 대비
map<long long, Node*> gift_info;
int n; // 선물의 개수
int m; // 벨트의 개수

/*
void enter() {
	cout << endl;
}

void print_all() {
	cout << "head부터 차례로 출력" << endl;
	for (int i = 1; i <= m; i++) {
		Node* n = heads[i];
		cout << i << ": ";
		while (n != nullptr) {
			cout << n->id << ", " << n->weight;
			n = n->back;

			if (n != nullptr) cout << " -> ";
		}
		cout << endl;
	}
}

void print_all_reverse() {
	cout << "tail부터 차례로 출력" << endl;
	for (int i = 1; i <= m; i++) {
		Node* n = tails[i];
		cout << i << ": ";
		while (n != nullptr) {
			cout << n->id << ", " << n->weight;
			n = n->front;

			if (n != nullptr) cout << " <- ";
		}
		cout << endl;
	}
}
*/


// 100 : 공장 설립
void make_factory() {
	cin >> n >> m;

	// id 입력받기
	for (int i = 1; i <= m; i++) { // belt는 1번부터 시작
		belt[i] = i;
		for (int j = 0; j < n / m; j++) {
			long long id;
			cin >> id;
			Node* new_node = new Node(i, id); // 벨트 정보랑 id 함께 입력
			if (j == 0) { // 아무것도 안만들어져있는 상태
				// i번째 벨트의 head와 tail 둘 다 새로운 node가 차지함
				heads[i] = new_node;
				tails[i] = new_node;

				// gift_info 등록
				gift_info[id] = new_node;
			}
			else { // 적어도 하나 이상 존재
				// tail에 new_node 연결
				tails[i]->back = new_node;
				// new_node에 tail 연결
				new_node->front = tails[i];

				// tail을 new_node로 변경
				tails[i] = new_node;

				// gift_info 등록
				gift_info[id] = new_node;
			}
		}
	}

	// weight 입력받기
	for (int i = 1; i <= m; i++) { // belt는 1번부터 시작
		Node* node = heads[i];
		for (int j = 0; j < n / m; j++) {
			long long weight;
			cin >> weight;

			node->weight = weight;
			node = node->back;
		}
	}

	/*
	enter();
	print_all();
	print_all_reverse();
	*/
}

// 200 : 물건 하차
long long take_gifts() {
	long long total = 0;
	long long weight;
	cin >> weight;

	for (int i = 1; i <= m; i++) { // 모든 벨트를 돌면서.. belt는 1부터 시작
		if (heads[i] == nullptr) continue; // 없는 경우도 있지 않을까
		
		Node* head = heads[i];

		// heads[i]에서 맨 앞 물건을 제거하는 과정은 동일함..
		//////////////// 틀린 부분: 동일하지만 제거가 먼저 진행되면 안된다고.................
		////////////////  weight를 따로 기록해두자
		///////////////// 틀린 부분!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 동일하지 않아!!!!!!!!!!!!!!!!!!!!!!!
		if (heads[i]->weight <= weight) { // 하차 진행
			// total에 heads[i]의 weight를 추가함
			total += heads[i]->weight;

			// gift_info에서 제거해야함
			gift_info.erase(head->id);

			////////////////// 틀린 부분 : 제거는 나중에..........
			// heads[i]의 back이 heads[i]가 됨
			heads[i] = head->back;
			// heads[i]가 nullptr이 아니라면 새로운 heads[i]의 front는 nullptr이 됨
			if (heads[i] != nullptr) heads[i]->front = nullptr;
			////////////////// 틀린 부분 : 하나만 남은 경우도 고려
			else tails[i] = nullptr;
		}
		//////////////////// 틀린 부분 : 하나만 있는 경우엔 안해도 됨
		else if(tails[i]->id != head->id) { // 맨 뒤로 보냄
			// heads[i]의 back이 heads[i]가 됨
			heads[i] = head->back;
			// heads[i]가 nullptr이 아니라면 새로운 heads[i]의 front는 nullptr이 됨
			if (heads[i] != nullptr) heads[i]->front = nullptr;

			// tails[i]의 back에  head를 연결
			tails[i]->back = head;
			// head의 front에 tails[i]을 연결
			head->front = tails[i];

			// head의 back은 nullptr
			head->back = nullptr;

			// tails[i]에 head를 등록
			tails[i] = head;
		}
	}

	/*
	enter();
	print_all();
	print_all_reverse();
	*/

	// 하차된 상자 무게의 총 합 출력;
	return total;
}

// 300
long long remove_gift() {
	long long id;
	cin >> id;

	// 없으면 -1
	if (gift_info.find(id) == gift_info.end()) return -1;

	// 있으면 제거
	Node* gift = gift_info[id];
	// gift_info에서 erase
	gift_info.erase(id);

	int num = belt[gift->belt];
	while (num != belt[num])
		num = belt[num];

	// back이 존재하고 front 가 존재하면; 사이에 껴있다는 의미
	if (gift->back != nullptr && gift->front != nullptr) {
		// back의 front는 gift의 front로 바뀜
		gift->back->front = gift->front;
		// front의 back은 gift의 back으로 바뀜
		gift->front->back = gift->back;
	}
	// back이 존재하고 front가 존재하지 않으면; head라는 의미
	else if (gift->back != nullptr && gift->front == nullptr) {
		// back의 front는 nullptr로 바뀜
		gift->back->front = nullptr;
		// heads가 back으로 바뀜...... belt 정보 필요!!!!!!!!!
		heads[num] = gift->back;
	}
	// front는 존재하고 back이 존재하지 않으면
	else if (gift->front != nullptr && gift->back == nullptr) {
		// front의 back이 nullptr로 바뀜
		gift->front->back = nullptr;
		// tails가 front로 바뀜.......  belt 정보 필요!!!!!!!!!
		tails[num] = gift->front;
	}
	// front back 둘 다 존재 안함
	else if(gift->back == nullptr && gift->front == nullptr) {
		// 해당 belt의 heads, tails가 전부 nullptr로 바뀜
		heads[num] = nullptr;
		tails[num] = nullptr;
	}

	/*
	enter();
	print_all();
	print_all_reverse();
	*/

	return id;
}

int check_gift() {
	long long id;
	cin >> id;

	// 존재하지 않으면 -1 리턴
	if (gift_info.find(id) == gift_info.end()) return -1;

	// 존재하면
	Node* gift = gift_info[id];
	int num = belt[gift->belt];
	//////////////// 틀린 부분 : 옮긴 벨트도 옮겨졌을 가능성이 있음
	while (num != belt[num])
		num = belt[num];
	// front가 존재하는 경우
	if (gift->front != nullptr) {
		// tails의 back이 heads로 바뀜
		tails[num]->back = heads[num];
		// heads의 front가 tails[num]로 바뀜
		heads[num]->front = tails[num];
		// heads가 gift로 바뀜
		heads[num] = gift;
		// tails의 값이 front로 바뀜
		tails[num] = gift->front;
		// tails의 back이 nullptr로 바뀜
		tails[num]->back = nullptr;
		// gift의 front가 nullptr로 바뀜
		gift->front = nullptr;
	}
	
	// front가 존재하지 않는 경우 -> 아무런 일도 없음

	/*
	enter();
	print_all();
	print_all_reverse();
	*/

	return num;
}

// 500
int remove_belt() {
	int num;
	cin >> num;

	// 이미 망가져있으면 -1 리턴
	if (belt[num] != num) return -1;

	// 망가져있지 않으면
	int move = num + 1;
	// 벨트 정보 수정

	while (true) {
		if (move > m) move = 1; // belt개수를 넘어가면 1로 초기화

		// 멀쩡한 벨트를 찾음
		//////////// 틀린 부분 : .... == 로 해야하는데 =로 함.....
		if (belt[move] == move) {
			// 뒤에 이어붙임
			/////////////// 틀린 부분 : 옮길 짐이 없는 경우를 생각 안함
			// num에 하나라도 존재한다면
			if (tails[num] != nullptr) {
				// move에 하나라도 존재한다면
				if (tails[move] != nullptr) {
					// move tails의 back이 num heads가 됨
					tails[move]->back = heads[num];
					// num heads의 front가 move tails이 됨
					heads[num]->front = tails[move];
					// move tails가 num tails가 됨
					tails[move] = tails[num];
				}
				// move에 하나도 존재하지 않는다면
				else {
					// move heads가 num heads가 됨
					heads[move] = heads[num];
					// move tails가 num tails가 됨
					tails[move] = tails[num];
				}
			}
			belt[num] = move;
			break;
		}

		move += 1;
	}

	// 기존 벨트에서 전부 제거
	heads[num] = nullptr;
	tails[num] = nullptr;
	
	/*
	enter();
	print_all();
	print_all_reverse();
	*/

	return num;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int q;
	cin >> q;

	while (q--) {
		int order;
		cin >> order;

		switch (order) {
		case 100: // 공장 설립
			make_factory();
			break;
		case 200: // 물건 하차
			cout << take_gifts() << "\n";
			break;
		case 300: // 물건 제거
			cout << remove_gift() << "\n";
			break;
		case 400: // 물건 확인
			cout << check_gift() << "\n";
			break;
		case 500: // 벨트 고장
			cout << remove_belt() << "\n";
			break;
		}
	}
}