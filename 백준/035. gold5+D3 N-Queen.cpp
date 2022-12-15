// https://jolly-note.tistory.com/72

// 같은 행과 열에 하나씩 들어갈 수 있음
// 대각선인지만 확인하면됨. 같은 x좌표끼리의 차이와 y좌표끼리의 차이가 같으면 대각선에 존재
// 모든 행이 꽉찼으면 끝


#include<iostream>
#include<vector>

using namespace std;

int N, answer;
vector<int> chess(14); // 각 원소는 n번째 행의 어느 column에 chess가 놓여있는지를 나타내고있다.
vector<bool> columns(14, false);

void dfs(int row = 0) { // row번째 행에 넣을 차례
	if (row == N) {
		answer++;
		return;
	}
	for (int i = 0; i < N; i++) { // 어느 column에 넣을지
		// 같은 열에 없어야함
		if (columns[i]) continue;
		// 대각선에 없어야함
		bool conti = false;
		for (int j = 0; j < row; j++) { // row의 전 행들을 돌면서
			if (abs(row - j) == abs(i - chess[j])) conti = true;
		}
		if (conti) continue;
		chess[row] = i;
		columns[i] = true;
		dfs(row + 1);
		columns[i] = false;
	}
}

int main() {
	int tc;
	cin >> tc;
	for (int i = 0; i < tc; i++) {
		answer = 0;
		cin >> N;

		dfs();
		cout << "#" << i + 1 << " " << answer << endl;
	}
}