#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    int K;

    int T;
    cin >> T;

    // O(NK)
    for (int t = 1; t <= T; t++) {
        cin >> N >> K;

        // 초기화
        vector<vector<int>> dp(N + 1, vector<int>(K + 1, 0));
        int w[101];
        int v[101];

        for (int i = 1; i <= N; i++) {
            cin >> w[i] >> v[i];
        }

        for (int i = 1; i <= N; i++) { // i번째 물건을 새롭게 고려 중
            for (int j = 0; j <= K; j++) { // 가방의 용량이 j인 상태를 고려 중
                // 지금 계산하고 싶은 상태: dp[i][j]

                // 1. 1번 물건을 사용하지 않을 때
                dp[i][j] = dp[i-1][j];

                // 2. 1번 물건을 사용할 때
                if (w[i] <= j) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - w[i]] + v[i]);
                }
            }
        }

        cout << "#" << t << " " << dp[N][K] << "\n";
    }
}
