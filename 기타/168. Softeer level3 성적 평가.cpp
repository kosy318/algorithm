#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct { // ������ ����
	bool operator()(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b) const { return a.second.first > b.second.first; }
} comp;

struct { // index�� ����
	bool operator()(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b) const { return a.first < b.first; }
} recomp;

int main() {
	int N; // �������� ��
	cin >> N;

	// scores[i][j]: i��° ��ȸ j��° �������� ����(second.first)
	// i == 3�϶��� �� ��
	// first���� index ���� ����������
	// second.second���� ����� �����Ұ���
	vector<vector<pair<int, pair<int, int>>>> scores(4, vector<pair<int, pair<int, int>>>(N));
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < N; j++) {
			// index�� ���� �Է�
			scores[i][j].first = j;
			cin >> scores[i][j].second.first;

			// ���� �� ��
			scores[3][j].first = j;
			scores[3][j].second.first += scores[i][j].second.first;
		}
	}

	// ������ sorting
	for (int i = 0; i <= 3; i++) {
		sort(scores[i].begin(), scores[i].end(), comp);
	}

	// ��� �Է�
	int bf = -1;
	int rank = 0;
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j < N; j++) {
			if (bf != scores[i][j].second.first) { // ������ ���� ����� ������ �ٸ���
				rank = j + 1;
				bf = scores[i][j].second.first;
			}

			// ��� �Է�
			scores[i][j].second.second = rank;
		}
	}

	// index�� sorting
	for (int i = 0; i <= 3; i++) {
		sort(scores[i].begin(), scores[i].end(), recomp);
		for (int j = 0; j < N; j++) {
			cout << scores[i][j].second.second << " ";
		}
		cout << "\n";
	}

	return 0;
}