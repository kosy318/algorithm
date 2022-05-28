// https://jolly-note.tistory.com/74

// vector<string> 으로 받아오면됨
// row로 검사했다가 column방향으로 검사하면 됨
// 길이 1인 회문을 검사하라할때는 string 길이 *  vector 사이즈 하면됨

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	for (int tc = 0; tc < 10; tc++) {
		int N, answer = 0;
		string str;
		vector<string> vec;
		cin >> N;
		for (int i = 0; i < 8; i++) {
			cin >> str;
			vec.push_back(str);
		}

		// N==1 인경우
		if (N == 1) {
			cout << "#" << tc + 1 << " 64" << endl;
			continue;
		}

		// row
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				bool found = true;
				if (j + N - 1 >= 8) break;
				int start = j, end = j + N - 1;
				while (true) {
					if (start >= end) break;
					if (vec[i][start] != vec[i][end]) {
						found = false;
						break;
					}
					start++;
					end--;
				}
				if (found) answer++;
			}
		}

		// column
		for (int j = 0; j < 8; j++) {
			for (int i = 0; i < 8; i++) {
				bool found = true;
				if (i + N - 1 >= 8) break;
				int start = i, end = i + N - 1;
				while (true) {
					if (start >= end) break;
					if (vec[start][j] != vec[end][j]) {
						found = false;
						break;
					}
					start++;
					end--;
				}
				if (found) answer++;
			}
		}

		cout << "#" << tc + 1 << " " << answer << endl;
	}
}