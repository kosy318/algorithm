#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
	int N, M;
	cin >> N >> M;

	vector<int> numsAcc(N + 1);

	for (int i = 1; i <= N; i++) {
		cin >> numsAcc[i];
		numsAcc[i] += numsAcc[i - 1];
	}

	string answer = "";
	for (int m = 0; m < M; m++) {
		int i, j;
		cin >> i >> j;

		answer += to_string(numsAcc[j] - numsAcc[i - 1]) + "\n";
	}
	cout << answer;
}
