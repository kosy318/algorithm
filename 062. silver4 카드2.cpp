#include <iostream>
#include <queue>

using namespace std;

int main() {
	queue<int> card;
	int N;
	cin >> N;

	for (int i = 1; i <= N; i++)
		card.push(i);

	while (card.size() > 1) {
		card.pop();
		int nb = card.front();
		card.pop();
		card.push(nb);
	}

	cout << card.front() << endl;
}