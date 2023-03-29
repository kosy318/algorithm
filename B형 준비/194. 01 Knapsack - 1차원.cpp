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
        vector<int> dp(K + 1, 0); // dp[j] := 총 무게 j를 맞추는 방법들 중에서, 내가 찾은 최고의 가치
        int w[101];
        int v[101];

        for (int i = 1; i <= N; i++) {
            cin >> w[i] >> v[i];
        }

        for (int i = 1; i <= N; i++) { // i번째 물건을 새롭게 고려 중
            // 0부터 차례대로 update하면 똑같은 물건을 여러번 넣는 가능성이 생겨버림
            // 무게가 큰것부터 차례대로 update
            for (int j = K; j >= 0; j--) { // 가방의 용량이 j인 상태를 고려 중
                // 지금 계산하고 싶은 상태: dp[j]

                // 1. i번 물건을 사용하지 않을 때
                dp[j] = dp[j];

                // 2. i번 물건을 사용할 때
                if (w[i] <= j) {
                    dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
                }
            }
        }

        cout << "#" << t << " " << dp[K] << "\n";
    }
}
