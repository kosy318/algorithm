#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Road {
	int from;
	int to;
	int cost;

	Road(int from, int to, int cost) : from{ from }, to { to }, cost{ cost }{}
};

vector<Road*> map;
int house, road;

int kruscal() {
	int answer = 0;
	vector<int> parent(house); // union find È°¿ë
	for (int i = 0; i < house; i++) {
		parent[i] = i;
	}
	for (Road* road : map) {
		if (parent[road->from] == parent[road->to]) continue;
		
		int parent_min = parent[road->from], parent_max = parent[road->to];
		if (parent[road->from] > parent[road->to]) {
			swap(parent_min, parent_max);
		}
		for (int& i : parent) {
			if (i == parent_max) i = parent_min;
		}
		answer += road->cost;
	}
	
	return answer;
}

bool comp(Road* r1, Road* r2) {
	return r1->cost < r2->cost;
}

int main() {
	while (cin >> house >> road) {
		if (house == 0) break;
		map.clear();

		int x, y, z, total = 0;
		for (int i = 0; i < road; i++) {
			cin >> x >> y >> z;
			total += z;
			map.push_back(new Road(x, y, z));
			map.push_back(new Road(y, x, z));
		}

		sort(map.begin(), map.end(), comp);

		cout << total - kruscal() << "\n";
	}
}