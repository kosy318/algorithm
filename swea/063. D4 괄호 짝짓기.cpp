#include <iostream>
#include <map>
#include <stack>
#include <string>

using namespace std;

int main() {
	map<char, char> pair = { {')', '('}, {']', '['}, {'}', '{'}, {'>', '<'} };
	for (int t = 1; t <= 10; t++) {
		stack<char> paren;

		int N;
		string str;
		cin >> N >> str;

		for (auto ch : str) {
			if (ch == ')' || ch == ']' || ch == '}' || ch == '>') {
				if (paren.top() == pair[ch]) paren.pop();
				else break;
			}
			else paren.push(ch);
		}

		if (!paren.empty()) cout << "#" << t << " 0\n";
		else cout << "#" << t << " 1\n";
	}
}
