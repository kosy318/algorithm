#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;

int N, answer = INT_MAX;
vector<vector<int>> synergy;
vector<bool> team;

int calculate(vector<bool>& team) {
	int t1 = 0, t2 = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if(team[i] && team[j]) t1 += synergy[i][j];
			else if(!team[i] && !team[j]) t2 += synergy[i][j];
		}
	}

	return abs(t1 - t2);
}

void comb(int idx = 0, int start = 0) {
	if (idx == N / 2) {
		answer = min(answer, calculate(team));
	}

	for (int i = start; i < N; i++) {
		team[i] = true;
		comb(idx + 1, i + 1);
		team[i] = false;
	}
}

int main() {
	cin >> N;

	synergy = vector<vector<int>>(N, vector<int>(N));
	team = vector<bool>(N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> synergy[i][j];
		}
	}

	comb();

	cout << answer;
}