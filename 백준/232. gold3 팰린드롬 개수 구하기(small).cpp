#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string str;
    cin >> str;
    int N = str.length();

    int dp[N][N]; // dp[i][j] := i~j 구간 string의 palindrome이 되는 부분 수열의 개수

    for (int i = 0; i < N; i++) { // 한 글자랑 두 글자의 경우 초기화
        memset(dp[i], 0, N);

        dp[i][i] = 1; // 길이 1인 문자열은 1개
        if(i != N - 1){
            if(str[i] == str[i + 1]) {
                dp[i][i + 1] = 3; // aa인 경우 a, a, aa 3가지가 가능
            }
            else{
                dp[i][i + 1] = 2; // ab인 경우 a, b 2가지가 가능
            }
        }
    }

    for (int len = 2; len < N; len++) {
        for (int start = 0; start + len < N; start++) {
            if(str[start] == str[start + len]) {
                // 양 끝이 같은 경우, 양 끝이 없는 경우에 왼쪽이 추가된 경우와 오른족이 추가된 경우에서 palindrome이 되는 부분 수열의 수를 더한다
                // 이 때, 양 끝이 추가되지 않는 경우의 palindrome 부분 수열이 2번 더해지는데,
                // 그 중 한번을 양 끝이 추가된 경우로 치면 문제가 없기 때문에 따로 빼주지 않는다.
                // 1을 더해주는 이유는 양 끝 문자만 가져오면 그것도 palindrome이 되는데 그것을 추가해 준 것이다.
                dp[start][start + len] = dp[start][start + len - 1] + dp[start + 1][start + len] + 1;
            }
            else {
                // 비슷한 과정으로 양 끝이 같지 않기 때문에 두 번 더해진 부분 수열의 개수 중 하나를 빼줘야한다.
                dp[start][start+ len] = dp[start][start + len - 1] + dp[start + 1][start + len] - dp[start + 1][start + len - 1];
            }
        }
    }

    cout << dp[0][N - 1];
}