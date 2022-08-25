## algorithm
Studying algorithms by myself.

explanation(KOREAN) : https://jolly-note.tistory.com/category/coding/algorithm


```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> gate;
vector<vector<int>> people;
vector<int> numbers = { 0,1,2 };
vector<bool> is_selected;
int answer = 0;

void perm(int cnt) {
	if (cnt == 3) return;
	for (int i = 0; i < 3; i++) {
		if (is_selected[i]) {
			calc();
			continue;
		}
		is_selected[i] = true;
		numbers[cnt] = i;
		perm(cnt + 1);
		is_selected[i] = false;
	}
}

void calc() {
	int result = 0;

	for (int n : numbers) {

	}

	answer = min(answer, result);
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int tc;
	cin >> tc;

	for (int t = 1; t <= tc; t++) {
		answer = 0;
		int N;
		cin >> N;

		gate = vector<vector<int>>(3, vector<int>(N+1));
		people.clear();
		
		for (int i = 0; i < 3; i++) {
			int cur, nb;
			cin >> cur >> nb;
			people.push_back({ cur, nb });
		}

		for (int g = 0; g < 3; g++) {
			for (int i = 1; i <= N; i++) {
				gate[g][i] = abs(people[g][0] - i);
			}
		}

		cout << "#" << t << " " << answer << "\n";
	}
}
```
