#include <iostream>
#include <queue>

using namespace std;

struct Point {
	int x, y;
	Point* prev;
	Point* next;

	Point(int x = 0, int y = 0, Point* prev = nullptr, Point* next = nullptr) : x{ x }, y{ y }, prev{ prev }, next{ next }{}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int tc;
	cin >> tc;
	for (int t = 0; t < tc; t++) {
		int n;
		cin >> n;
		bool possible = false;

		queue<Point> que;
		Point head;

		int x, y;
		cin >> x >> y; // home
		que.push(Point(x, y));

		Point* stores = new Point();
		Point* start = stores;

		for (int i = 1; i <= n; i++) { // stores
			cin >> x >>y;
			stores->next = new Point(x, y, stores);
			stores = stores->next;
		}

		Point festival;
		cin >> festival.x >> festival.y;

		while (!que.empty()) {
			Point cur = que.front(); que.pop();
			if ((abs(cur.x - festival.x) + abs(cur.y - festival.y)) <= 1000) {
				possible = true;
				break;
			}

			auto store = start;
			while (store != nullptr) {
				if ((abs(cur.x - store->x) + abs(cur.y - store->y)) <= 1000) {
					que.push(*store);

					if(store->prev != nullptr) (store->prev)->next = store->next;
					else start = store->next;
					if(store->next != nullptr) (store->next)->prev = store->prev;
				}
				store = store->next;
			}
		}

		(possible) ? cout << "happy\n" : cout << "sad\n";
	}
}