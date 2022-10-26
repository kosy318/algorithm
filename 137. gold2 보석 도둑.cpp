#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct Jewelry {
	int weight;
	int price;

	Jewelry(int weight, int price) :weight{ weight }, price{ price }{}

	bool operator <(const Jewelry j) const {
		if (j.weight > weight) return true;
		else return false;
	}
};

int main() {
	int N, K;
	cin >> N >> K;

	vector<Jewelry> jewelries;
	for (int i = 0; i < N; i++) {
		int weight, price;
		cin >> weight >> price;
		jewelries.push_back(Jewelry(weight, price));
	}

	vector<int> bag(K);
	for (int i = 0; i < K; i++) {
		cin >> bag[i];
	}

	sort(jewelries.begin(), jewelries.end());
	sort(bag.begin(), bag.end());

	int idx = 0;
	long long answer = 0;
	priority_queue<int> que;
	for (int i = 0; i < K; i++) {
		while (idx < N && jewelries[idx].weight <= bag[i]) {
			que.push(jewelries[idx].price);
			idx++;
		}

		if (!que.empty()) {
			answer += que.top();
			que.pop();
		}
	}

	cout << answer;
}