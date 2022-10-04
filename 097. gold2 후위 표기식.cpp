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
			while (!op.empty() && op.top() != '(') { // ���� �켱������ �տ����� ������
				cout << op.top();
				op.pop();
			}
			op.push(ch); // ���� ���°� ���� ���ĺ��� ���� ������ ��������
			break;
		case '*':
		case '/':
			while (!op.empty() && (op.top() == '*' || op.top() == '/')) { // ���� �켱������ �տ����� ������
				cout << op.top();
				op.pop();
			}
			op.push(ch); // ���� ���°� ���� ���ĺ��� ���� ������ ��������
			break;
		case '(':
			op.push(ch);
			break;
		case ')':
			while (op.top() != '(') {
				cout << op.top();
				op.pop();
			}
			op.pop(); // '(' ����
			break;
		default: // ���ĺ�
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