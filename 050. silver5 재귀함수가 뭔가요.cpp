#include <iostream>
#include <string>

using namespace std;

void chatbot(int cnt, string underbar);

int main() {
	int n;
	cin >> n;

	cout << "��� �� ��ǻ�Ͱ��а� �л��� ������ �������� ã�ư� ������." << endl;
	chatbot(n, "");
}

void chatbot(int cnt, string underbar) {
	if (cnt == 0) {
		cout << underbar << "\"����Լ��� ������?\"" << endl;
		cout << underbar << "\"����Լ��� �ڱ� �ڽ��� ȣ���ϴ� �Լ����\"" << endl;
	}
	else {
		cout << underbar << "\"����Լ��� ������?\"" << endl;
		cout << underbar << "\"�� ����. �������� �� �� ����⿡ �̼��� ��� ������ ����� ������ �־���." << endl;
		cout << underbar << "���� ������� ��� �� ���ο��� ������ ������ �߰�, ��� �����Ӱ� ����� �־���." << endl;
		cout << underbar << "���� ���� ��κ� �ǾҴٰ� �ϳ�. �׷��� ��� ��, �� ���ο��� �� ���� ã�ƿͼ� ������.\"" << endl;
		chatbot(cnt - 1, underbar + "____");
	}
	cout << underbar << "��� �亯�Ͽ���." << endl;
}