#include <iostream>
#include <vector>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N;
	cin >> N;
	vector<pair<int, int>> works(N);
	vector<int> schedule(N);

	for (int i = 0; i < N; i++) {
		int t, p;
		cin >> t >> p;
		works[i] = { t, p };
	}

	for (int i = 0; i < N; i++) {
		int time = i + works[i].first - 1;
		int cost = works[i].second;
		if (i - 1 >= 0) cost += schedule[i - 1];
		if (time >= N || time <0) continue;
		if (schedule[time] < cost) {
			for (int j = time; j < N; j++) {
				if (schedule[j] >= cost) break;
				schedule[j] = cost;
			}
		}
	}

	cout << schedule[N - 1];
}