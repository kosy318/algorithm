#include <iostream>
#include <queue>

using namespace std;

int N, K;
int load = 1;
int unload;
queue<int> que;

void load_robot(vector<int>& belt, vector<int>& robots) {
	if (belt[load] != 0) {
		robots[load] = 1;
		belt[load] -= 1;
		que.push(load);
	}
}

void move_robot(vector<int>& belt, vector<int>& robots) {
	int size = que.size();
	for (int i = 0; i < size; i++) {
		int cur = que.front();
		que.pop();
		if (cur == unload) {
			robots[cur] = 0;
			continue;
		}

		int next = cur + 1;
		if (next > 2 * N) next = 1;
		if (robots[next] == 0 && belt[next] != 0) {
			belt[next] -= 1;
			robots[cur] = 0;
			if (next != unload) {
				robots[next] = 1;
				que.push(next);
			}
		}
		else {
			que.push(cur);
		}
	}
}

void spin_belt() {
	load -= 1;
	unload -= 1;
	if (load == 0) load = 2*N;
	if (unload == 0) unload =  2*N;
}

bool check(vector<int>& belt) {
	int cnt = 0;
	for (int i = 1; i <= 2 * N; i++) {
		if (belt[i] == 0) cnt += 1;
	}
	if (cnt >= K) return true;
	return false;
}

int start(vector<int>& belt, vector<int>& robots) {
	int cnt = 0;
	while (!check(belt)) {
		cnt += 1;
		spin_belt();
		move_robot(belt, robots);
		load_robot(belt, robots);
	}
	return cnt;
}

int main() {
	cin >> N >> K;

	unload = N;

	vector<int> belt(2 * N + 1);
	vector<int> robots(2 * N + 1);
	for (int i = 1; i <= 2 * N; i++) {
		cin >> belt[i];
	}

	cout << start(belt, robots);
}