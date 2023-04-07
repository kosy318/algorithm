#include <iostream>
#include <map>

using namespace std;

struct Node {
	int num;
	Node* front;
	Node* back;

	Node(int num = -1, Node* front = nullptr, Node* back = nullptr) : num(num), front(front), back(back) {}
};

int n; // ��Ʈ�� ����
int m; // ������ ����
map<int, Node*> node_info; // �� ������ ��ȣ�� ���� Node �ּҰ�
Node* heads[100001] = { nullptr, }; // �� ��Ʈ�� head ������ �������
Node* tails[100001] = { nullptr, }; // �� ��Ʈ�� tail ������ �������
int cnt[100001] = { 0, }; // �� ��Ʈ�� �ִ� ������ ��

/*
void enter() {
	cout << endl;
}

void print_heads() {
	cout << "heads ����" << endl;
	for (int i = 1; i <= n; i++) {
		if (heads[i] == nullptr) cout << "- ";
		else cout << heads[i]->num << " ";
	}
	cout << endl;
}

void print_tails() {
	cout << "tails ����" << endl;
	for (int i = 1; i <= n; i++) {
		if (tails[i] == nullptr) cout << "- ";
		else cout << tails[i]->num << " ";
	}
	cout << endl;
}

void print_all() {
	cout << "��Ʈ ��ü ����" << endl;
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
	cout << "��Ʈ ��ü ���� reverse" << endl;
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
	cout << "���� ����" << endl;
	for (int i = 1; i <= n; i++) {
		cout << cnt[i] << " ";
	}
	cout << endl;
}
*/

