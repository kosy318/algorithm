#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main() {
	string str;
	cin >> str;

	stack<char> op;
	for (auto ch : str) {
		switch (ch) {
		case '+':
		case '-':
			while (!op.empty() && op.top() != '(') { // 같은 우선순위면 앞에것이 먼저임
				cout << op.top();
				op.pop();
			}
			op.push(ch); // 지금 들어온건 다음 알파벳이 나온 다음에 빠져야함
			break;
		case '*':
		case '/':
			while (!op.empty() && (op.top() == '*' || op.top() == '/')) { // 같은 우선순위면 앞에것이 먼저임
				cout << op.top();
				op.pop();
			}
			op.push(ch); // 지금 들어온건 다음 알파벳이 나온 다음에 빠져야함
			break;
		case '(':
			op.push(ch);
			break;
		case ')':
			while (op.top() != '(') {
				cout << op.top();
				op.pop();
			}
			op.pop(); // '(' 없앰
			break;
		default: // 알파벳
			cout << ch;
			break;
		}
	}

	char top_op;
	while (!op.empty()) {
		cout << op.top();
		op.pop();
	}
}