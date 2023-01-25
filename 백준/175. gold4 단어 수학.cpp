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

	// ���ĺ� ���� �и�
	// GCF -> G : G*100, C: C*10, F: F*1
	// ACDEB -> A: A*10000, C: C*1000, D: D*100, E: E*100, B: B*1
	// ���ĺ��� ���سִ� ���ڴ� ���߿� ���ϸ� �ȴ�. ������ ���ڰ� ū�Ϳ� ū ���ڸ� �־��ָ� �Ǵ� ����
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