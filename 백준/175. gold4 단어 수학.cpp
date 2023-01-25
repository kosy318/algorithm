#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
	int N;
	cin >> N;

	vector<string> words(N);
	for (int i = 0; i < N; i++) {
		cin >> words[i];
	}

	// 알파벳 별로 분리
	// GCF -> G : G*100, C: C*10, F: F*1
	// ACDEB -> A: A*10000, C: C*1000, D: D*100, E: E*100, B: B*1
	// 알파벳에 정해넣는 숫자는 나중에 곱하면 된다. 곱해줄 숫자가 큰것에 큰 숫자를 넣어주면 되는 것임
	vector<int> alphabet(26);
	for (string str : words) {
		int cnt = 0;
		for (int i = str.length() - 1; i >= 0; i--) {
			alphabet[str[i] - 'A'] += (int)pow(10, cnt);
			cnt += 1;
		}
	}

	sort(alphabet.rbegin(), alphabet.rend());
	int result = 0;
	for (int i = 9; i >= 0; i--) {
		result += i * alphabet[9 - i];
	}
	cout << result;
}