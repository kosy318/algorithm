#include <iostream>
#include <vector>

using namespace std;

int N, M, K;
int x, y; // 주사위 위치
vector<vector<int>> map;
vector<int> horizontal(4, 0); // 남, 북으로 움직이는 배열
vector<int> vertical(4, 0); // 동, 서로 움직이는 배열
// 두 벡터는 전개도상, 1번 index와 3번 index가 동일한 위치임
// 1번 index : 상단, 3번 index : 하단

void copy_num(vector<int>& vec) {
	if (map[x][y] == 0) map[x][y] = vec[3];
	else {
		vec[3] = map[x][y];
		map[x][y] = 0;
	}
}

void move(vector<int>& vec, vector<int>& vec2, int add) {
	vector<int> temp(4);
	for (int i = 0; i < 4; i++) {
		temp[(4+i+add)%4] = vec[i];
	}
	vec = temp;
	copy_num(vec);

	vec2[1] = vec[1];
	vec2[3] = vec[3];

	cout << vec[1] << "\n";
}

void get_order(int K) {
	int order;
	for (int i = 0; i < K; i++) {
		cin >> order;
		switch (order) {
		case 1: // 동쪽
			if (y + 1 < M) {
				y += 1;
				move(vertical, horizontal, 1);
			}
			break;
		case 2: // 서쪽
			if (y - 1 >= 0) {
				y -= 1;
				move(vertical, horizontal, -1);
			}
			break;
		case 3: // 북쪽
			if (x - 1 >= 0) {
				x -= 1;
				move(horizontal, vertical, -1);
			}
			break;
		case 4: // 남쪽
			if (x + 1 < N) {
				x += 1;
				move(horizontal, vertical, 1);
			}
			break;
		default:
			break;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M >> x >> y >> K;

	map = vector<vector<int>>(N, vector<int>(M));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	get_order(K);
}