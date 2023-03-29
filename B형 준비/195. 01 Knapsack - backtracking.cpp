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
        // come[i][j] := 1; i번 물건을 안쓰는 것이 더 좋았다.
        // come[i][j] := 2; i번 물건을 쓰는 것이 더 좋았다.
        vector<vector<int>> come(N + 1, vector<int>(K + 1, 0));
        int w[101];
        int v[101];

        for (int i = 1; i <= N; i++) {
            cin >> w[i] >> v[i];
        }

        for (int i = 1; i <= N; i++) { // i번째 물건을 새롭게 고려 중
            for (int j = 0; j <= K; j++) { // 가방의 용량이 j인 상태를 고려 중
                // 지금 계산하고 싶은 상태: dp[i][j]

                // 1. i번 물건을 사용하지 않을 때
                dp[i][j] = dp[i-1][j];
                come[i][j] = 1;

                // 2. i번 물건을 사용할 때
                if (w[i] <= j) {
                    // 가치가 더 좋으면 선택
                    if (dp[i][j] < dp[i - 1][j - w[i]] + v[i]){
                        dp[i][j] = dp[i - 1][j - w[i]] + v[i];
                        come[i][j] = 2;
                    }
                }
            }
        }

        int used[N + 1]; // used[i] := i번 물건이 사용되었는가?
        int j = K; // 현재 가방 용량

        // N번 물건부터 역추적
        for (int i = N; i >= 1; i--) {
            // 현재 j만큼의 용량을 쓴 상태
            if (come[i][j] == 1) {
                // i번 물건을 안쓰는게 더 좋았다.
                used[i] = 0;
            } else {
                // i번 물건을 쓰는게 더 좋았다.
                used[i] = 1;
                j -= w[i]; // 썼으니까 가방 용량에서 제외
            }
        }

        for (int i = 1; i <= N; i++) {
            cout << i << "번 물건 사용 : " << used[i] << "\n";
        }

        cout << "#" << t << " " << dp[N][K] << "\n";
    }
}
