// https://jolly-note.tistory.com/59

#include <string>
#include <vector>

// 11 42
// 12 44
// 13 111
// 14 112
// 15 114

using namespace std;

vector<string> one_two_four = { "", "1", "2", "4" };

string solution(int n) {
	string answer = "";
	int quotient = n, remainder = n % 3;
	do {
		remainder = quotient % 3;
		quotient = quotient / 3;
		if (remainder == 0) {
			quotient -= 1;
			remainder = 3;
		}
		answer = one_two_four[remainder] + answer;
		if (quotient <= 3) answer = one_two_four[quotient] + answer;
	} while (quotient > 3);

	return answer;
}