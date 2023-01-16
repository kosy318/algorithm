#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

// ��������Ʈ�� to �迭
// root : 0, root-left : 1, root-right : 2
// left : 1, left-left : 3, left-right : 4
// right: 2, right-left: 5, right-right: 6
// parent : N, parent-left : (2N+1), parent-right : (2N+2)
// child -> parent ���ϴ� �� : (index - 1)/2
// index -  1 ������ ¦���� left, Ȧ���� right

struct Node{
	queue<int> left, right; // ���� ����
	queue<int> work; // �ø� ����
};

void push_up(int i, int work, Node* tree) {
	if ((i - 1) % 2 == 0) { // ����
		tree[(i - 1) / 2].left.push(work);
	}
	else { // ������
		tree[(i - 1) / 2].right.push(work);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(false);
	
	// H: depth, K: ���ܿ� ����ϴ� ������ ����, R: ������ ����Ǵ� ��¥ ��
	int H, K, R;
	cin >> H >> K >> R;

	// depth: 1 -> ���� : 1, 2
	// depth: 2 -> ���� : 3, 4, 5, 6
	// depth: 3 -> ���� : 7, 8, 9, 10, 11, 12, 13, 14
	// depth: N -> ���� : 2^N -1 ... 2^(N+1)-2

	Node* tree = new Node[(int)pow(2, H + 1) - 1];
	for (int i = pow(2, H) - 1; i <= (pow(2, H + 1) - 2); i++) {
		int work;
		for (int j = 0; j < K; j++) {
			cin >> work;

			tree[i].work.push(work);
		}
	}

	/// TODO:: root�� ó���� ���� ��ȣ�� ��
	int res = 0;
	for(int i = 1; i<= R; i++){
		// ¦���� -> right, Ȧ���� -> left
		// root(index == 0)���� ���� �� res�� ���ϰ� ó��
		if (i % 2 == 0 && !tree[0].right.empty()) { // ¦����
			res += tree[0].right.front();
			tree[0].right.pop();
		}
		else if(!tree[0].left.empty()) { // Ȧ����
			res += tree[0].left.front();
			tree[0].left.pop();
		}

		// ���� ���� ó��
		// ¦���� -> right, Ȧ���� -> left
		for (int j = 1; j <= pow(2, H) - 2; j++) {
			if (i % 2 == 0) { // ¦����
				if (tree[j].right.empty()) continue;
				push_up(j, tree[j].right.front(), tree);
				tree[j].right.pop();
			}
			else { // Ȧ����
				if (tree[j].left.empty()) continue;
				push_up(j, tree[j].left.front(), tree);
				tree[j].left.pop();
			}
		}

		// ���� �ø�
		// ����
		for (int i = pow(2, H) - 1; i <= (pow(2, H + 1) - 2); i++) {
			if (tree[i].work.empty()) break; // ���ܿ� ���̻� ���� ������ �ߴ�
			push_up(i, tree[i].work.front(), tree);
			tree[i].work.pop();
		}
	}

	cout << res;
}