#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct { // 점수로 정렬
	bool operator()(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b) const { return a.second.first > b.second.first; }
} comp;

struct { // index로 정렬
	bool operator()(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b) const { return a.first < b.first; }
} recomp;

int main() {
	int N; // 참가자의 수
	cin >> N;

	// scores[i][j]: i번째 대회 j번째 참가자의 점수(second.first)
	// i == 3일때는 총 합
	// first에는 index 값을 가지고있음
	// second.second에는 등수를 저장할거임
	vector<vector<pair<int, pair<int, int>>>> scores(4, vector<pair<int, pair<int, int>>>(N));
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < N; j++) {
			// index랑 점수 입력
			scores[i][j].first = j;
			cin >> scores[i][j].second.first;

			// 점수 총 합
			scores[3][j].first = j;
			scores[3][j].second.first += scores[i][j].second.first;
		}
	}

	// 점수로 sorting
	for (int i = 0; i <= 3; i++) {
		sort(scores[i].begin(), scores[i].end(), comp);
	}

	// 등수 입력
	int bf = -1;
	int rank = 0;
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j < N; j++) {
			if (bf != scores[i][j].second.first) { // 점수가 이전 사람의 점수와 다르면
				rank = j + 1;
				bf = scores[i][j].second.first;
			}

			// 등수 입력
			scores[i][j].second.second = rank;
		}
	}

	// index로 sorting
	for (int i = 0; i <= 3; i++) {
		sort(scores[i].begin(), scores[i].end(), recomp);
		for (int j = 0; j < N; j++) {
			cout << scores[i][j].second.second << " ";
		}
		cout << "\n";
	}

	return 0;
}