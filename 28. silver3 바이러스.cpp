// https://jolly-note.tistory.com/65

#include<iostream>
#include<vector>

using namespace std;

vector<bool> visited;
vector<vector<int>> adj;
int cnt = 0;

void dfs(int current) {
	visited[current] = true;

	for (int a : adj[current]) {
		if (visited[a]) continue;

		cnt++;
		dfs(a);
	}
}

int main() {
	int computer, connected;

	cin >> computer >> connected;
	adj = vector<vector<int>>(computer+1);
	visited = vector<bool>(computer + 1);

	int x, y;
	for (int i = 0; i < connected; i++) {
		cin >> x >> y;

		adj[x].push_back(y);
		adj[y].push_back(x);
	}

	dfs(1);

	cout << cnt;
}