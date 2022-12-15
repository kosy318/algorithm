// https://jolly-note.tistory.com/53?category=1025701

#include <iostream>

using namespace std;

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		int result = 0;
		int num;
		for (int j = 0; j < 10; j++) {
			cin >> num;
			if (num % 2 == 1) {
				result += num;
			}
		}
		cout << "#" << i + 1 << " " << result << endl;
	}
}