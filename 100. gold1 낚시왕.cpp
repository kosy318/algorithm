#include <iostream>
#include <vector>

using namespace std;

struct Shark {
	int speed, direction, size;

	Shark(int speed=0, int direction=0, int size=0) : speed{ speed }, direction{ direction }, size{ size }{}
};

int dx[] = { 0, -1, 1, 0, 0 };
int dy[] = { 0, 0, 0, 1, -1 };

vector<vector<Shark>> move(vector<vector<Shark>>& map, int R, int C) {
	vector<vector<Shark>> moved_map(R+1, vector<Shark>(C+1, Shark()));
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (map[i][j].size == 0) continue; // shark�� ������ �Ѿ

			Shark cur = map[i][j];
			int nx = i + dx[cur.direction] * cur.speed;
			int ny = j + dy[cur.direction] * cur.speed;

			while (nx <= 0 || nx > R || ny <= 0 || ny > C){
				if (nx <= 0 || nx > R) { // ����
					// ���� �ٲ�
					if (cur.direction == 1) cur.direction = 2;
					else cur.direction = 1;

					// �� ��ġ
					nx = (nx <= 0) ? 2 - nx : 2 * R - nx;
				}
				else if (ny <= 0 || ny > C) { // �¿�
					// ���� �ٲ�
					if (cur.direction == 3) cur.direction = 4;
					else cur.direction = 3;

					// �� ��ġ
					ny = (ny <= 0) ? 2 - ny : 2 * C - ny;
				}
			}
			
			if (moved_map[nx][ny].size < cur.size) // ū �� �ڸ� ����
				moved_map[nx][ny] = cur;
		}
	}

	return moved_map;
}

int main() {
	int R, C, shark_num;
	cin >> R >> C >> shark_num;

	vector<vector<Shark>> map(R+1, vector<Shark>(C+1, Shark()));

	for (int i = 0; i < shark_num; i++) {
		int r, c, s, d, z;
		cin >> r >> c >> s >> d >> z;
		map[r][c] = Shark(s, d, z);
	}

	int total_size = 0;
	for (int person = 1; person <= C; person++) { // person moves
		// eat
		for (int i = 1; i <= R; i++) {
			if (map[i][person].size != 0) {
				total_size += map[i][person].size;
				map[i][person] = Shark();
				break;
			}
		}

		// shark move
		map = move(map, R, C);
	}

	cout << total_size;
}