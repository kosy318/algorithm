#include<iostream>
#include<vector>

using namespace std;

int main() {
	// 오른쪽 아래 왼쪽 위 순서대로
	vector<int> dx = { 0, 1, 0, -1 };
	vector<int> dy = { 1, 0, -1, 0 };

	int tc;
	cin >> tc;
	for (int t = 0; t < tc; t++) {
		int N;
		cin >> N;
		vector<vector<int>> snails(N, vector<int>(N, 0));

		int x = 0, y = 0, dir = 0;
		for (int i = 1; i < N*N + 1; i++) {
			snails[x][y] = i;
			if (i == N * N) break;
			while (x + dx[dir] >= N || y + dy[dir] >= N || x + dx[dir] < 0 || y + dy[dir] < 0 || snails[x + dx[dir]][y + dy[dir]] != 0)
				dir = (dir + 1) % 4;

			x = x + dx[dir];
			y = y + dy[dir];
		}

		cout << "#" << t + 1 << endl;
		for (vector<int> vec : snails) {
			for (int snail : vec) {
				cout << snail << " ";
			}
			cout << endl;
		}
	}
}