#include <iostream>
#include <map>
#include <queue>
#include <list>

using namespace std;

struct Point {
	int x, y;

	Point(int x = 0, int y = 0) : x(x), y(y) {}
};

// 격자의 정보
// 0 : 빈 공간, 1 : 베이스캠프
int grid[16][16];
int n; // 격자의 크기
// i번째 사람이 가고싶은 편의점의 위치
Point store[30];
vector<Point> goal; // 편의점에 도달한 사람들의 위치
int finish[30]; // 이미 도착

Point find_camp(Point point);
void move(list<pair<int, Point>>& pp);

void print() {
	//cout << endl;	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			//cout << grid[i][j] << " ";
		}
		//cout << endl;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int m; // 사람의 수
	cin >> n >> m;

	// 격자의 정보 입력받음
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> grid[i][j];
		}
	}

	// 사람들이 가고싶어하는 편의점 위치 입력받음
	for (int i = 0; i < m; i++) {
		cin >> store[i].x;
		cin >> store[i].y;
	}

	//////////////////////// TODO::총 몇 분 후 모두 편의점에 도착? ///////////////////////////////
	int time = 0;
	int check = 0;
	list<pair<int, Point>> people; // 격자에 있는 이동 가능한 사람들
	while (check != m) { // 아직 모두가 편의점을 방문하지 않았다면 계속함
		// 1. 격자에 있는 사람들(베이스캠프에서 출발)이 본인이 가고 싶은 편의점 방향을 향해 1칸 움직임
		// 최단 거리로 움직임. 최단거리 방법이 여러가지면 위, 왼, 오른, 아래 순위로 움직임
		if (!people.empty()) {
			//cout << time + 1 << "초에 " << endl;
			move(people);
		}

		// 2. 편의점에 도착하면 멈춤. 다른 사람은 해당 편의점이 있는 칸을 지나가지 못함
		while(!goal.empty()) {
			Point p = goal.back();
			goal.pop_back();
			grid[p.x][p.y] = 2; // 못지나감
			check += 1; // 도착한 사람 수 1 증가
		}

		// 3. 현재 시간 t분. t<=m을 만족한다면 t는 가고싶은 편의점과 가장 가까운 베이스 캠프에 들어감
		// 여러가지인 경우 행이 작은거 -> 열이 작은거 순서
		// 베이스 캠프로 이동하는데에 시간이 전혀 소요되지 않음 (순간이동)
		// 다른 사람들은 해당 베이스 캠프가 있는 칸은 지날 수 없음
		// 편의점으로 향하기 시작해도 지나갈 수 없음
		if (time < m) { // 더 나올 사람이 있을 때만
			Point camp = find_camp(store[time]); // 가고싶은 편의점 근처의 camp를 찾음
			grid[camp.x][camp.y] = 2; // 해당 캠프는 아무도 못감을 표시
			people.emplace_back(time, camp); // time 번째 사람이 camp 위치에 있음
			//cout << time << " 사람이 " << camp.x << ", " << camp.y << "에 텐트 침" << endl;
		}

		time += 1;
	}

	cout << time;
}

int dx[] = { -1, 0, 0, 1 };
int dy[] = { 0, -1, 1, 0 };

// 여러가지인 경우 행이 작은거 -> 열이 작은거 순서
Point find_camp(Point point) {
	Point camp(0, 0);
	queue<Point> que;

	que.push(point);

	while (!que.empty()) {
		int size = que.size();
		for (int i = 0; i < size; i++) {
			Point cur = que.front(); que.pop();

			for (int d = 0; d < 4; d++) {
				int nx = cur.x + dx[d];
				int ny = cur.y + dy[d];

				if (nx <= 0 || ny <= 0 || nx > n || ny > n) continue;
				if (grid[nx][ny] == 2) continue; // 지나갈 수 없는 곳
				else if (grid[nx][ny] == 1) { // 베이스 캠프 찾음
					////////////////////// 틀렸던 부분 : 여러가지인 경우에 대해 적지 않음...
					if ((camp.x == 0 && camp.y == 0) || camp.x > nx) { // 아직 입력된 값이 없거나, 행이 작으면
						camp = Point(nx, ny);
					}
					else if (camp.x == nx && camp.y > ny) { // 행이 같다면 열이 작으면
						camp = Point(nx, ny);
					}
				}
				else {
					que.push(Point(nx, ny));
				}
			}
		}
		if (camp.x != 0 && camp.y != 0) return camp;
	}
}


void move(list<pair<int, Point>>& pp) {
	auto iter = pp.begin();
	int size = pp.size();
	for (int i = 0; i < size; i++) { // 등록되어있는 모든 사람들에 대해서
		////////////////////// 틀렸던 부분1 : iter를 삭제할때는 주의하자!!
		////////////////////// 틀렸던 부분2 : 삭제를 하고 다음 iter도 도착한 사람일 수도 있기 때문에 while을 써야한다
		while (finish[iter->first]) { // 이미 도착해 있는 사람이면
			auto next = iter;
			next++;
			pp.erase(iter);
			iter = next;
			i += 1;
			if (i == size) break;
		}

		for (int d = 0; d < 4; d++) { // 사방으로 이동
			int nx = iter->second.x + dx[d];
			int ny = iter->second.y + dy[d];

			if (nx <= 0 || ny <= 0 || nx > n || ny > n) continue;
			if (grid[nx][ny] == 2) continue; // 지나갈 수 없는 곳

			// 도달했으면 나중에 grid에서 2로 바꿔줘야함

			if (store[iter->first].x == nx && store[iter->first].y == ny) {
				//cout << iter->first << "사람이 " << store[iter->first].x << ", " << store[iter->first].y << "에 도착" << endl;
				goal.push_back(store[iter->first]);
				finish[iter->first] = true;
				break;
			}
			else {
				pp.push_back({ iter->first, Point(nx, ny) });
			}
		}
		iter++;
	}
}
