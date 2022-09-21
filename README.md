## algorithm
Studying algorithms by myself.

explanation(KOREAN) : https://jolly-note.tistory.com/category/coding/algorithm

### 알고리즘 스터디
- 072 gold4 연구소 : https://www.notion.so/14502-ed1647c2fd6e475980d6f9b03c1153cb
- 073 gold3 내리막길 : https://www.notion.so/1520-51d61f8a11824ff78e11811533390caf
- 074 gold4 빙산 : https://www.notion.so/2573-457813a27e184389b2829f041d6cfcd2
- 075 gold4 벽 부수고 이동하기 : https://www.notion.so/2206-c5136ed7bf4e4dbf96c846c340b86ef9
- 076 gold3 나무 재태크 : https://www.notion.so/16235-5b56f5444ab94d9d858aab3eb76ffc4e
- 077 gold3 ACM Craft : https://www.notion.so/1005-ACM-Craft-1c735ed533e74dba849b3c62125e66b7
- 078 gold3 줄세우기 : https://www.notion.so/2252-9f629e304df04bf3a694527eda64346a
- 079 gold3 파티 : https://www.notion.so/1238-d031c486c9254d7aa1b387b69d6f00f4
- 080 gold4 치즈 : https://www.notion.so/2636-16476cdcd0124108b61b3ee9399c174e
- 081 gold3 치즈 : https://www.notion.so/2638-15b827ab85d2433ab99e511277e0f624
- 083 gold3 우주 탐사선 : https://www.notion.so/17182-945b15c411674632801c151f4b724be7
- 084 gold2 문제집 : https://www.notion.so/1766-24ed20618fd740ca8bbc816c043b6990

```
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<bool> visited;
vector<vector<pair<int, int>>> tree;
int V, answer = -1;

void dfs(int cur, int total=0, int cnt=1) {
	// if (total == 0) visited = vector<bool>(V + 1, false);
	if (answer < total) answer = total;
	if (cnt == V) return;

	for (auto vp : tree[cur]) {
		int node = vp.first;
		int dis = vp.second;

		if (visited[node]) continue;
		visited[node] = true;
		dfs(node, total + dis, cnt+1);
		visited[node] = false;
	}
}

int main() {
	cin >> V;

	tree = vector<vector<pair<int, int>>>(V + 1);

	for (int i = 1; i <= V; i++) {
		int node, dis;
		int from;
		cin >> from;
		while (true) {
			cin >> node;
			if (node == -1) break;
			cin >> dis;

			tree[from].push_back({ node, dis });
		}
	}

	visited = vector<bool>(V + 1, false);
	for (int i = 1; i <= V; i++) {
		visited[i] = true;
		dfs(i);
		visited[i] = false;
	}

	cout << answer << endl;
}
```
