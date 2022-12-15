#include <iostream>

using namespace std;

void count(int x, int y, int len);

int r, c, cnt = 0;

int main() {
	int N;
	cin >> N >> r >> c;

	count(0, 0, 1<<N);
}

void count(int x, int y, int len) {
	if (x == r && y == c) {
		cout << cnt;
		return;
	}

	if (r < x + len && r >= x && c < y + len && c >= y) {
		count(x, y, len / 2);
		count(x, y+len/2, len / 2);
		count(x+len/2, y, len / 2);
		count(x+len/2, y+len/2, len / 2);
	}
	else cnt += len * len;
}