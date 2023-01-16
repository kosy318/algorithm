#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

// 완전이진트리 to 배열
// root : 0, root-left : 1, root-right : 2
// left : 1, left-left : 3, left-right : 4
// right: 2, right-left: 5, right-right: 6
// parent : N, parent-left : (2N+1), parent-right : (2N+2)
// child -> parent 구하는 법 : (index - 1)/2
// index -  1 했을때 짝수면 left, 홀수면 right

struct Node{
	queue<int> left, right; // 받은 업무
	queue<int> work; // 올릴 업무
};

void push_up(int i, int work, Node* tree) {
	if ((i - 1) % 2 == 0) { // 왼쪽
		tree[(i - 1) / 2].left.push(work);
	}
	else { // 오른쪽
		tree[(i - 1) / 2].right.push(work);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(false);
	
	// H: depth, K: 말단에 대기하는 업무의 개수, R: 업무가 진행되는 날짜 수
	int H, K, R;
	cin >> H >> K >> R;

	// depth: 1 -> 말단 : 1, 2
	// depth: 2 -> 말단 : 3, 4, 5, 6
	// depth: 3 -> 말단 : 7, 8, 9, 10, 11, 12, 13, 14
	// depth: N -> 말단 : 2^N -1 ... 2^(N+1)-2

	Node* tree = new Node[(int)pow(2, H + 1) - 1];
	for (int i = pow(2, H) - 1; i <= (pow(2, H + 1) - 2); i++) {
		int work;
		for (int j = 0; j < K; j++) {
			cin >> work;

			tree[i].work.push(work);
		}
	}

	/// TODO:: root가 처리한 업무 번호의 합
	int res = 0;
	for(int i = 1; i<= R; i++){
		// 짝수날 -> right, 홀수날 -> left
		// root(index == 0)에서 전날 일 res에 더하고 처리
		if (i % 2 == 0 && !tree[0].right.empty()) { // 짝수날
			res += tree[0].right.front();
			tree[0].right.pop();
		}
		else if(!tree[0].left.empty()) { // 홀수날
			res += tree[0].left.front();
			tree[0].left.pop();
		}

		// 받은 업무 처리
		// 짝수날 -> right, 홀수날 -> left
		for (int j = 1; j <= pow(2, H) - 2; j++) {
			if (i % 2 == 0) { // 짝수날
				if (tree[j].right.empty()) continue;
				push_up(j, tree[j].right.front(), tree);
				tree[j].right.pop();
			}
			else { // 홀수날
				if (tree[j].left.empty()) continue;
				push_up(j, tree[j].left.front(), tree);
				tree[j].left.pop();
			}
		}

		// 업무 올림
		// 말단
		for (int i = pow(2, H) - 1; i <= (pow(2, H + 1) - 2); i++) {
			if (tree[i].work.empty()) break; // 말단에 더이상 일이 없으면 중단
			push_up(i, tree[i].work.front(), tree);
			tree[i].work.pop();
		}
	}

	cout << res;
}