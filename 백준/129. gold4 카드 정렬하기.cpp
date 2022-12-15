#include <iostream>
#include <queue>

using namespace std;

int main() {
	int N;
	cin >> N;

	priority_queue<int, vector<int>, greater<int>> card;
	int num;
	for (int i = 0; i < N; i++) {
		cin >> num;
		card.push(num);
	}

	int answer = 0;
	while (card.size() > 1) {
		int num1 = card.top(); card.pop();
		int num2 = card.top(); card.pop();

		answer += num1 + num2;
		card.push(num1 + num2);
	}

	cout << answer;
}