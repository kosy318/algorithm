#include <iostream>
#include <map>
#include <queue>
#include <cmath>

using namespace std;

int n; // ���� ũ��
int m; // ������ ��
int h; // ���� ��
int k; // �� ��

///////////////// 2���� �迭 �ʱ�ȭ ���
// �¿�θ� ���� -> �׻� �������� ���� ����
// ���Ϸθ� ���� -> �׻� �Ʒ����� ���� ����
int dx[3][2] = { {}, {0, 0}, {1, -1} };
int dy[3][2] = { {}, {1, -1}, {0, 0} };

struct Node {
	int x, y;
	int dir; // 1: �¿�, 2: ����
	int dir_detail = 0; // default: 0

	Node(int x = -1, int y = -1, int dir = 0) : x(x), y(y), dir(dir) {}
};

queue<int> runaway[99][99]; // 0���� �ʱ�ȭ
bool trees[99][99] = { false, }; // 0���� �ʱ�ȭ
map<int, Node> run_info;

/*
void print_runaway() {
	cout << "������ ��ġ" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (runaway[i][j].empty()) cout << "0 ";
			else cout << runaway[i][j].size() << " ";
		}
		cout << endl;
	}
}
*/

int it_dx[] = { -1, 0, 1, 0 }; // �� �� �� ��
int it_dy[] = { 0, 1, 0, -1 };

struct It {
	int x, y;
	int dir;

	It(int x, int y, int dir) : x(x), y(y), dir(dir) {}
};

queue<It> it;

/*
void print_snail(queue<It> que) {
	while (!que.empty()) {
		cout << que.front().x << ", " << que.front().y << " -> " << que.front().dir << endl;
		que.pop();
	}
}
*/

// ���� �����ϸ� �ٽ� �߽����� �̵�
// ������ Ʈ�� ��ġ������ �������ڸ��� ������ ƴ
// 0,0�� ���߾� ��ġ�� Ʋ����� ����!!!!!!!
void get_snail() {
	vector<vector<bool>> visited(n, vector<bool>(n, false));

	// ������ ó�� n/2, n/2�� ������(0,0 ���� �����Ѵٰ� �� ��)
	int x = n / 2;
	int y = n / 2;
	int dir = 0;

	visited[x][y] = true;
	it.push(It(x, y, dir));

	while (x != 0 || y != 0) {
		int nx = x + it_dx[dir];
		int ny = y + it_dy[dir];

		if (!visited[nx + it_dx[(dir + 1) % 4]][ny + it_dy[(dir + 1) % 4]]) {
			dir = (dir + 1) % 4;
		}

		x = nx;
		y = ny;
		visited[x][y] = true;

		it.push(It(x, y, dir));
	}

	it.back().dir = 2;

	// ���ƿ��� �κ�
	x = 0;
	y = 0;
	dir = 2;

	visited[x][y] = false;

	while (x != n / 2 || y != n / 2) {
		int nx = x + it_dx[dir];
		int ny = y + it_dy[dir];

		if ((nx < 0 || ny < 0 || nx >= n || ny >= n) || !visited[nx][ny]) {
			dir = (dir - 1) % 4;
			if (dir == -1) dir = 3;

			nx = x + it_dx[dir];
			ny = y + it_dy[dir];

			it.back().dir = dir;
		}

		x = nx;
		y = ny;
		visited[x][y] = false;

		if (x == n / 2 && y == n / 2) break;
		it.push(It(x, y, dir));
	}
	//print_snail(it);
}

// �׶��׶� distance�� �����������, ���������� ��ǥ���� �̸� �������
int dis_x[] = { -3, -2, -2, -2, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 3 };
int dis_y[] = { 0, -1, 0, 1, -2, -1, 0, 1, 2, -3, -2, -1, 0, 1, 2, 3, -2, -1, 0, 1, 2, -1, 0, 1, 0 };

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> h >> k;

	for (int i = 1; i <= m; i++) { // �������� ��ġ�� ����
		int x, y, d;
		cin >> x >> y >> d;

		runaway[x - 1][y - 1].push(i);
		run_info[i] = Node(x - 1, y - 1, d);
	}

	for (int i = 0; i < h; i++) {
		int x, y;
		cin >> x >> y;

		trees[x - 1][y - 1] = true;
	}

	//print_runaway();

	// ������ ������� ������ ��ǥ�� �־����
	get_snail();

	int score = 0;
	for (int turn = 1; turn <= k; turn++) {
		// �������� �Ÿ��� 3 ������ �����ڰ� ���ÿ� ����
		vector<int> moved;
		for (int d = 0; d < 25; d++) {
			int x = it.front().x + dis_x[d];
			int y = it.front().y + dis_y[d];

			if (x < 0 || y < 0 || x >= n || y >= n) continue;

			if (!runaway[x][y].empty()) { // �ش� ��ǥ�� �����ڰ� ���� -> ���������� ������
				while (!runaway[x][y].empty()) {
					int num = runaway[x][y].front(); runaway[x][y].pop();
					moved.push_back(num);

					// ���� �ٶ󺸰� �ִ� �������� 1ĭ ����
					int nx = x + dx[run_info[num].dir][run_info[num].dir_detail];
					int ny = y + dy[run_info[num].dir][run_info[num].dir_detail];

					// ���ڸ� �����
					if (nx < 0 || ny < 0 || nx >= n || ny >= n) {
						// �ݴ� �������� ���� Ʋ����
						run_info[num].dir_detail = 1 - run_info[num].dir_detail;

						nx = x + dx[run_info[num].dir][run_info[num].dir_detail];
						ny = y + dy[run_info[num].dir][run_info[num].dir_detail];

						// ������ ������ 1ĭ ������ ����
						////////////////////////////// Ʋ�� �κ� : ............ nx, ny�ε� nx, y������� �ߺ��� �Ф�
						if (nx != it.front().x || ny != it.front().y) {
							run_info[num].x = nx;
							run_info[num].y = ny;
						}
					}
					// ���ڸ� ����� ������
					else {
						// ������ ������ �������� x
						// ������ ������ �̵�(���� �־ ����)
						////////////////////////////// Ʋ�� �κ� : ............ nx, ny�ε� nx, y������� �ߺ��� �Ф�
						if (nx != it.front().x || ny != it.front().y) {
							run_info[num].x = nx;
							run_info[num].y = ny;
						}
					}
				}
			}
		}
		// ������ �ֵ� runaway�� ǥ��
		for (int i : moved) {
			Node info = run_info[i];

			runaway[info.x][info.y].push(i);
		}

		//print_runaway();

		// ������ ����(������ ������� 1ĭ ����)
		it.push(it.front());
		it.pop();

		// �þ� �� 3ĭ�� �ִ� ������ ����(���� ���� 3ĭ, ������ �����ִ� ������ ����)
		int x = it.front().x;
		int y = it.front().y;

		//cout << "���� ��ġ : " << x << ", " << y << endl;
		for (int i = 0; i < 3; i++) {
			// ���ڸ� ����� break;
			if (x < 0 || y < 0 || x >= n || y >= n) break;

			if (!trees[x][y]) { // ������ ���������� ������
				// �� �� * ���� �Ͽ��� ���� �������� ��
				score += turn * runaway[x][y].size();
				while (!runaway[x][y].empty()) {
					int num = runaway[x][y].front(); runaway[x][y].pop();

					//cout << num << "������ ����\n";

					// ���� �����ڴ� �����
					run_info.erase(num);
				}
			}

			x += it_dx[it.front().dir];
			y += it_dy[it.front().dir];
		}
	}

	cout << score;
}