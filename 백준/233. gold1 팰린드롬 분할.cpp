#include <iostream>
#include <string>
#include <climits>
#include <algorithm>
#include <string.h>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string inp;
    cin >> inp;

    int N = inp.length();
    bool palin_dp[N][N]; // palin_dp[i][j] := i~j string이 palindrome인지 여부

    // 초기화(길이 1인 경우랑 2인 경우)
    for (int i = 0; i < N; i++) {
        memset(palin_dp[i], false, N);

        palin_dp[i][i] = true;

        if(i != N - 1 && inp[i] == inp[i + 1]){
            palin_dp[i][i + 1] = true;
        }
    }

    // palin_dp 채우기
    for (int len = 2; len < N; len++) { // substring 길이
        for (int start = 0; start + len < N; start++) { // 시작 위치
            if(inp[start] == inp[start + len] && palin_dp[start + 1][start + len - 1])
                palin_dp[start][start + len] = true;
        }
    }

    int dp[N]; // dp[i] := i번째까지 고려했을 때 최소 분할 개수
    for (int i = 0; i < N; i++) {
        if(palin_dp[0][i]) {
            dp[i] = 1;
            continue;
        }

        dp[i] = INT_MAX;
        for (int mid = 1; mid <= i; mid++) {
            if(palin_dp[mid][i])
                dp[i] = min(dp[i], dp[mid - 1] + 1);
        }
    }

    cout << dp[N - 1];
}