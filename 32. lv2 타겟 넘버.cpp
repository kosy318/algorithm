// https://jolly-note.tistory.com/69

#include <vector>

using namespace std;

int answer = 0;
void dfs(vector<int>& numbers, int& target, int idx, int num) {
	if (idx + 1 == numbers.size() + 1) {
		if (num == target) answer++;
		return;
	}
	dfs(numbers, target, idx + 1, num + (-1)*numbers[idx]);
	dfs(numbers, target, idx + 1, num + numbers[idx]);
}

void bfs(vector<int>& numbers, int& target) {
	queue<pair<int, int>> que;
	que.push({ numbers[0], 1 });
	que.push({ (-1)*numbers[0], 1 });

	while (!que.empty()) {
		auto[num, idx] = que.front(); que.pop();
		if (idx == numbers.size()) {
			if (num == target) answer++;
			continue;
		}
		que.push({ num + numbers[idx], idx + 1 });
		que.push({ num + (-1)*numbers[idx], idx + 1 });
	}
}

int solution(vector<int> numbers, int target) {
	dfs(numbers, target, 0, 0);
	// bfs(numbers, target);

	return answer;
}