void make_factory() {
	cin >> n >> m;

	int num; // ��� ��Ʈ�� ������ ��������
	for (int i = 1; i <= m; i++) { // ���ǹ�ȣ 1���� ����
		cin >> num;// ���� ��Ʈ ��ȣ

		if (heads[num] == nullptr) { // �ش� ��Ʈ�� ���������
			heads[num] = new Node(i);
			tails[num] = heads[num];
		}
		else { // �ش� ��Ʈ�� ������� ����
			// ��Ʈ ���ʿ� �ִ� node�� front�� �߰�
			Node* new_node = new Node(i, tails[num]);

			// ���ʿ� �߰�
			tails[num]->back = new_node;
			tails[num] = new_node;
		}

		// ���� �Է�
		node_info[i] = tails[num];
		// ��Ʈ�� ���� ���� ����
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

	// src�� ������ �������� �ű�
	if (cnt[src] != 0) {
		// src��° ��Ʈ�� �ִ� ���ǵ��� dst �� �������� �ű�
		
		// dst head�� front�� src tail�� ����
		//////////////// Ʋ�� �κ� : nullptr�� ��츦 ���� ����
		if (heads[dst] != nullptr) {
			heads[dst]->front = tails[src];
		}
		else { // dst�� �ƹ��͵� ������
			///////////////////// Ʋ�� �κ� : tails ������ �����
			tails[dst] = tails[src];
		}

		// src tail�� back�� dst head�� ����
		tails[src]->back = heads[dst];

		// src head ������ dst head�� �ű�
		heads[dst] = heads[src];

		// src head�� tail ������ ����
		heads[src] = nullptr;
		tails[src] = nullptr;

		// dst ������ src ���� �߰�
		cnt[dst] += cnt[src];
		// src ���� 0���� �ʱ�ȭ
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

	// dst ��Ʈ�� �ִ� ������ ���� ���
	return cnt[dst];
}

int change_front() {
	int src, dst;
	cin >> src >> dst;

	// ������ �������� ������ �ű�⸸ �ϸ��
	if (cnt[src] == 0 && cnt[dst] != 0) { // dst�� src�� �ű�� ��Ȳ
		Node* dst_head = heads[dst];

		// ���ο� heads[src]�� dst_head�� ��
		heads[src] = dst_head;
		// ���ο� tails[src]�� dst_head�� ��
		tails[src] = dst_head;

		// dst_head�� back�� ���ο� heads[dst]�� ��
		heads[dst] = dst_head->back;

		// dst_head�� back�� nullptr�� ��; src ��Ʈ�� ����ֱ� ����
		dst_head->back = nullptr;
		// heads[dst]�� front�� nullptr�� ��; src ��Ʈ���� �Űܿ� ���� ���� ����
		//////////////// Ʋ�� �κ� : nullptr�� ��츦 ���� ����
		if (heads[dst] != nullptr) heads[dst]->front = nullptr;

		// cnt[dst]�� 1�� ������
		cnt[dst] -= 1;
		// cnt[src]�� 1�� ������
		cnt[src] += 1;
	}
	else if (cnt[dst] == 0 && cnt[src] != 0) {
		Node* src_head = heads[src];

		// ���ο� heads[dst]�� src_head�� ��
		heads[dst] = src_head;
		// ���ο� tails[dst]�� src_head�� ��
		tails[dst] = src_head;

		// src_head�� back�� ���ο� heads[src]�� ��
		heads[src] = src_head->back;

		// src_head�� back�� nullptr�� ��; dst ��Ʈ�� ����ֱ� ����
		src_head->back = nullptr;
		// heads[src]�� front�� nullptr�� ��; dst ��Ʈ���� �Űܿ� ���� ���� ����
		//////////////// Ʋ�� �κ� : nullptr�� ��츦 ���� ����
		if (heads[src] != nullptr) heads[src]->front = nullptr;

		// cnt[src]�� 1�� ������
		cnt[src] -= 1;
		// cnt[dst]�� 1�� ������
		cnt[dst] += 1;

	}
	else if(cnt[dst] != 0 && cnt[src] != 0) { // �� �� ���� ����
		Node* src_head = heads[src];
		Node* dst_head = heads[dst];

		Node* dst_head_back = dst_head->back;
		Node* src_head_back = src_head->back;

		// dst, src head�� back�� front�� ���� src, dst head�� ����Ŵ
		//////////////// Ʋ�� �κ� : nullptr�� ��츦 ���� ����
		if (dst_head_back != nullptr) dst_head_back->front = src_head;
		if (src_head_back != nullptr) src_head_back->front = dst_head;

		// dst, src head�� back�� ���� src, dst head�� back�� ����Ŵ
		src_head->back = dst_head_back;
		dst_head->back = src_head_back;

		// ���ο� heads[src]�� dst_head�� ��
		heads[src] = dst_head;
		// ���ο� heads[dst]�� src_head�� ��
		heads[dst] = src_head;

		//////////////////// Ʋ�� �κ� : tails ������ �����....
		if (cnt[src] == 1) tails[src] = heads[src];
		if (cnt[dst] == 1) tails[dst] = heads[dst];

		// ���� ��ȯ�߱� ������ ���� ��ȭ�� ����
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

int divide() { // �ִ� 100��!! ������ �ȴ�~
	int src, dst;

	cin >> src >> dst;

	if (cnt[src] > 1) { // 1���� Ŭ ���� �ű�
		int move_cnt = cnt[src] / 2;

		Node* dst_head = heads[dst]; // �� dst head
		Node* head = heads[src]; // ������ ������ �� ��
		Node* tail = head; // ������ ������ �� ��
		Node* new_head = tail->back; // ���Ӱ� src�� head�� �� ��

		for (int i = 1; i < move_cnt; i++) {
			tail = tail->back;
			new_head = tail->back;
		}
		
		// ���ο� src head ����
		heads[src] = new_head;
		// ���ο� src head�� front�� nullptr
		if(heads[src] != nullptr) heads[src]->front = nullptr;

		// ���ο� dst head ����
		heads[dst] = head;
		// ���� dst_head�� front�� ���� ���� ����Ʈ�� tail
		if (dst_head != nullptr) dst_head->front = tail;
		// ���� ���� ����Ʈ�� tail�� back�� ���� dst_head
		tail->back = dst_head;
		// ������ dst�� �ƹ��͵� ��������, tails�� ��������
		if (cnt[dst] == 0) tails[dst] = tail;
		
		// ���� ����
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

	int q; // ����� ��
	cin >> q;

	while (q--) {
		int order;
		cin >> order;

		switch (order) {
		case 100: // ���� ����
			make_factory();
			break;
		case 200: // ���� ��� �ű��
			cout << move_all() << "\n";
			break;
		case 300: // �� ���Ǹ� ��ü�ϱ�
			cout << change_front() << "\n";
			break;
		case 400: // ���� ������
			cout << divide() << "\n";
			break;
		case 500: // ���� ���� ���
			cout << get_gift_info() << "\n";
			break;
		case 600: // ��Ʈ ���� ���
			cout << get_belt_info() << "\n";
			break;
		}
	}
}