#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

struct Tree {
	int age;

	Tree(int age) : age{ age }{}

	bool operator <(const Tree o1) const {
		return o1.age > this->age;
	}
};

struct Land {
	int sum_age;
	priority_queue<Tree> que;
};

vector<tuple<int, int, int>> trees;
int answer = 0;

int trees_to_breed(int K, priority_queue<Tree> que);
void drink(int K, int N, vector<vector<Land>>& map, vector<vector<int>>& nourishment, vector<vector<int>>& add);
void breeding(int K, int N, vector<vector<Land>>& map);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M, K;
	cin >> N >> M >> K;

	// NxN �� ��
	vector<vector<Land>> map(N, vector<Land>(N, Land()));
	vector<vector<int>> add(N, vector<int>(N));
	vector<vector<int>> nourishment(N, vector<int>(N, 5));

	// ���
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> add[i][j];
		}
	}

	// ����
	for (int i = 0; i < M; i++) {
		int x, y, age;
		cin >> x >> y >> age;
		map[x-1][y-1].que.push(Tree(age));
		map[x-1][y-1].sum_age += age;
		answer += 1;
	}

	for (int k = 0; k < K; k++) {
		// �� : ������ �ڽ��� ���̸�ŭ ����� ����(ĭ �ȿ� �ִ� ��и� ���� �� ����), ���� +1
		// �ϳ��� ĭ�� ������ �������� � �������� ����� ����, �ڽ��� ���̸�ŭ ����� �������� ���
		// ���� : ���� ���� ������ ����� ��(����/2)
		drink(k, N, map, nourishment, add);

		// ���� : ������ ����(���̰� 5�� ����� ����), ������ 8���� ĭ�� ���̰� 1�� ������ ����
		breeding(k, N, map);

		// �ܿ� : ����� �߰�(���� �� �� ����)
	}

	// K���� ���� �� ���� ����ִ� ������ ����?
	cout << answer;
}

void drink(int K, int N, vector<vector<Land>>& map, vector<vector<int>>& nourishment, vector<vector<int>>& add) {
	trees.clear();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int size = map[i][j].que.size();
			int A = nourishment[i][j];
			for (int k = 0; k < size; k++) {
				if (map[i][j].sum_age <= A)
					break;
				Tree t = map[i][j].que.top();
				map[i][j].que.pop();

				map[i][j].sum_age -= (t.age + K);
				nourishment[i][j] += (t.age + K) / 2;
				answer -= 1;
			}
			nourishment[i][j] += (add[i][j] - map[i][j].sum_age);
			map[i][j].sum_age += map[i][j].que.size();

			int cnt = trees_to_breed(K+1, map[i][j].que);
			trees.emplace_back(i, j, cnt);
		}
	}
}

int trees_to_breed(int K, priority_queue<Tree> que) {
	int cnt = 0;
	while (!que.empty()) {
		Tree t = que.top();
		que.pop();
		if ((t.age+K) % 5 != 0) continue;

		cnt += 1;
	}
	return cnt;
}

int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

void breeding(int K, int N, vector<vector<Land>>& map) {
	int age = -K;
	for (auto t : trees) {
		int x, y, cnt;
		tie(x, y, cnt) = t;

		for (int i = 0; i < 8; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
			answer += cnt;
			map[nx][ny].sum_age += cnt;

			for (int j = 0; j < cnt; j++) {
				map[nx][ny].que.push(Tree(age));
			}
		}
	}
}