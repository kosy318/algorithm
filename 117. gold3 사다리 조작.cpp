#include <iostream>
#include <algorithm>

using namespace std;

int N, M, H;
int answer = -1;
bool ladder[31][11];

bool start_game() {
	bool possible = true;

	for (int j = 1; j <= N; j++) {
		int col = j;
		for (int i = 1; i <= H; i++) {
			if (ladder[i][col]) col += 1;
			else if (ladder[i][col-1]) col -= 1;
		}
		if (col != j) {
			possible = false;
			break;
		}
	}

	return possible;
}

void subset(int idx = N+1, int cnt = 0) {
	if (answer == 1) return;
	if (cnt >= 1) {
		if (answer != -1 && answer <= cnt) return;
		if (start_game()) {
			if(answer == -1) answer = cnt;
			else answer = min(answer, cnt);
		}
	}
	if (cnt == 3) return;

	int x = idx / N, y = idx % N;
	if (y == 0) y = 1;
	if (x > H || y > N) return;
	if (ladder[x][y] || (y-1>=1 && ladder[x][y-1]) || (y+1<=N && ladder[x][y+1])) {
		subset(N*x + y + 1, cnt);
	} else{
		ladder[x][y] = true;
		subset(N*x + y + 1, cnt + 1);
		ladder[x][y] = false;
		subset(N*x + y + 1, cnt);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M >> H;

	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		ladder[a][b] = true;
	}

	if (start_game()) cout << "0";
	else {
		subset();
		cout << answer;
	}
}