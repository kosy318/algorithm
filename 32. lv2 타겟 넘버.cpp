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

int solution(vector<int> numbers, int target) {
	dfs(numbers, target, 0, 0);

	return answer;
}