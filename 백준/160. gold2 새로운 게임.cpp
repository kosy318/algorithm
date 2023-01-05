#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<map>

using namespace std;

struct Node {
	int num;
	int x, y;
	int dir;

	Node(int num, int x, int y, int dir) :num{ num }, x{ x }, y{ y }, dir{ dir }{};
};

int N; // ü���� ũ��
int K; // ����ϴ� ���� ����
int color[12][12]; // ü����; 0: ���, 1: ������, 2:�Ķ���
int board[12][12]; // ���� �Ʒ��� ���� ü������ ��ȣ ǥ��
map<int, vector<Node>> pieces; // ü����

int dx[] = { 0, 0, 0, -1, 1 };
int dy[] = { 0, 1, -1, 0, 0 };

void print_board() {
	cout << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

int move() {
	int turn = 0;

	while (turn <= 1000) {
		set<int> erase;
		turn += 1;
		// 1������ K�� ������ ������� �̵�(���� �÷��� �ִ� ���� �Բ� �̵�, ���� �Ʒ��� �ִ� ���� �̵� ����)
		for (auto& piece : pieces) {
			int num = piece.second[0].num;
			int x = piece.second[0].x;
			int y = piece.second[0].y;
			int dir = piece.second[0].dir;

			// ������ �̵��Ϸ��� ĭ
			int nx = x + dx[dir];
			int ny = y + dy[dir];

			// A�� ���� �̵��Ϸ��� ĭ�� ü������ ����� ����̰ų� �Ķ����� ���
			if ((nx < 0 || ny < 0 || nx >= N || ny >= N) || color[nx][ny] == 2) {
				// �̵� ������ �ݴ�� �ϰ� �� ĭ �̵��Ϸ��� �ϴµ�...
				if (dir == 1 || dir == 3)
					dir += 1;
				else dir -= 1;

				// ������ �̵��Ϸ��� ĭ �ݴ�� �ٲ�
				nx = x + dx[dir];
				ny = y + dy[dir];

				// �̵��Ϸ��� ĭ�� �Ķ����� ��� �̵����� �ʰ� ���⸸ �ݴ�� �ٲ۴�.
				if ((nx < 0 || ny < 0 || nx >= N || ny >= N) || color[nx][ny] == 2) {
					if (dir == 1 || dir == 3)
						dir += 1;
					else dir -= 1;

					// ���� �ٲٰ� ��
					piece.second[0].dir = dir;
					continue;
				}

				// ���� �ٲ�
				piece.second[0].dir = dir;
				// �Ķ����� �ƴ� ��� ������ ���������� �� ������ Ȯ��
			}

			// A�� ���� �̵��Ϸ��� ĭ�� ����� ���
			if (color[nx][ny] == 0) {
				// �ش� ĭ���� �̵��Ϸ��� �ϴµ�...
				// �̹� ���� �ִ� ���
				if (board[nx][ny] != 0) {
					// A�� ���� ���� �״´�(�������)
					pieces[board[nx][ny]].insert(pieces[board[nx][ny]].end(), piece.second.begin(), piece.second.end());

					// A�� ���� �� �Ʒ��� ���� �ʱ� ������ A�� ���� map���� �����ϱ� ���� ���
					erase.insert(num);

					// nx, ny ��ġ�� �� �Ʒ��� �ִ� �� ��ȣ �ٲ�
					num = board[nx][ny];
				}
				else { // �ش� ĭ�� ����ִ� ���
				   // A�� ���� �̵������ش�.
				   // board���� �̵�, nx, ny ��ġ�� �� �Ʒ��� �ִ� �� ��ȣ�� �ٲ�
					board[nx][ny] = num;

					// A�� ���� ���� ����(��ġ �̵�)
					piece.second[0].x = nx;
					piece.second[0].y = ny;
				}
				// A�� ���� �̵��߱� ������ ���� ��ġ���� �������ش�.
				board[x][y] = 0;
			}
			else if (color[nx][ny] == 1) { // A�� ���� �̵��Ϸ��� ĭ�� �������� ���
			   // �ش� ĭ���� �̵��Ϸ��� �ϴµ�...
			   // A�� ���� �� ���� �ִ� ��� ���� �׿��ִ� ������ �ݴ�� �ٲ۴�.
				reverse(piece.second.begin(), piece.second.end());

				// A�� ���� �� �Ʒ��� ���� �ʱ� ������ A�� ���� map���� �����ϰ�
				erase.insert(num);
				// �� �Ʒ��� �ִ� �� ��ȣ�� �ٲ����Ƿ� ����
				num = piece.second[0].num;

				if (board[nx][ny] == 0) { // �ش� ĭ�� ����ִ� ���
					// A�� ���� �̵������ش�.
					// board���� �̵�
					board[nx][ny] = num;

					// A�� ���� ���� ����
					piece.second[0].x = nx;
					piece.second[0].y = ny;

					// �������� ������ �� �Ʒ� �� ��ȣ�� ���� ������ ���� �Է��������
					// �� �Ʒ��� �ִ� �� ��ȣ�� ��� �ִ� �� ���� �Է�
					pieces[num] = piece.second;

					// ���� �� �ؿ� �ִ� �� ��ȣ�� �� ���� �ö����Ƿ� ���� ����
					erase.erase(num);
				}
				else if (board[nx][ny] != 0) { // �̹� ���� �ִ� ���
					// A�� ���� ���� �״´�(�������)
					pieces[board[nx][ny]].insert(pieces[board[nx][ny]].end(), piece.second.begin(), piece.second.end());

					// �ִ� ������ �� �Ʒ� ��ȣ
					num = board[nx][ny];
				}
				// A�� ���� �̵��߱� ������ board���� �������ش�.
				board[x][y] = 0;
			}

			// ���� 4�� �̻� ���̴� ���� ���� ����
			if (pieces[num].size() >= 4) return turn;
		}

		// ������� �� ���� ����
		for (int i : erase) {
			pieces.erase(i);
		}

		//print_board();
	}

	/// TODO:: ������ ����Ǵ� ���� ��ȣ
	return -1;
}

int main() {
	// �Է�
	cin >> N >> K;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> color[i][j];
		}
	}

	for (int i = 1; i <= K; i++) {
		int x, y, dir;

		cin >> x >> y >> dir;

		pieces[i].push_back(Node(i, x - 1, y - 1, dir));
		board[x - 1][y - 1] = i;
	}

	//print_board();

	// �̵�
	int turn = move();

	if (turn > 1000)
		cout << "-1";
	else
		cout << turn;
}