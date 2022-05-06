#include <string>
#include <vector>
#include <algorithm> // next_permutation

using namespace std;

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, vector<string> data) {
    vector<char> kakao_friends = { 'A', 'C', 'F', 'J', 'M', 'N', 'R', 'T' };
    int cnt = 0;
    do {
        bool flag = true;
        for (auto d : data) {
            char f1 = d[0], f2 = d[2];
            char condition = d[3];
            int dist = d[4] - '0' + 1;

            int f1_idx = find(kakao_friends.begin(), kakao_friends.end(), f1) - kakao_friends.begin();
            int f2_idx = find(kakao_friends.begin(), kakao_friends.end(), f2) - kakao_friends.begin();

            switch (condition) {
            case '=':
                if (abs(f1_idx - f2_idx) != dist) flag = false;
                break;
            case '<':
                if (abs(f1_idx - f2_idx) >= dist) flag = false;
                break;
            case '>':
                if (abs(f1_idx - f2_idx) <= dist) flag = false;
                break;
            default:
                break;
            }
            if (!flag) break;
        }
        if (flag) cnt++;
    } while (next_permutation(kakao_friends.begin(), kakao_friends.end()));

    return cnt;
}