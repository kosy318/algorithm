#include <iostream>
#include <queue>

using namespace std;

int N, M; // ��, ��
vector<vector<int>> planet; // �༺ ���

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

int adventure() {
	int res = 0;

	queue<pair<int, int>> que; // ��ǥ ���� ����ִ� queue

	// ����ִ� ��ġ ã��
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (planet[i][j] == 0) {
				res += 1;
				que.push({ i, j });
				planet[i][j] = 2; // visited ��� planet�� 2�� ǥ���ؼ� ó��

				// bfs ����
				while (!que.empty()) {
					pair<int, int> cur = que.front(); que.pop();

					for (int d = 0; d < 4; d++) { // 4��Ž��
						int nx = cur.first + dx[d];
						int ny = cur.second + dy[d];

						if (nx < 0) {
							nx = N - 1;
						}
						if (ny < 0) {
							ny = M - 1;
						}
						if (nx >= N) {
							nx = 0;
						}
						if (ny >= M) {
							ny = 0;
						}

						if (planet[nx][ny] != 0) continue; // �̹� �湮�߰ų� ������� ���� ���̸� ������

						que.push({ nx, ny });
						planet[nx][ny] = 2; // visited ��� planet�� 2�� ǥ���ؼ� ó��
					}
				}

				// check
				/*cout << endl;
				for (auto vv : planet) {
					for (auto v : vv)
						cout << v << " ";
					cout << endl;
				}*/
			}
		}
	}

	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	planet = vector<vector<int>>(N, vector<int>(M)); // �༺ ũ�� �ʱ�ȭ

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> planet[i][j];
		}
	}

	cout << adventure();
}