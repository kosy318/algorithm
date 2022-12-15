#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

struct Coord {
	int x, y;

	Coord(int x=0, int y=0) : x{ x }, y{ y }{}
};

bool isIn(int x, int y) {
	return (x >= 0 && y >= 0 && x < 100 && y < 100);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int dir_x[] = { -1, 1, 0, 0 };
	int dir_y[] = { 0, 0, -1, 1 };

	for (int t = 1; t <= 10; t++) {
		int tc;
		cin >> tc;

		vector<string> map(100);
		bool possible = false;
		Coord* start = new Coord();
		Coord* end = new Coord();

		for (int i = 0; i < 100; i++) {
			cin >> map[i];
			for(int j=0; j<100; j++)
				if (map[i][j] == '2') {
					start->x = i;
					start->y = j;
				} else if (map[i][j] == '3') {
					end->x = i;
					end->y = j;
				}
		}

		stack<Coord*> st;
		st.push(new Coord(start->x, start->y));
		while (!st.empty()) {
			Coord* top = st.top();
			st.pop();
			for (int i = 0; i < 4; i++) {
				int nx = top->x + dir_x[i], ny = top->y + dir_y[i];
				if (nx == end->x && ny == end->y) {
					possible = true;
					break;
				} else if (isIn(nx, ny)) {
					if (map[nx][ny] == '0') {
						st.push(new Coord(nx, ny));
						map[nx][ny] = '1';
					}
				}
			}
			if (possible) break;
		}

		cout << "#" << t << " " << possible << "\n";
	}


}