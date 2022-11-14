#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Delivery {
	int from;
	int to;
	int box;

	Delivery(int from, int to, int box) : from{ from }, to{ to }, box{ box }{}
};

bool comp(Delivery& d1, Delivery& d2) {
	if (d1.to < d2.to) return true;
	return false;
}

int main() {
	int N, C;
	cin >> N >> C;
	int M;
	cin >> M;

	vector<Delivery> info;
	for (int i = 0; i < M; i++) {
		int to, from, box;
		cin >> from >> to >> box;

		info.push_back(Delivery(from, to, box));
	}

	sort(info.begin(), info.end(), comp);

	/*for (auto i : info)
		cout <<i.from << " -> "<< i.to << endl;*/

	int answer = 0;
	vector<int> capacity(N + 1, 0);
	for (Delivery d : info) {
		int max = *max_element(capacity.begin() + d.from, capacity.begin() + d.to);
		/*cout << d.from << " -> " << d.to << endl;
		cout << max << endl;
		for (int i = 1; i <= N; i++)
			cout << capacity[i] << " ";
		cout << endl;*/

		int put = C - max;
		if (put > d.box) put = d.box;

		answer += put;
		for (int i = d.from; i < d.to; i++) {
			capacity[i] += put;
		}
	}

	cout << answer;
}