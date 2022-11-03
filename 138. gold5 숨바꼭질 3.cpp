#include <iostream>
#include <queue>

using namespace std;

int main() {
	int N, K;

	cin >> N >> K;

	bool visited[100001] = { false, };
	queue<pair<int, int>> que;
	que.push({ N, 0 });
	visited[N] = true;

	while (!que.empty()) {
		pair<int, int> cur = que.front();
		que.pop();
		if (cur.first == K) {
			cout << cur.second;
			break;
		}

		if (cur.first != 0 && cur.first * 2 <= 100000 && !visited[cur.first * 2]) {
			que.push({ cur.first * 2, cur.second });
			visited[cur.first * 2] = true;
		}
		if (cur.first - 1 >= 0 && !visited[cur.first - 1]) {

			que.push({ cur.first - 1, cur.second + 1 });
			visited[cur.first - 1] = true;
		}
		if (cur.first + 1 <= 100000 && !visited[cur.first + 1]) {
			que.push({ cur.first + 1, cur.second + 1 });
			visited[cur.first + 1] = true;
		}
	}
}