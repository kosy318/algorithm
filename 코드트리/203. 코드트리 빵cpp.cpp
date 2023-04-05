#include <iostream>
#include <map>
#include <queue>
#include <list>

using namespace std;

struct Point {
	int x, y;

	Point(int x = 0, int y = 0) : x(x), y(y) {}
};

// ������ ����
// 0 : �� ����, 1 : ���̽�ķ��
int grid[16][16];
int n; // ������ ũ��
// i��° ����� ������� �������� ��ġ
Point store[30];
vector<Point> goal; // �������� ������ ������� ��ġ
int finish[30]; // �̹� ����

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

	int m; // ����� ��
	cin >> n >> m;

	// ������ ���� �Է¹���
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> grid[i][j];
		}
	}

	// ������� ����;��ϴ� ������ ��ġ �Է¹���
	for (int i = 0; i < m; i++) {
		cin >> store[i].x;
		cin >> store[i].y;
	}

	//////////////////////// TODO::�� �� �� �� ��� �������� ����? ///////////////////////////////
	int time = 0;
	int check = 0;
	list<pair<int, Point>> people; // ���ڿ� �ִ� �̵� ������ �����
	while (check != m) { // ���� ��ΰ� �������� �湮���� �ʾҴٸ� �����
		// 1. ���ڿ� �ִ� �����(���̽�ķ������ ���)�� ������ ���� ���� ������ ������ ���� 1ĭ ������
		// �ִ� �Ÿ��� ������. �ִܰŸ� ����� ���������� ��, ��, ����, �Ʒ� ������ ������
		if (!people.empty()) {
			//cout << time + 1 << "�ʿ� " << endl;
			move(people);
		}

		// 2. �������� �����ϸ� ����. �ٸ� ����� �ش� �������� �ִ� ĭ�� �������� ����
		while(!goal.empty()) {
			Point p = goal.back();
			goal.pop_back();
			grid[p.x][p.y] = 2; // ��������
			check += 1; // ������ ��� �� 1 ����
		}

		// 3. ���� �ð� t��. t<=m�� �����Ѵٸ� t�� ������� �������� ���� ����� ���̽� ķ���� ��
		// ���������� ��� ���� ������ -> ���� ������ ����
		// ���̽� ķ���� �̵��ϴµ��� �ð��� ���� �ҿ���� ���� (�����̵�)
		// �ٸ� ������� �ش� ���̽� ķ���� �ִ� ĭ�� ���� �� ����
		// ���������� ���ϱ� �����ص� ������ �� ����
		if (time < m) { // �� ���� ����� ���� ����
			Point camp = find_camp(store[time]); // ������� ������ ��ó�� camp�� ã��
			grid[camp.x][camp.y] = 2; // �ش� ķ���� �ƹ��� ������ ǥ��
			people.emplace_back(time, camp); // time ��° ����� camp ��ġ�� ����
			//cout << time << " ����� " << camp.x << ", " << camp.y << "�� ��Ʈ ħ" << endl;
		}

		time += 1;
	}

	cout << time;
}

int dx[] = { -1, 0, 0, 1 };
int dy[] = { 0, -1, 1, 0 };

// ���������� ��� ���� ������ -> ���� ������ ����
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
				if (grid[nx][ny] == 2) continue; // ������ �� ���� ��
				else if (grid[nx][ny] == 1) { // ���̽� ķ�� ã��
					////////////////////// Ʋ�ȴ� �κ� : ���������� ��쿡 ���� ���� ����...
					if ((camp.x == 0 && camp.y == 0) || camp.x > nx) { // ���� �Էµ� ���� ���ų�, ���� ������
						camp = Point(nx, ny);
					}
					else if (camp.x == nx && camp.y > ny) { // ���� ���ٸ� ���� ������
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
	for (int i = 0; i < size; i++) { // ��ϵǾ��ִ� ��� ����鿡 ���ؼ�
		////////////////////// Ʋ�ȴ� �κ�1 : iter�� �����Ҷ��� ��������!!
		////////////////////// Ʋ�ȴ� �κ�2 : ������ �ϰ� ���� iter�� ������ ����� ���� �ֱ� ������ while�� ����Ѵ�
		while (finish[iter->first]) { // �̹� ������ �ִ� ����̸�
			auto next = iter;
			next++;
			pp.erase(iter);
			iter = next;
			i += 1;
			if (i == size) break;
		}

		for (int d = 0; d < 4; d++) { // ������� �̵�
			int nx = iter->second.x + dx[d];
			int ny = iter->second.y + dy[d];

			if (nx <= 0 || ny <= 0 || nx > n || ny > n) continue;
			if (grid[nx][ny] == 2) continue; // ������ �� ���� ��

			// ���������� ���߿� grid���� 2�� �ٲ������

			if (store[iter->first].x == nx && store[iter->first].y == ny) {
				//cout << iter->first << "����� " << store[iter->first].x << ", " << store[iter->first].y << "�� ����" << endl;
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