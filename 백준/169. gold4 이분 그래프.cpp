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
			if (color[i] != 0) { // �湮�� ���� �ִ� �����
				if (color[i] == color[cur]) // ������ ��尡 ���� ������
					return false; // �̺� �׷����� �ƴ�
			}
			else { // �湮�� ���� ����
				que.push(i);
				color[i] = color[cur] * -1; // cur�� color�� �ݴ� ������ ĥ����
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
		int V, E; // V: ������ ����, E: ������ ����
		cin >> V >> E;
		
		vector<vector<int>> edges(V);
		for (int e = 0; e < E; e++) {
			int u, v;
			cin >> u >> v;

			edges[u - 1].push_back(v - 1); // ������ ��ȣ�� 1���� �����ϴµ� 0���� �����ϰ� �ϱ� ���ؼ� 1�� ����
			edges[v - 1].push_back(u - 1);
		}

		bool bipartite = true;
		vector<int> color(V); // 1, -1�� ǥ���Ұ���
		for (int i = 0; i < V; i++) { // ��� ������ ����Ǿ��ִ� ���°� �ƴ� ���� �����Ƿ� �湮���� ��带 ã�� bfs�� ������.
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