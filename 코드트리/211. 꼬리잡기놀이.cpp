#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

struct Point {
	int x;
	int y;
	Point(int x = -1, int y = -1) : x(x), y(y) {}
};

int map[20][20];
int n; // ������ ũ��
int m; // ���� ����
int k; // ���� ��
deque<Point> deq[6]; // �� 1���� �����ϰ� ����

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

//void print_map() {
//	//cout << "map print" << endl;
//	for (int i = 0; i < n; i++) {
//		for (int j = 0; j < n; j++) {
//			//cout << map[i][j] << " ";
//		}
//		//cout << endl;
//	}
//
//	for (int num = 1; num <= m; num++) {
//		//cout << "�� " << num << " => ";
//		//cout << "head : " << deq[num].front().x << ", " << deq[num].front().y;
//		//cout << ", tail : " << deq[num].back().x << ", " << deq[num].back().y << endl;
//	}
//}

void find_tails() {
	vector<vector<bool>> visited(n, vector<bool>(n, false));
	for (int i = 1; i <= m; i++) {
		int x = deq[i].front().x;
		int y = deq[i].front().y;

		// �� map�� �� i ������� i�� ǥ���ϱ�� ����
		map[x][y] = i;
		visited[x][y] = true;

		//cout << x << ", " << y << "�� tail�� ";

		bool found = false;
		int cnt = 0;
		while (!found) {
			for (int d = 0; d < 4; d++) {
				int nx = x + dx[d];
				int ny = y + dy[d];

				if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
				if (map[nx][ny] == 0 || map[nx][ny] == 1 || visited[nx][ny]) continue;
				////////////////////// Ʋ�� �κ� : 3���̶� �򰥸� ���� ����....
				else if (cnt != 0 && map[nx][ny] == -3) { // ����ã��
					//cout << nx << ", " << ny << endl;
					deq[i].push_back(Point(nx, ny));

					// �� map�� �� i ������� i�� ǥ���ϱ�� ����
					map[nx][ny] = i;

					found = true;
					break;
				}
				else if (map[nx][ny] == -2) { // ���� ã��
					cnt += 1;
					x = nx;
					y = ny;

					deq[i].push_back(Point(x, y));
					// �� map�� �� i ������� i�� ǥ���ϱ�� ����
					map[x][y] = i;

					visited[x][y] = true;
					break;
				}
			}
		}
	}

	//print_map();
}

///////////////////// Ʋ�� �κ� : 9�� ������ �̵��ϴ� ������ �Ϸ��� tail�� ���� ����� �̵��ؾ���
void move() {
	for (int i = 1; i <= m; i++) {
		// tail�� �� ��ȣ�� ã�� �̵���
		int tail_x = deq[i].back().x;
		int tail_y = deq[i].back().y;

		// tail�� �־��� ���� 9�� ����
		map[tail_x][tail_y] = 9;

		// deq���� �� �� ���� ����
		deq[i].pop_back();

		// head�� 9�� ã�� �̵��ϰ�
		int head_x = deq[i].front().x;
		int head_y = deq[i].front().y;

		for (int d = 0; d < 4; d++) {
			int nx = head_x + dx[d];
			int ny = head_y + dy[d];

			if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
			if (map[nx][ny] == 9) {  // �̵��� �� ã��~
				// �Ӹ��� �̵��� ���� �� ��ȣ�� ����
				map[nx][ny] = i;
				// deq ���ʿ� ���ο� head �߰�
				deq[i].push_front(Point(nx, ny));
			}
		}
	}

	//print_map();
}

#include <cmath>

int answer = 0;

///////////////// Ʋ�� �κ� : ����ź �Ÿ��� ���ϸ� �ȵǳ�........... �Ƥ�����������������
///////////////// Ʋ�� �κ� : ���Ž������ ã���� �ð��ʰ��� ����
int score(Point target, int num) {
	int dis = 1;

	//cout << "head : " << deq[num].front().x << ", " << deq[num].front().y;
	//cout << ", tail : " << deq[num].back().x << ", " << deq[num].back().y << endl;

	for (Point p : deq[num]) {
		if (p.x == target.x && p.y == target.y) break;
		dis += 1;
	}
	//cout << dis << "�� ° ��� ����\n";

	return dis * dis;
}

void change(int num) {
	reverse(deq[num].begin(), deq[num].end());
	//cout << "head : " << deq[num].front().x << ", " << deq[num].front().y;
	//cout << ", tail : " << deq[num].back().x << ", " << deq[num].back().y << endl;
}

void throw_ball(int round) {
	if (round / n == 0) { // ���ʿ��� ���������� ����
		int row = round;
		//cout << row << "�࿡�� ���������� ����\n";
		for (int j = 0; j < n; j++) {
			if (map[row][j] != 9 && map[row][j] != 0) { // ����� ����
				//cout << map[row][j] << "�� �� ";
				answer += score(Point(row, j), map[row][j]);

				change(map[row][j]);
				break;
			}
		}
	}
	else if (round / n == 1) { // �Ʒ����� ���� ����
		int col = round % n;
		//cout << col << "������ ���� ����\n";
		for (int i = n - 1; i >= 0; i--) {
			if (map[i][col] != 9 && map[i][col] != 0) { // ����� ����
				//cout << map[i][col] << "�� �� ";
				answer += score(Point(i, col), map[i][col]);

				change(map[i][col]);
				break;
			}
		}
	}
	else if (round / n == 2) { // �����ʿ��� �������� ����
		int row = n - round % n - 1;
		//cout << row << "�࿡�� �������� ����\n";
		for (int j = n - 1; j >= 0; j--) {
			if (map[row][j] != 9 && map[row][j] != 0) { // ����� ����
				//cout << map[row][j] << "�� �� ";
				answer += score(Point(row, j), map[row][j]);

				change(map[row][j]);
				break;
			}
		}
	}
	else if (round / n == 3) { // ������ �Ʒ��� ����
		int col = n - round % n - 1;
		//cout << col << "������ �Ʒ��� ����\n";
		for (int i = 0; i < n; i++) {
			if (map[i][col] != 9 && map[i][col] != 0) { // ����� ����
				//cout << map[i][col] << "�� �� ";
				answer += score(Point(i, col), map[i][col]);

				change(map[i][col]);
				break;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> k;

	int cnt = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) { // �Ӹ� ���� ǥ��
				deq[cnt].push_back(Point(i, j));
				cnt += 1;
			}
			else if (map[i][j] == 4) { // ���� 9�� ǥ������.. ����� 1~5���� ǥ���Ұű� ����
				map[i][j] = 9;
			}
			else { // ����� ������ ǥ��
				map[i][j] *= -1;
			}
		}
	}

	//print_map();

	// �� head�� tail�� ã�ƾ���
	find_tails();

	for (int i = 0; i < k; i++) {
		// �Ӹ������ ���� �� ĭ �̵�
		move();

		throw_ball(i % (4 * n));
	}

	cout << answer;
}