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
Node* tails[11] = { nullptr, }; // belt�� 1���� ����
int belt[11]; // belt ����; default�� belt[i] = i;�ε� ����Ǽ� �Ű��� ��츦 ���
map<long long, Node*> gift_info;
int n; // ������ ����
int m; // ��Ʈ�� ����

/*
void enter() {
	cout << endl;
}

void print_all() {
	cout << "head���� ���ʷ� ���" << endl;
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
	cout << "tail���� ���ʷ� ���" << endl;
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


// 100 : ���� ����
void make_factory() {
	cin >> n >> m;

	// id �Է¹ޱ�
	for (int i = 1; i <= m; i++) { // belt�� 1������ ����
		belt[i] = i;
		for (int j = 0; j < n / m; j++) {
			long long id;
			cin >> id;
			Node* new_node = new Node(i, id); // ��Ʈ ������ id �Բ� �Է�
			if (j == 0) { // �ƹ��͵� �ȸ�������ִ� ����
				// i��° ��Ʈ�� head�� tail �� �� ���ο� node�� ������
				heads[i] = new_node;
				tails[i] = new_node;

				// gift_info ���
				gift_info[id] = new_node;
			}
			else { // ��� �ϳ� �̻� ����
				// tail�� new_node ����
				tails[i]->back = new_node;
				// new_node�� tail ����
				new_node->front = tails[i];

				// tail�� new_node�� ����
				tails[i] = new_node;

				// gift_info ���
				gift_info[id] = new_node;
			}
		}
	}

	// weight �Է¹ޱ�
	for (int i = 1; i <= m; i++) { // belt�� 1������ ����
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

// 200 : ���� ����
long long take_gifts() {
	long long total = 0;
	long long weight;
	cin >> weight;

	for (int i = 1; i <= m; i++) { // ��� ��Ʈ�� ���鼭.. belt�� 1���� ����
		if (heads[i] == nullptr) continue; // ���� ��쵵 ���� ������
		
		Node* head = heads[i];

		// heads[i]���� �� �� ������ �����ϴ� ������ ������..
		//////////////// Ʋ�� �κ�: ���������� ���Ű� ���� ����Ǹ� �ȵȴٰ�.................
		////////////////  weight�� ���� ����ص���
		///////////////// Ʋ�� �κ�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! �������� �ʾ�!!!!!!!!!!!!!!!!!!!!!!!
		if (heads[i]->weight <= weight) { // ���� ����
			// total�� heads[i]�� weight�� �߰���
			total += heads[i]->weight;

			// gift_info���� �����ؾ���
			gift_info.erase(head->id);

			////////////////// Ʋ�� �κ� : ���Ŵ� ���߿�..........
			// heads[i]�� back�� heads[i]�� ��
			heads[i] = head->back;
			// heads[i]�� nullptr�� �ƴ϶�� ���ο� heads[i]�� front�� nullptr�� ��
			if (heads[i] != nullptr) heads[i]->front = nullptr;
			////////////////// Ʋ�� �κ� : �ϳ��� ���� ��쵵 ���
			else tails[i] = nullptr;
		}
		//////////////////// Ʋ�� �κ� : �ϳ��� �ִ� ��쿣 ���ص� ��
		else if(tails[i]->id != head->id) { // �� �ڷ� ����
			// heads[i]�� back�� heads[i]�� ��
			heads[i] = head->back;
			// heads[i]�� nullptr�� �ƴ϶�� ���ο� heads[i]�� front�� nullptr�� ��
			if (heads[i] != nullptr) heads[i]->front = nullptr;

			// tails[i]�� back��  head�� ����
			tails[i]->back = head;
			// head�� front�� tails[i]�� ����
			head->front = tails[i];

			// head�� back�� nullptr
			head->back = nullptr;

			// tails[i]�� head�� ���
			tails[i] = head;
		}
	}

	/*
	enter();
	print_all();
	print_all_reverse();
	*/

	// ������ ���� ������ �� �� ���;
	return total;
}

