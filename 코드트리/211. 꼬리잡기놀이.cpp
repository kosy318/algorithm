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
int n; // 격자의 크기
int m; // 팀의 개수
int k; // 라운드 수
deque<Point> deq[6]; // 팀 1부터 시작하게 하자

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
//		//cout << "팀 " << num << " => ";
//		//cout << "head : " << deq[num].front().x << ", " << deq[num].front().y;
//		//cout << ", tail : " << deq[num].back().x << ", " << deq[num].back().y << endl;
//	}
//}

void find_tails() {
	vector<vector<bool>> visited(n, vector<bool>(n, false));
	for (int i = 1; i <= m; i++) {
		int x = deq[i].front().x;
		int y = deq[i].front().y;

		// 각 map에 팀 i 사람들은 i로 표시하기로 하자
		map[x][y] = i;
		visited[x][y] = true;

		//cout << x << ", " << y << "의 tail은 ";

		bool found = false;
		int cnt = 0;
		while (!found) {
			for (int d = 0; d < 4; d++) {
				int nx = x + dx[d];
				int ny = y + dy[d];

				if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
				if (map[nx][ny] == 0 || map[nx][ny] == 1 || visited[nx][ny]) continue;
				////////////////////// 틀린 부분 : 3팀이랑 헷갈릴 수가 있음....
				else if (cnt != 0 && map[nx][ny] == -3) { // 꼬리찾음
					//cout << nx << ", " << ny << endl;
					deq[i].push_back(Point(nx, ny));

					// 각 map에 팀 i 사람들은 i로 표시하기로 하자
					map[nx][ny] = i;

					found = true;
					break;
				}
				else if (map[nx][ny] == -2) { // 몸통 찾음
					cnt += 1;
					x = nx;
					y = ny;

					deq[i].push_back(Point(x, y));
					// 각 map에 팀 i 사람들은 i로 표시하기로 하자
					map[x][y] = i;

					visited[x][y] = true;
					break;
				}
			}
		}
	}

	//print_map();
}

///////////////////// 틀린 부분 : 9인 곳으로 이동하는 것으로 하려면 tail을 먼저 지우고 이동해야함
void move() {
	for (int i = 1; i <= m; i++) {
		// tail은 팀 번호를 찾아 이동함
		int tail_x = deq[i].back().x;
		int tail_y = deq[i].back().y;

		// tail이 있었던 곳은 9가 남고
		map[tail_x][tail_y] = 9;

		// deq에서 맨 뒤 원소 제거
		deq[i].pop_back();

		// head는 9를 찾아 이동하고
		int head_x = deq[i].front().x;
		int head_y = deq[i].front().y;

		for (int d = 0; d < 4; d++) {
			int nx = head_x + dx[d];
			int ny = head_y + dy[d];

			if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
			if (map[nx][ny] == 9) {  // 이동할 곳 찾음~
				// 머리가 이동한 곳엔 팀 번호가 생김
				map[nx][ny] = i;
				// deq 앞쪽에 새로운 head 추가
				deq[i].push_front(Point(nx, ny));
			}
		}
	}

	//print_map();
}

#include <cmath>

int answer = 0;

///////////////// 틀린 부분 : 맨하탄 거리로 구하면 안되네........... 아ㅏㅏㅏㅏㅏㅏㅏㅏㅏ
///////////////// 틀린 부분 : 사방탐색으로 찾으면 시간초과남 ㅇㅇ
int score(Point target, int num) {
	int dis = 1;

	//cout << "head : " << deq[num].front().x << ", " << deq[num].front().y;
	//cout << ", tail : " << deq[num].back().x << ", " << deq[num].back().y << endl;

	for (Point p : deq[num]) {
		if (p.x == target.x && p.y == target.y) break;
		dis += 1;
	}
	//cout << dis << "번 째 사람 맞음\n";

	return dis * dis;
}

void change(int num) {
	reverse(deq[num].begin(), deq[num].end());
	//cout << "head : " << deq[num].front().x << ", " << deq[num].front().y;
	//cout << ", tail : " << deq[num].back().x << ", " << deq[num].back().y << endl;
}

void throw_ball(int round) {
	if (round / n == 0) { // 외쪽에서 오른쪽으로 던짐
		int row = round;
		//cout << row << "행에서 오른쪽으로 던짐\n";
		for (int j = 0; j < n; j++) {
			if (map[row][j] != 9 && map[row][j] != 0) { // 사람이 존재
				//cout << map[row][j] << "번 팀 ";
				answer += score(Point(row, j), map[row][j]);

				change(map[row][j]);
				break;
			}
		}
	}
	else if (round / n == 1) { // 아래에서 위로 던짐
		int col = round % n;
		//cout << col << "열에서 위로 던짐\n";
		for (int i = n - 1; i >= 0; i--) {
			if (map[i][col] != 9 && map[i][col] != 0) { // 사람이 존재
				//cout << map[i][col] << "번 팀 ";
				answer += score(Point(i, col), map[i][col]);

				change(map[i][col]);
				break;
			}
		}
	}
	else if (round / n == 2) { // 오른쪽에서 왼쪽으로 던짐
		int row = n - round % n - 1;
		//cout << row << "행에서 왼쪽으로 던짐\n";
		for (int j = n - 1; j >= 0; j--) {
			if (map[row][j] != 9 && map[row][j] != 0) { // 사람이 존재
				//cout << map[row][j] << "번 팀 ";
				answer += score(Point(row, j), map[row][j]);

				change(map[row][j]);
				break;
			}
		}
	}
	else if (round / n == 3) { // 위에서 아래로 던짐
		int col = n - round % n - 1;
		//cout << col << "열에서 아래로 던짐\n";
		for (int i = 0; i < n; i++) {
			if (map[i][col] != 9 && map[i][col] != 0) { // 사람이 존재
				//cout << map[i][col] << "번 팀 ";
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
			if (map[i][j] == 1) { // 머리 먼저 표시
				deq[cnt].push_back(Point(i, j));
				cnt += 1;
			}
			else if (map[i][j] == 4) { // 길을 9로 표시하자.. 사람을 1~5까지 표시할거기 때문
				map[i][j] = 9;
			}
			else { // 사람들 음수로 표시
				map[i][j] *= -1;
			}
		}
	}

	//print_map();

	// 각 head의 tail을 찾아야함
	find_tails();

	for (int i = 0; i < k; i++) {
		// 머리사람을 따라서 한 칸 이동
		move();

		throw_ball(i % (4 * n));
	}

	cout << answer;
}