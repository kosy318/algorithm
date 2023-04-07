#include <iostream>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int N;
        long long M; // 한 가방에 필요한 사탕의 개수
        cin >> N >> M;

        long long candy[N];
        long long max = -1; // 각 종류의 캔디중 가장 많은 캔디를 가지고 있는 값의 최대
        for (int i = 0; i < N; i++) {
            cin >> candy[i];
            if(max < candy[i]) max = candy[i];
        }

        long long low = 1L;
        long long high = max;
        long long ans = 0;
        while (low <= high) {
            long long mid = (low + high) / 2;
            // 가방을 mid개 만큼 만들 것이라고 결정했다.

            // 각 가방에 최대 몇 개의 사탕을 넣을 수 있는 지
            long long sum = 0L;
            for (int i = 0; i < N; i++) {
                sum += (candy[i] / mid);
            }
            if (sum < M) {
                high = mid - 1;
            } else {
                ans = mid;
                low = mid + 1;
            }
        }
        cout<< "#" << t << " " << ans << "\n";
    }
}