#include <iostream>
#include <map>
#include <queue>
#include <cmath>

using namespace std;

int n; // 격자 크기
int m; // 도망자 수
int h; // 나무 수
int k; // 턴 수

///////////////// 2차원 배열 초기화 방법
// 좌우로만 움직 -> 항상 오른쪽을 보고 시작
// 상하로만 움직 -> 항상 아래쪽을 보고 시작
int dx[3][2] = { {}, {0, 0}, {1, -1} };
int dy[3][2] = { {}, {1, -1}, {0, 0} };

struct Node {
	int x, y;
	int dir; // 1: 좌우, 2: 상하
	int dir_detail = 0; // default: 0

	Node(int x = -1, int y = -1, int dir = 0) : x(x), y(y), dir(dir) {}
};

queue<int> runaway[99][99]; // 0으로 초기화
bool trees[99][99] = { false, }; // 0으로 초기화
map<int, Node> run_info;

/*
void print_runaway() {
	cout << "도망자 위치" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (runaway[i][j].empty()) cout << "0 ";
			else cout << runaway[i][j].size() << " ";
		}
		cout << endl;
	}
}
*/

int it_dx[] = { -1, 0, 1, 0 }; // 상 우 하 좌
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

// 끝에 도달하면 다시 중심으로 이동
// 방향을 트는 위치에서는 도착하자마자 방향을 틈
// 0,0과 정중앙 위치도 틀어야함 주의!!!!!!!
void get_snail() {
	vector<vector<bool>> visited(n, vector<bool>(n, false));

	// 술래는 처음 n/2, n/2에 서있음(0,0 부터 시작한다고 할 때)
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

	// 돌아오는 부분
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

// 그때그때 distance를 계산하지말고, 움직여야할 좌표들을 미리 적어두자
int dis_x[] = { -3, -2, -2, -2, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 3 };
int dis_y[] = { 0, -1, 0, 1, -2, -1, 0, 1, 2, -3, -2, -1, 0, 1, 2, 3, -2, -1, 0, 1, 2, -1, 0, 1, 0 };

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> h >> k;

	for (int i = 1; i <= m; i++) { // 도망자의 위치와 방향
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

	// 달팽이 모양으로 움직일 좌표를 넣어두자
	get_snail();

	int score = 0;
	for (int turn = 1; turn <= k; turn++) {
		// 술래와의 거리가 3 이하인 도망자가 동시에 움직
		vector<int> moved;
		for (int d = 0; d < 25; d++) {
			int x = it.front().x + dis_x[d];
			int y = it.front().y + dis_y[d];

			if (x < 0 || y < 0 || x >= n || y >= n) continue;

			if (!runaway[x][y].empty()) { // 해당 좌표에 도망자가 있음 -> 움직여야할 도망자
				while (!runaway[x][y].empty()) {
					int num = runaway[x][y].front(); runaway[x][y].pop();
					moved.push_back(num);

					// 현재 바라보고 있는 방향으로 1칸 움직
					int nx = x + dx[run_info[num].dir][run_info[num].dir_detail];
					int ny = y + dy[run_info[num].dir][run_info[num].dir_detail];

					// 격자를 벗어나면
					if (nx < 0 || ny < 0 || nx >= n || ny >= n) {
						// 반대 방향으로 몸을 틀어줌
						run_info[num].dir_detail = 1 - run_info[num].dir_detail;

						nx = x + dx[run_info[num].dir][run_info[num].dir_detail];
						ny = y + dy[run_info[num].dir][run_info[num].dir_detail];

						// 술래가 없으면 1칸 앞으로 움직
						////////////////////////////// 틀린 부분 : ............ nx, ny인데 nx, y라고했음 잘보기 ㅠㅠ
						if (nx != it.front().x || ny != it.front().y) {
							run_info[num].x = nx;
							run_info[num].y = ny;
						}
					}
					// 격자를 벗어나지 않으면
					else {
						// 술래가 있으면 움직이지 x
						// 술래가 없으면 이동(나무 있어도 괜찮)
						////////////////////////////// 틀린 부분 : ............ nx, ny인데 nx, y라고했음 잘보기 ㅠㅠ
						if (nx != it.front().x || ny != it.front().y) {
							run_info[num].x = nx;
							run_info[num].y = ny;
						}
					}
				}
			}
		}
		// 움직인 애들 runaway에 표시
		for (int i : moved) {
			Node info = run_info[i];

			runaway[info.x][info.y].push(i);
		}

		//print_runaway();

		// 술래가 움직(달팽이 모양으로 1칸 움직)
		it.push(it.front());
		it.pop();

		// 시야 내 3칸에 있는 도망자 잡음(술래 포함 3칸, 나무랑 같이있는 도망자 제외)
		int x = it.front().x;
		int y = it.front().y;

		//cout << "술래 위치 : " << x << ", " << y << endl;
		for (int i = 0; i < 3; i++) {
			// 격자를 벗어나면 break;
			if (x < 0 || y < 0 || x >= n || y >= n) break;

			if (!trees[x][y]) { // 나무에 가려져있지 않으면
				// 턴 수 * 현재 턴에서 잡힌 도망자의 수
				score += turn * runaway[x][y].size();
				while (!runaway[x][y].empty()) {
					int num = runaway[x][y].front(); runaway[x][y].pop();

					//cout << num << "도망자 잡힘\n";

					// 잡힌 도망자는 사라짐
					run_info.erase(num);
				}
			}

			x += it_dx[it.front().dir];
			y += it_dy[it.front().dir];
		}
	}

	cout << score;
}