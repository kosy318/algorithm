#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int N;
	cin >> N;
	vector<vector<int>> triangle(N);

	for (int i = 0; i < N; i++) {
		int num;
		for (int j = 0; j <= i; j++) {
			cin >> num;
			triangle[i].push_back(num);
		}
	}

	for (int i = 1; i < N; i++) {
		for (int j = 0; j <= i; j++) {
			if (j - 1 < 0) triangle[i][j] += triangle[i - 1][j];
			else if (i == j) triangle[i][j] += triangle[i - 1][j - 1];
			else triangle[i][j] += max(triangle[i - 1][j - 1], triangle[i - 1][j]);
		}
	}

	cout << *max_element(triangle[N - 1].begin(), triangle[N - 1].end());
}