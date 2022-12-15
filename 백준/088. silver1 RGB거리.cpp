#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum {
	RED, GREEN, BLUE
};

int main() {
	int N;
	cin >> N;
	vector<vector<int>> rgb(N, vector<int>(3));


	for (int i = 0; i < N; i++)
		cin >> rgb[i][RED] >> rgb[i][GREEN] >> rgb[i][BLUE];

	for (int i = 1; i < N; i++) {
		rgb[i][RED] += min(rgb[i - 1][GREEN], rgb[i - 1][BLUE]);
		rgb[i][GREEN] += min(rgb[i - 1][RED], rgb[i - 1][BLUE]);
		rgb[i][BLUE] += min(rgb[i - 1][GREEN], rgb[i - 1][RED]);
	}

	cout << *min_element(rgb[N - 1].begin(), rgb[N - 1].end());
}
