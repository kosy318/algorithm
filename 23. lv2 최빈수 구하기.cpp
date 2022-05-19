// https://jolly-note.tistory.com/57

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

bool comp(const pair<int, int>& a, const pair<int, int>& b) {
	if (a.second == b.second) return a.first > b.first;
	return a.second > b.second;
}

int main() {
	int n, tc;
	cin >> n;
	for (int i = 0; i < n; i++) {
		map<int, int> scores;
		cin >> tc;
		int score;
		for (int j = 0; j < 1000; j++) {
			cin >> score;
			scores[score] += 1;
		}

		vector<pair<int, int>> scores_vec(scores.begin(), scores.end());
		sort(scores_vec.begin(), scores_vec.end(), comp);

		cout << "#" << tc << " " << scores_vec[0].first << endl;
	}
}