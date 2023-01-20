#include <iostream>
#include <queue>

using namespace std;

bool is_bipartite(int V, vector<vector<int>>& edges, vector<int>& color, int start) {
	queue<int> que;
	que.push(start);
	color[start] = 1;

	while (!que.empty()) {
		int cur = que.front();
		que.pop();

		for (int i : edges[cur]) {
			if (color[i] != 0) { // 방문한 적이 있는 노드임
				if (color[i] == color[cur]) // 인접한 노드가 색이 동일함
					return false; // 이분 그래프가 아님
			}
			else { // 방문한 적이 없음
				que.push(i);
				color[i] = color[cur] * -1; // cur의 color와 반대 색으로 칠해줌
			}
		}
	}

	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		int V, E; // V: 정점의 개수, E: 간선의 개수
		cin >> V >> E;
		
		vector<vector<int>> edges(V);
		for (int e = 0; e < E; e++) {
			int u, v;
			cin >> u >> v;

			edges[u - 1].push_back(v - 1); // 정점의 번호는 1부터 시작하는데 0부터 시작하게 하기 위해서 1을 뺐음
			edges[v - 1].push_back(u - 1);
		}

		bool bipartite = true;
		vector<int> color(V); // 1, -1로 표시할거임
		for (int i = 0; i < V; i++) { // 모든 정점이 연결되어있는 상태가 아닐 수도 있으므로 방문안한 노드를 찾아 bfs를 돌린다.
			if (color[i] == 0) {
				bipartite = is_bipartite(V, edges, color, i);
				if (!bipartite) break;
			}
		}
		if (bipartite)
			cout << "YES\n";
		else cout << "NO\n";
	}
}