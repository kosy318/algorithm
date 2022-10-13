#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;

struct Fish {
	int x, y;
	int dir;

	Fish(int x, int y, int dir) : x{ x }, y{ y }, dir{ dir }{}

	bool operator == (const Fish& f) const {
		return x == f.x && y == f.y && dir == f.dir;
	}
	
	friend hash<Fish>;
};

// struct�� map�� key�� ����ϱ� ���� �ʿ��� hash �Լ�
namespace std {
	template <>
	struct hash<Fish> {
		size_t operator()(const Fish& f) const {
			return f.x*100 + f.y*10 + f.dir;
		}
	};
}

// �� �ִ� ĭ, ������� ������ �ִ� ĭ �̵� �Ұ�
int dx[] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
int dy[] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };

// ��� �����̴� ���, ���� 3�� ������!!!! ���� �ƴ� ����
// �� �� �� ��
// �� �������� ���� �� �ƴ�!!!
int sx[] = {0, -1, 0, 1, 0 };
int sy[] = {0, 0, -1, 0, 1 };

vector<vector<vector<int>>> board(5, vector<vector<int>>(5, vector<int>(9))); // 0���� scent, 1~8�� ����� ����
unordered_map<Fish, int> fishes;
int fish_num;
int shark_x, shark_y;

int max_dir = 999;
int max_ate = -1;

void copy_fish(unordered_map<Fish, int>& origin) {
	for (auto f : origin) {
		fishes[f.first] += f.second;
		board[f.first.x][f.first.y][f.first.dir] += f.second;
	}
}

vector<vector<int>> visited(5, vector<int>(5));
void choose_dir(int x = shark_x, int y = shark_y, int cnt = 0, int total = 0, int dir = 0) {
	if (cnt == 3) {
		if (max_ate < total) {
			max_ate = total;
			max_dir = dir;
		}
		return;
	}

	for (int d = 1; d <= 4; d++) {
		int nx = x + sx[d];
		int ny = y + sy[d];

		
		if (nx <= 0 || ny <= 0 || nx > 4 || ny > 4) continue;
		int temp = 0;

		if(visited[nx][ny] == 0)
			for (int i = 1; i <= 8; i++) {
				temp += board[nx][ny][i];
			}

		visited[nx][ny] += 1;
		choose_dir(nx, ny, cnt + 1, total + temp, dir*10 + d);
		visited[nx][ny] -= 1;
	}
}

void shark_moves() {
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			if (board[i][j][0] != 0) board[i][j][0] -= 1;
		}
	}

	max_ate = -1;
	max_dir = 999;
	choose_dir();

	fish_num -= max_ate;
	for (int i = 2; i >= 0; i--) {
		int div = pow(10, i);
		int ndir = max_dir / div;
		// cout << ndir << endl;
		shark_x += sx[ndir];
		shark_y += sy[ndir];

		max_dir = max_dir % div;

		for (int j = 1; j <= 8; j++) {
			if(board[shark_x][shark_y][j] != 0) board[shark_x][shark_y][0] = 2;
			board[shark_x][shark_y][j] = 0;

			fishes.erase(Fish(shark_x, shark_y, j));
		}
	}
}

void fish_moves() {
	vector<vector<vector<int>>> new_board(5, vector<vector<int>>(5, vector<int>(9))); // 0���� scent, 1~8�� ����� ����

	unordered_map<Fish, int> new_fishes;
	for (auto f : fishes) {
		int x = f.first.x;
		int y = f.first.y;
		int dir = f.first.dir;
		int cnt = f.second;


		bool moved = false;
		for (int d = 1; d <= 8; d++) {
			if (dir <= 0) dir = 8;
			else if (dir > 8) dir = 1;

			int nx = x + dx[dir];
			int ny = y + dy[dir];

			if (nx <= 0 || ny <= 0 || nx > 4 || ny > 4 || (nx == shark_x && ny == shark_y) || board[nx][ny][0] != 0) {
				dir -= 1;
				continue;
			}
			moved = true;

			new_board[nx][ny][dir] += cnt;
			new_fishes[Fish(nx, ny, dir)] += cnt;
			break;
		}
		if (!moved) {
			new_fishes[Fish(x, y, f.first.dir)] += cnt;
			new_board[x][y][f.first.dir] += cnt;
		}
	}
	fishes = unordered_map<Fish, int>(new_fishes);

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			new_board[i][j][0] = board[i][j][0];
		}
	}
	board = new_board;
}

void practice(int S, vector<vector<vector<int>>>& board) {
	for (int s = 0; s < S; s++) {
		unordered_map<Fish, int> origin(fishes);
		fish_num *= 2; // ������ 2�� �ɰŰ� �״°��� 2�� ��Ű�°Ŷ� ��� ����
		fish_moves();

		shark_moves();
		copy_fish(origin); // �� ���� ���� �ֵ� �����(�� ���� ���� �ֹ� ����) -> �� board�� �����ؼ� �������
	}
}

// 1, 1���� ����!!
int main() {
	int S;
	cin >> fish_num >> S;

	int fx, fy, dir;
	for (int i = 0; i < fish_num; i++) {
		cin >> fx >> fy >> dir;
		board[fx][fy][dir] += 1;
		fishes[Fish(fx, fy, dir)] += 1;
	}


	cin >> shark_x >> shark_y;

	practice(S, board);

	cout << fish_num;
}