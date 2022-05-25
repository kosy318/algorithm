// https://jolly-note.tistory.com/70

#include <string>
#include <vector>

using namespace std;

void dfs(vector<vector<int>>& computers, int i) {
	computers[i][i] = 0;

	for (int k = 0; k < computers.size(); k++) {
		if (computers[i][k] == 1 && computers[k][k] == 1) dfs(computers, k);
	}
}

int solution(int n, vector<vector<int>> computers) {
	int answer = 0;

	for (int i = 0; i < n; i++) {
		if (computers[i][i] == 1) {
			dfs(computers, i);
			answer++;
		}
	}

	return answer;
}