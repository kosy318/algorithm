// https://jolly-note.tistory.com/58

#include <string>
#include <vector>

using namespace std;

int solution(vector<int> numbers) {
	int answer = 45;
	vector<int> elements(10);

	for (int num : numbers) {
		if (elements[num] == 0) {
			elements[num] = 1;
			answer -= num;
		}
	}
	return answer;
}