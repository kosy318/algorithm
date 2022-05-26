#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

int cnt = 0;
vector<int> house;
vector<vector<int>> map;

vector<int> dir_x = { 1, -1, 0, 0 };
vector<int> dir_y = { 0, 0, 1, -1 };
void dfs(int i, int j, int idx) {
	if (map[i][j] != -1) return;
	house[idx]++;
	map[i][j] = cnt;

	for (int k = 0; k < 4; k++) {
		if (i + dir_x[k] < 0 || i + dir_x[k] >= map.size() ||
			j + dir_y[k] < 0 || j + dir_y[k] >= map.size()) continue;
		dfs(i + dir_x[k], j + dir_y[k], idx);
	}
}

int main() {
	int N;
	cin >> N;
	map = vector<vector<int>>(N, vector<int>(N, 0));

	string num;
	for (int i = 0; i < N; i++) {
		cin >> num;
		for (int j = 0; j < N; j++) {
			if (num[j] == '1') map[i][j] = -1;
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == -1) {
				cnt++;
				house.push_back(0);
				dfs(i, j, cnt-1);
			}
		}
	}
	
	sort(house.begin(), house.end());
	cout << cnt << endl;
	for (int n : house) cout << n << endl;
}