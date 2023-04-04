#include <iostream>
#include <string>

using namespace std;

const int EXPONENT1 = 31;
const int EXPONENT2 = 37;
const int EXPONENT3 = 41;

int hash_value(int value, int power){
    return value * power;
}

int get_count(const string& str, const string& pattern){
    int count = 0;

    int string_length = str.length();
    int pattern_length = pattern.length();

    int string_hash1 = 0;
    int pattern_hash1 = 0;

    int string_hash2 = 0;
    int pattern_hash2 = 0;

    int string_hash3 = 0;
    int pattern_hash3 = 0;

    int power1 = 1;
    int power2 = 1;
    int power3 = 1;

    for (int i = 0; i <= string_length - pattern_length; i++) { // window의 시작 위치
        // string[i ... i+patternLength -1] 이 pattern과 같은 지 확인
        if (i == 0) { // 최초
            for (int j = 0; j < pattern_length; j++) {
                string_hash1 += hash_value(str[pattern_length - 1 - j], power1);
                pattern_hash1 += hash_value(pattern[pattern_length - 1 - j], power1);

                string_hash2 += hash_value(str[pattern_length - 1 - j], power2);
                pattern_hash2 += hash_value(pattern[pattern_length - 1 - j], power2);

                string_hash3 += hash_value(str[pattern_length - 1 - j], power3);
                pattern_hash3 += hash_value(pattern[pattern_length - 1 - j], power3);

                if (j < pattern_length - 1) {
                    power1 *= EXPONENT1;
                    power2 *= EXPONENT2;
                    power3 *= EXPONENT3;
                }
            }
        } else { // 오른쪽으로 이동중
            string_hash1 = EXPONENT1 * (string_hash1 - hash_value(str[i - 1], power1)) + str[pattern_length - 1 + i];
            string_hash2 = EXPONENT2 * (string_hash2 - hash_value(str[i - 1], power2)) + str[pattern_length - 1 + i];
            string_hash3 = EXPONENT3 * (string_hash3 - hash_value(str[i - 1], power3)) + str[pattern_length - 1 + i];
        }

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