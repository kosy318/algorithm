#include <iostream>
#include <string>

using namespace std;

bool is_possible(string str){
	int size = str.size();
	if (size % 2 == 0) return false;
	while (str.size() != 1) {
		int i = size - 1;
		int j = 0;
		while(i > size / 2 && j < size / 2){
			if (str[i] == str[j]) return false;

			i--; j++;
		}
		str = str.substr(0, size/2);
		size = str.size();
	}
	return true;
}

int main() {
	int tc;
	cin >> tc;
	for (int t = 1; t <= tc; t++) {
		string inp;
		cin >> inp;

		if (is_possible(inp)) cout << "YES\n";
		else cout << "NO\n";
	}
}