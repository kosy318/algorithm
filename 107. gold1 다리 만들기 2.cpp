#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct Bridge {
	int from, to, weight;

	Bridge(int from, int to, int weight) : from{ from }, to{ to }, weight{ weight }{}

	bool operator < (const Bridge& b) {
		return weight < b.weight;
	}
};

int N, M;
int num = 1;
int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };
vector<int> parents;
vector<Bridge> bridge_list;

void coloring(vector<vector<int>>& map) {
	vector<vector<bool>> visited(N, vector<bool>(M));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (visited[i][j]) continue;
			visited[i][j] = true;
			if (map[i][j] != -1) continue;

			queue<pair<int, int>> que;
			que.push({ i, j });

			while (!que.empty()) {
				int x = que.front().first;
				int y = que.front().second;
				map[x][y] = num;
				que.pop();

				for (int d = 0; d < 4; d++) {
					int nx = x + dx[d];
					int ny = y + dy[d];

					if (nx < 0 || ny < 0 || nx >= N || ny >= M || visited[nx][ny]) continue;
					visited[nx][ny] = true;
					if (map[nx][ny] == 0) continue;
					que.push({ nx, ny });
				}
			}
			num += 1;
		}
	}
}

// 위로 가는 애랑 오른쪽으로 가는 애만 만들거임
void build_bridges(vector<vector<int>>& map) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] != 0) continue;
			if (j - 1 >= 0 && map[i][j - 1] != 0) {
				int cnt = 1;
				int cur_bridge = map[i][j - 1];
				int next_bridge = 0;
				while (j+cnt <M) {
					if (map[i][j + cnt] == 0) cnt += 1;
					else if (map[i][j + cnt] != 0) {
						next_bridge = map[i][j + cnt];
						break;
					}
				}
				if (cnt >= 2 && next_bridge != 0) {
					bridge_list.push_back(Bridge(cur_bridge, next_bridge, cnt));
				}
			}
			if (i + 1 < N && map[i+1][j] != 0) {
				int cnt = 1;
				int cur_bridge = map[i+1][j];
				int next_bridge = 0;
				while (i - cnt >= 0) {
					if (map[i - cnt][j] == 0) cnt += 1;
					else if (map[i - cnt][j] != 0) {
						next_bridge = map[i - cnt][j];
						break;
					}
				}
				if (cnt >= 2 && next_bridge != 0) {
					bridge_list.push_back(Bridge(cur_bridge, next_bridge, cnt));
				}
			}
		}
	}
}

void make() { // 크기가 1인 서로소 집합 생성
	parents = vector<int>(num);
	for (int i = 0; i < num; i++) { // 모든 노드가 자신을 부모로 하는 (대표자) 집합으로 만듦
		parents[i] = i;
	}
}

int find(int a) { // a의 대표자 찾기
	if (parents[a] == a) return a;
	return parents[a] = find(parents[a]); // 우리의 대표자를 나의 부모로 .. : path compression
}

bool union_set(int a, int b) { // 리턴값 : true -> union 성공
	int aRoot = find(a);
	int bRoot = find(b);

	if (aRoot == bRoot) return false; // 합칠 수 없음

	parents[bRoot] = aRoot;
	return true;
}

int answer = 0;
void kruskal() {
	int temp = 0;
	int count = 0;
	for (auto b : bridge_list) {
		if (union_set(b.from, b.to)) {
			temp += b.weight;
			if (++count == num - 2) {
				answer = temp;
				break;
			}
		}
	}
}

int main() {
	cin >> N >> M;
	vector<vector<int>> map(N, vector<int>(M));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int num;
			cin >> num;
			map[i][j] -= num;
		}
	}

	coloring(map);

	build_bridges(map);
	sort(bridge_list.begin(), bridge_list.end());
	
	make();
	kruskal();
	(answer == 0)? cout << "-1" : cout << answer;
}