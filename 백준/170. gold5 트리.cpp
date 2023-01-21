#include <iostream>

using namespace std;

int N;
int* parents;
void delete_node(int num) {
	//cout << "delete node " << num << endl;
	parents[num] = -2;

	for (int i = 0; i < N; i++) {
		if (parents[i] == num) {
			delete_node(i);
		}
	}
}

int count_leaf() {
	int cnt = 0;
	/*for (int i : parents)
		cout << i << " ";
	cout << endl;*/

	for (int i = 0; i < N; i++) {
		if (parents[i] != -2) {
			bool leaf = true;
			for (int j = 0; j < N; j++) {
				if (parents[j] == i) { // i번째 노드는 리프노드가 아니다.
					leaf = false;
					break;
				}
			}
			if (leaf) {
				cnt += 1;
				//cout << i << "번째 노드는 리프노드!\n";
			}
		}
	}
	return cnt;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	parents = new int[N];
	for (int i = 0; i < N; i++) {
		cin >> parents[i];
	}

	int num;
	cin >> num;

	delete_node(num);

	cout << count_leaf();
}