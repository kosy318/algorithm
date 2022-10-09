#include <iostream>
#include <vector>

using namespace std;

int N, M, K;
int x, y; // �ֻ��� ��ġ
vector<vector<int>> map;
vector<int> horizontal(4, 0); // ��, ������ �����̴� �迭
vector<int> vertical(4, 0); // ��, ���� �����̴� �迭
// �� ���ʹ� ��������, 1�� index�� 3�� index�� ������ ��ġ��
// 1�� index : ���, 3�� index : �ϴ�

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
		case 1: // ����
			if (y + 1 < M) {
				y += 1;
				move(vertical, horizontal, 1);
			}
			break;
		case 2: // ����
			if (y - 1 >= 0) {
				y -= 1;
				move(vertical, horizontal, -1);
			}
			break;
		case 3: // ����
			if (x - 1 >= 0) {
				x -= 1;
				move(horizontal, vertical, -1);
			}
			break;
		case 4: // ����
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