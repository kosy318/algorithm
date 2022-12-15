#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	int tc;
	cin >> tc;

	for (int t = 1; t <= tc; t++) {
		int answer = 0;
		string origin;
		cin >> origin;

		char bit = '0';

		for (char ch : origin) {
			if (bit != ch) {
				answer += 1;
				bit = ch;
			}
		}

		cout << "#" << t << " " << answer << endl;
	}
}