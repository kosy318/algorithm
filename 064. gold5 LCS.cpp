#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	string str1, str2;
	cin >> str1 >> str2;
	
	vector<vector<int>> count(str1.length() + 1, vector<int>(str2.length() + 1));

	for (int i = 1; i <= str1.length(); i++) {
		for (int j = 1; j <= str2.length(); j++) {
			if (str1[i - 1] == str2[j - 1]) count[i][j] = count[i-1][j-1]+1;
			else count[i][j] = max(count[i - 1][j], count[i][j - 1]);
		}
	}

	cout << count[str1.length()][str2.length()] << endl;
}