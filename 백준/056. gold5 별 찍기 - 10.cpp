#include <iostream>
#include <vector>

using namespace std;

void delete_star(int x, int y, int len);

vector<vector<char>> answer;

int main() {
	int N;
	cin >> N;

	answer = vector<vector<char>>(N, vector<char>(N, '*'));
	
	delete_star(0, 0, N);

	for (auto ans : answer) {
		for (char ch : ans)
			cout << ch;
		cout << "\n";
	}
}

void delete_star(int x, int y, int len) {
	if (len == 1) return;

	delete_star(x, y, len / 3);
	delete_star(x + len / 3, y, len / 3);
	delete_star(x + 2 * len / 3, y, len / 3);

	delete_star(x, y + len / 3, len / 3);
	delete_star(x + len / 3, y + len / 3, len / 3);
	delete_star(x + 2 * len / 3, y + len / 3, len / 3);

	delete_star(x, y + 2 * len / 3, len / 3);
	delete_star(x + len / 3, y + 2 * len / 3, len / 3);
	delete_star(x + 2 * len / 3, y + 2 * len / 3, len / 3);
	
	for (int i = x + len / 3; i < x + 2 * len / 3; i++) {
		for (int j = y + len / 3; j < y + 2 * len / 3; j++) {
			answer[i][j] = ' ';
		}
	}
}

