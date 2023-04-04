#include <iostream>
#include <string>

using namespace std;

const int EXPONENT1 = 31;
const int EXPONENT2 = 37;
const int EXPONENT3 = 41;

// 주어진 value와 power를 사용하여 hash 값을 계산하는 함수
int hash_value(int value, int power){
    return value * power;
}

// 주어진 문자열에서 패턴이 등장하는 횟수를 구하는 함수
int get_count(const string& str, const string& pattern){
    int count = 0;

    int string_length = str.length(); // 문자열의 길이
    int pattern_length = pattern.length(); // 패턴의 길이

    int string_hash1 = 0;
    int pattern_hash1 = 0;

    int string_hash2 = 0;
    int pattern_hash2 = 0;

    int string_hash3 = 0;
    int pattern_hash3 = 0;

    int power1 = 1;
    int power2 = 1;
    int power3 = 1;

	// 문자열을 처음부터 끝까지 탐색하면서 패턴이 있는지 확인
    for (int i = 0; i <= string_length - pattern_length; i++) { // window의 시작 위치
        // string[i ... i+patternLength -1] 이 pattern과 같은 지 확인
        if (i == 0) { // 최초
            for (int j = 0; j < pattern_length; j++) {
				// 첫번째 substring에 대한 hash값과 패턴의 hash값 계산
                string_hash1 += hash_value(str[pattern_length - 1 - j], power1);
                pattern_hash1 += hash_value(pattern[pattern_length - 1 - j], power1);

				// 두번째 substring에 대한 hash값과 패턴의 hash값 계산
                string_hash2 += hash_value(str[pattern_length - 1 - j], power2);
                pattern_hash2 += hash_value(pattern[pattern_length - 1 - j], power2);

				// 세번째 substring에 대한 hash값과 패턴의 hash값 계산
                string_hash3 += hash_value(str[pattern_length - 1 - j], power3);
                pattern_hash3 += hash_value(pattern[pattern_length - 1 - j], power3);

				// 다음 substring을 계산하기 위해 exponent 값을 증가시킴
                if (j < pattern_length - 1) {
                    power1 *= EXPONENT1;
                    power2 *= EXPONENT2;
                    power3 *= EXPONENT3;
                }
            }
        } else { // 오른쪽으로 이동중
			// 이미 계산된 hash 값을 활용해 오른쪽으로 이동할 때마다 hash 값을 다시 계산한다.
			// 이때, 현재 위치의 문자를 더하고 이전 위치의 문자를 빼준다.
			// hash 값을 갱신할 때, 기존 hash 값을 사용해 계산하는 것이 더 효율적이다.
			// 이전에 계산된 hash 값에서 빼주고, 오른쪽으로 한 칸 이동한 후 새로운 문자에 대해 곱해준다.
			// 따라서 power 값을 이전 것에 곱해준다.
            string_hash1 = EXPONENT1 * (string_hash1 - hash_value(str[i - 1], power1)) + str[pattern_length - 1 + i];
            string_hash2 = EXPONENT2 * (string_hash2 - hash_value(str[i - 1], power2)) + str[pattern_length - 1 + i];
            string_hash3 = EXPONENT3 * (string_hash3 - hash_value(str[i - 1], power3)) + str[pattern_length - 1 + i];
        }

		// 일치하는 부분이 있으면 count 값을 증가시킨다.
        if(string_hash1 == pattern_hash1 && string_hash2 == pattern_hash2 && string_hash3 == pattern_hash3){
            count += 1;
        }
    }

    return count;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        string B, S;

        cin >> B >> S;

        cout << "#" << t << " " << get_count(B, S) << "\n";
    }
}