// 300
long long remove_gift() {
	long long id;
	cin >> id;

	// ������ -1
	if (gift_info.find(id) == gift_info.end()) return -1;

	// ������ ����
	Node* gift = gift_info[id];
	// gift_info���� erase
	gift_info.erase(id);

	int num = belt[gift->belt];
	while (num != belt[num])
		num = belt[num];

	// back�� �����ϰ� front �� �����ϸ�; ���̿� ���ִٴ� �ǹ�
	if (gift->back != nullptr && gift->front != nullptr) {
		// back�� front�� gift�� front�� �ٲ�
		gift->back->front = gift->front;
		// front�� back�� gift�� back���� �ٲ�
		gift->front->back = gift->back;
	}
	// back�� �����ϰ� front�� �������� ������; head��� �ǹ�
	else if (gift->back != nullptr && gift->front == nullptr) {
		// back�� front�� nullptr�� �ٲ�
		gift->back->front = nullptr;
		// heads�� back���� �ٲ�...... belt ���� �ʿ�!!!!!!!!!
		heads[num] = gift->back;
	}
	// front�� �����ϰ� back�� �������� ������
	else if (gift->front != nullptr && gift->back == nullptr) {
		// front�� back�� nullptr�� �ٲ�
		gift->front->back = nullptr;
		// tails�� front�� �ٲ�.......  belt ���� �ʿ�!!!!!!!!!
		tails[num] = gift->front;
	}
	// front back �� �� ���� ����
	else if(gift->back == nullptr && gift->front == nullptr) {
		// �ش� belt�� heads, tails�� ���� nullptr�� �ٲ�
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

	// �������� ������ -1 ����
	if (gift_info.find(id) == gift_info.end()) return -1;

	// �����ϸ�
	Node* gift = gift_info[id];
	int num = belt[gift->belt];
	//////////////// Ʋ�� �κ� : �ű� ��Ʈ�� �Ű����� ���ɼ��� ����
	while (num != belt[num])
		num = belt[num];
	// front�� �����ϴ� ���
	if (gift->front != nullptr) {
		// tails�� back�� heads�� �ٲ�
		tails[num]->back = heads[num];
		// heads�� front�� tails[num]�� �ٲ�
		heads[num]->front = tails[num];
		// heads�� gift�� �ٲ�
		heads[num] = gift;
		// tails�� ���� front�� �ٲ�
		tails[num] = gift->front;
		// tails�� back�� nullptr�� �ٲ�
		tails[num]->back = nullptr;
		// gift�� front�� nullptr�� �ٲ�
		gift->front = nullptr;
	}
	
	// front�� �������� �ʴ� ��� -> �ƹ��� �ϵ� ����

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

	// �̹� ������������ -1 ����
	if (belt[num] != num) return -1;

	// ���������� ������
	int move = num + 1;
	// ��Ʈ ���� ����

	while (true) {
		if (move > m) move = 1; // belt������ �Ѿ�� 1�� �ʱ�ȭ

		// ������ ��Ʈ�� ã��
		//////////// Ʋ�� �κ� : .... == �� �ؾ��ϴµ� =�� ��.....
		if (belt[move] == move) {
			// �ڿ� �̾����
			/////////////// Ʋ�� �κ� : �ű� ���� ���� ��츦 ���� ����
			// num�� �ϳ��� �����Ѵٸ�
			if (tails[num] != nullptr) {
				// move�� �ϳ��� �����Ѵٸ�
				if (tails[move] != nullptr) {
					// move tails�� back�� num heads�� ��
					tails[move]->back = heads[num];
					// num heads�� front�� move tails�� ��
					heads[num]->front = tails[move];
					// move tails�� num tails�� ��
					tails[move] = tails[num];
				}
				// move�� �ϳ��� �������� �ʴ´ٸ�
				else {
					// move heads�� num heads�� ��
					heads[move] = heads[num];
					// move tails�� num tails�� ��
					tails[move] = tails[num];
				}
			}
			belt[num] = move;
			break;
		}

		move += 1;
	}

	// ���� ��Ʈ���� ���� ����
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
		case 100: // ���� ����
			make_factory();
			break;
		case 200: // ���� ����
			cout << take_gifts() << "\n";
			break;
		case 300: // ���� ����
			cout << remove_gift() << "\n";
			break;
		case 400: // ���� Ȯ��
			cout << check_gift() << "\n";
			break;
		case 500: // ��Ʈ ����
			cout << remove_belt() << "\n";
			break;
		}
	}
}