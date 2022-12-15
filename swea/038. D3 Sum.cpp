// 열은 데이터를 받아오면서 구할 수 있다
// 행을 구하면서 최대값을 확인한다.
// 0,0에서 행과 열을 1씩 증가시키며 더한다.
// 0,99에서 행은 +1 열은 -1을하며 더한다.

#include <iostream>
#include <vector>

using namespace std;

int main() {
	int tc, num;
	// 계속 새로운 값을 "대입"할것이기 때문에 매번 벡터를 초기화 해줄 필요 없다.
	vector<vector<int>> vec(100, vector<int>(100, 0));
	for (int t = 0; t < 10; t++) {
		cin >> tc;
		int answer = 0;
		int temp = 0;
		for (int i = 0; i < 100; i++) {
			temp = 0;
			for (int j = 0; j < 100; j++) {
				cin >> num;
				vec[i][j] = num;
				temp += num;
			}
			if (answer < temp) answer = temp;
		}

		// column방향
		for (int j = 0; j < 100; j++) {
			temp = 0;
			for (int i = 0; i < 100; i++) {
				temp += vec[i][j];
			}
			if (answer < temp) answer = temp;
		}

		// 대각선 왼쪽위에서 오른쪽 아래
		temp = 0;
		int i = 0, j = 0;
		while (true) {
			temp += vec[i][j];
			i++; j++;
			if (i == 100) break;
		}
		if (answer < temp) answer = temp;

		// 대각선 오른쪽위에서 왼쪽 아래
		temp = 0;
		i = 0; j = 99;
		while (true) {
			temp += vec[i][j];
			i++; j--;
			if (i == 100) break;
		}
		if (answer < temp) answer = temp;

		cout << "#" << tc << " " << answer << endl;
	}
}