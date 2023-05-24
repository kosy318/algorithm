#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    int num[N];

    for(int i=0; i<N; i++){
        cin >> num[i];
    }

    // left_dp[i] := i번째 숫자를 포함한 왼쪽으로 연속한 숫자들의 합 중 최대(오른쪽은 포함 x)
    // right_dp[i] := i번째 숫자를 포함한 오른쪽으로 연속한 숫자들의 합 중 최대(왼족은 포함x)
    int left_dp[N], right_dp[N];

    // 제일 첫번째 숫자 초기화
    left_dp[0] = num[0];
    right_dp[N - 1] = num[N - 1];
    int max_value = max(left_dp[0], right_dp[N - 1]);

    // dp 초기화
    // 이전에 연속하던 것에 현재 숫자를 더한 것이 더 큰지, 아니면 그냥 현재 숫자 하나가 더 큰지 비교해서 입력
    for (int i = 1; i < N; i++) {
        left_dp[i] = max(left_dp[i - 1] + num[i], num[i]);
        right_dp[N - 1 - i] = max(right_dp[N - 1 - (i - 1)] + num[N - 1 - i], num[N - 1 - i]);

        // 하나를 제외하지 않았을 때 최대 값
        max_value = max(max_value, max(left_dp[i], right_dp[N - 1 - i]));
    }

    // 하나를 제외하고 최대값
    // 연속된 숫자 중 중간을 빼야하기 때문에 1부터 N-2만 제외해주면 된다.
    for (int i = 1; i < N - 1; i++) {
        // 제외한 숫자 왼쪽 숫자의 왼쪽으로 연속된 숫자의 최대합 +
        // 제외한 숫자 오른쪽 숫자의 오른쪽으로 연속된 숫자의 최대합
        max_value = max(max_value, left_dp[i - 1] + right_dp[i + 1]);
    }

    cout << max_value;
}