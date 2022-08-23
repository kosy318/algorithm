## algorithm
Studying algorithms by myself.

explanation(KOREAN) : https://jolly-note.tistory.com/category/coding/algorithm

```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
	int N;
	cin >> N;
	vector<int> numbers(N+1);
	for (int i = 1; i <= N; i++)
		cin >> numbers[i];

	vector<vector<bool>> is_palin(N+1, vector<bool>(N+1));
	for (int i = 1; i <= N; i++) {
		is_palin[i][i] = true;
		if (i + 1 <= N && numbers[i] == numbers[i + 1]) {
			is_palin[i][i + 1] = true;
		}
	}

	for(int i=1; i<=N; i++)
		for (int j = i + 2; j <= N; j++) {
			if (numbers[i] == numbers[j]) {
				is_palin[i][j] = is_palin[i + 1][j - 1];
			}
		}

	int M;
	cin >> M;
	for (int i = 0; i < M; i++) {
		int x, y;
		cin >> x >> y;
		cout << is_palin[x][y] << "\n";
	}
}
```
