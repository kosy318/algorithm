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
int n; // 維切税 滴奄
int m; // 得税 鯵呪
int k; // 虞錘球 呪
deque<Point> deq[6]; // 得 1採斗 獣拙馬惟 馬切

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
//		//cout << "得 " << num << " => ";
//		//cout << "head : " << deq[num].front().x << ", " << deq[num].front().y;
//		//cout << ", tail : " << deq[num].back().x << ", " << deq[num].back().y << endl;
//	}
//}

void find_tails() {
	vector<vector<bool>> visited(n, vector<bool>(n, false));
	for (int i = 1; i <= m; i++) {
		int x = deq[i].front().x;
		int y = deq[i].front().y;

		// 唖 map拭 得 i 紫寓級精 i稽 妊獣馬奄稽 馬切
		map[x][y] = i;
		visited[x][y] = true;

		//cout << x << ", " << y << "税 tail精 ";

		bool found = false;
		int cnt = 0;
		while (!found) {
			for (int d = 0; d < 4; d++) {
				int nx = x + dx[d];
				int ny = y + dy[d];

				if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
				if (map[nx][ny] == 0 || map[nx][ny] == 1 || visited[nx][ny]) continue;
				////////////////////// 堂鍵 採歳 : 3得戚櫛 白哀険 呪亜 赤製....
				else if (cnt != 0 && map[nx][ny] == -3) { // 何軒達製
					//cout << nx << ", " << ny << endl;
					deq[i].push_back(Point(nx, ny));

					// 唖 map拭 得 i 紫寓級精 i稽 妊獣馬奄稽 馬切
					map[nx][ny] = i;

					found = true;
					break;
				}
				else if (map[nx][ny] == -2) { // 倖搭 達製
					cnt += 1;
					x = nx;
					y = ny;

					deq[i].push_back(Point(x, y));
					// 唖 map拭 得 i 紫寓級精 i稽 妊獣馬奄稽 馬切
					map[x][y] = i;

					visited[x][y] = true;
					break;
				}
			}
		}
	}

	//print_map();
}

///////////////////// 堂鍵 採歳 : 9昔 員生稽 戚疑馬澗 依生稽 馬形檎 tail聖 胡煽 走酔壱 戚疑背醤敗
void move() {
	for (int i = 1; i <= m; i++) {
		// tail精 得 腰硲研 達焼 戚疑敗
		int tail_x = deq[i].back().x;
		int tail_y = deq[i].back().y;

		// tail戚 赤醸揮 員精 9亜 害壱
		map[tail_x][tail_y] = 9;

		// deq拭辞 固 及 据社 薦暗
		deq[i].pop_back();

		// head澗 9研 達焼 戚疑馬壱
		int head_x = deq[i].front().x;
		int head_y = deq[i].front().y;

		for (int d = 0; d < 4; d++) {
			int nx = head_x + dx[d];
			int ny = head_y + dy[d];

			if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
			if (map[nx][ny] == 9) {  // 戚疑拝 員 達製~
				// 袴軒亜 戚疑廃 員殖 得 腰硲亜 持沿
				map[nx][ny] = i;
				// deq 蒋楕拭 歯稽錘 head 蓄亜
				deq[i].push_front(Point(nx, ny));
			}
		}
	}

	//print_map();
}

#include <cmath>

int answer = 0;

///////////////// 堂鍵 採歳 : 固馬添 暗軒稽 姥馬檎 照鞠革........... 焼たたたたたたたたた
///////////////// 堂鍵 採歳 : 紫号貼事生稽 達生檎 獣娃段引害 しし
int score(Point target, int num) {
	int dis = 1;

	//cout << "head : " << deq[num].front().x << ", " << deq[num].front().y;
	//cout << ", tail : " << deq[num].back().x << ", " << deq[num].back().y << endl;

	for (Point p : deq[num]) {
		if (p.x == target.x && p.y == target.y) break;
		dis += 1;
	}
	//cout << dis << "腰 属 紫寓 限製\n";

	return dis * dis;
}

void change(int num) {
	reverse(deq[num].begin(), deq[num].end());
	//cout << "head : " << deq[num].front().x << ", " << deq[num].front().y;
	//cout << ", tail : " << deq[num].back().x << ", " << deq[num].back().y << endl;
}

void throw_ball(int round) {
	if (round / n == 0) { // 須楕拭辞 神献楕生稽 揮像
		int row = round;
		//cout << row << "楳拭辞 神献楕生稽 揮像\n";
		for (int j = 0; j < n; j++) {
			if (map[row][j] != 9 && map[row][j] != 0) { // 紫寓戚 糎仙
				//cout << map[row][j] << "腰 得 ";
				answer += score(Point(row, j), map[row][j]);

				change(map[row][j]);
				break;
			}
		}
	}
	else if (round / n == 1) { // 焼掘拭辞 是稽 揮像
		int col = round % n;
		//cout << col << "伸拭辞 是稽 揮像\n";
		for (int i = n - 1; i >= 0; i--) {
			if (map[i][col] != 9 && map[i][col] != 0) { // 紫寓戚 糎仙
				//cout << map[i][col] << "腰 得 ";
				answer += score(Point(i, col), map[i][col]);

				change(map[i][col]);
				break;
			}
		}
	}
	else if (round / n == 2) { // 神献楕拭辞 図楕生稽 揮像
		int row = n - round % n - 1;
		//cout << row << "楳拭辞 図楕生稽 揮像\n";
		for (int j = n - 1; j >= 0; j--) {
			if (map[row][j] != 9 && map[row][j] != 0) { // 紫寓戚 糎仙
				//cout << map[row][j] << "腰 得 ";
				answer += score(Point(row, j), map[row][j]);

				change(map[row][j]);
				break;
			}
		}
	}
	else if (round / n == 3) { // 是拭辞 焼掘稽 揮像
		int col = n - round % n - 1;
		//cout << col << "伸拭辞 焼掘稽 揮像\n";
		for (int i = 0; i < n; i++) {
			if (map[i][col] != 9 && map[i][col] != 0) { // 紫寓戚 糎仙
				//cout << map[i][col] << "腰 得 ";
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
			if (map[i][j] == 1) { // 袴軒 胡煽 妊獣
				deq[cnt].push_back(Point(i, j));
				cnt += 1;
			}
			else if (map[i][j] == 4) { // 掩聖 9稽 妊獣馬切.. 紫寓聖 1~5猿走 妊獣拝暗奄 凶庚
				map[i][j] = 9;
			}
			else { // 紫寓級 製呪稽 妊獣
				map[i][j] *= -1;
			}
		}
	}

	//print_map();

	// 唖 head税 tail聖 達焼醤敗
	find_tails();

	for (int i = 0; i < k; i++) {
		// 袴軒紫寓聖 魚虞辞 廃 牒 戚疑
		move();

		throw_ball(i % (4 * n));
	}

	cout << answer;
}