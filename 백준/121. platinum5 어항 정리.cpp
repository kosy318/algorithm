#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int dx[] = { 1, 0 };
int dy[] = { 0, 1 };

int fish_max = -1, fish_min = INT_MAX;

vector<int> moved(vector<vector<int>>& org) {
	fish_max = -1, fish_min = INT_MAX;
	vector<vector<int>> fish;
	for (auto vec : org)
		fish.push_back(vector<int>(vec.size(), 0));

	for (int i = 0; i < org.size(); i++) {
		for (int j = 0; j < org[i].size(); j++) {
			int num = org[i][j];
			for (int dir = 0; dir < 2; dir++) {
				int nx = i + dx[dir];
				int ny = j + dy[dir];

				if (nx < 0 || ny < 0 || nx >= org.size() || (ny >= org[0].size() && nx != org.size()-1) || ny >= org[i].size()) continue;

				int n_num = org[nx][ny];
				int d = abs(n_num - num) / 5;
				if (d > 0) {
					if (n_num > num) {
						fish[nx][ny] -= d;
						fish[i][j] += d;
					}
					else if (n_num < num) {
						fish[nx][ny] += d;
						fish[i][j] -= d;
					}
				}
			}
		}
	}

	for (int i = 0; i < org.size(); i++) {
		for (int j = 0; j < org[i].size(); j++) {
			org[i][j] += fish[i][j];
		}
	}

	vector<int> result;
	for (int y = 0; y < org[org.size() - 1].size(); y++) {
		for (int x = org.size() - 1; x >= 0; x--) {
			fish_max = max(fish_max, org[x][y]);
			fish_min = min(fish_min, org[x][y]);
			result.push_back(org[x][y]);
			if (y >= org[0].size()) break;
		}
	}
	return result;
}

vector<int> spin_stack(vector<int>& fish_bowl) {
	vector<vector<int>> spinned;
	spinned.push_back({ fish_bowl[0] });
	vector<int> temp;
	for (int i = 1; i < fish_bowl.size(); i++) {
		temp.push_back(fish_bowl[i]);
	}
	spinned.push_back(temp);

	int height = spinned[0].size() + 1;
	int left = fish_bowl.size() - height;

	while (height <= left) {
		left -= height;
		height = spinned[0].size() + 1;
		vector<vector<int>> spinning;
		for (int y = 0; y < spinned[0].size(); y++) {
			vector<int> temp;
			for (int x = spinned.size()-1; x >= 0; x--) {
				temp.push_back(spinned[x][y]);
			}
			spinning.push_back(temp);
		}

		vector<int> temp;
		for (int y = spinned[0].size(); y < spinned[spinned.size() - 1].size(); y++) {
			temp.push_back(spinned[spinned.size() - 1][y]);
		}
		spinning.push_back(temp);

		spinned = vector<vector<int>>(spinning);
		
	}

	return moved(spinned);
}

// N은 4의 배수! 걱정x
vector<int> divide_stack(vector<int>& fish_bowl) {
	vector<vector<int>> stacked;
	stacked.push_back(fish_bowl);
	for (int cnt = 0; cnt <= 1; cnt++) {
		vector<vector<int>> stacking;

		for (int i = stacked.size()-1; i >= 0 ; i--) {
			vector<int> temp;
			for (int j = stacked[0].size()/2 - 1; j >= 0; j--) {
				temp.push_back(stacked[i][j]);
			}
			stacking.push_back(temp);
		}

		for (int i = 0; i < stacked.size(); i++) {
			vector<int> temp;
			for (int j = stacked[0].size() / 2; j < stacked[0].size(); j++) {
				temp.push_back(stacked[i][j]);
			}
			stacking.push_back(temp);
		}

		stacked = vector<vector<int>>(stacking);
	}

	return moved(stacked);
} 

int organize(vector<int>& fish_bowl, int K) {
	int cnt = 0;
	while (true) {
		for (int i = 0; i < fish_bowl.size(); i++) {
			if (fish_bowl[i] == fish_min) fish_bowl[i] += 1;
		}
		fish_bowl = spin_stack(fish_bowl);
		fish_bowl = divide_stack(fish_bowl);
		cnt += 1;
		if (fish_max - fish_min <= K) break;
	}
	return cnt;
}

int main() {
	int N; // fish_bowl의 수
	int K; // 어항의 물고기 수 차이가 K 이하
	cin >> N >> K;

	vector<int> fish_bowl(N);

	for (int i = 0; i < N; i++) {
		cin >> fish_bowl[i];
		fish_max = max(fish_max, fish_bowl[i]);
		fish_min = min(fish_min, fish_bowl[i]);
	}

	if(fish_max - fish_min > K) cout << organize(fish_bowl, K);
	else  cout << "0";
}