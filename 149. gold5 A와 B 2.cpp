#include <iostream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

string start, target;

int compute(string str) {
	if (str.length() == target.length()) {
		if (str == target) return 1;
		return 0;
	}

	if (str[str.length()-1] == 'A' && compute(str.substr(0, str.length() - 1)) == 1) {
		return 1;
	}
	if (str[0] == 'B') {
		reverse(str.begin(), str.end());
		if (compute(str.substr(0, str.length() - 1)) == 1) {
			return 1;
		}
	}

	return 0;
}

int main() {
	cin >> target >> start;

	cout << compute(start);
}