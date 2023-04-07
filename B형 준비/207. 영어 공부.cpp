#include <iostream>
#include <algorithm>

using namespace std;

int n; // 공부를 한 날
int p; // 해킹을 할 수 있는 기회
int* a;

int solve(){
    int ans = 0; // 내가 찾은 최장 슬트릭 길이
    for (int i = 0; i < n; i++) { // i := 공부를 시작한 날짜의 인덱스
        // a[i]에 공부를 시작한 상태

        int L=i, R = n-1, mid;
        while (L <= R) {
            mid = (L+R) / 2;
            int blank = (a[mid] - a[i] + 1) - (mid - i + 1); // 빈 날짜 개수
            if (blank > p) { // 불가능
                R = mid - 1;
            } else { // 가능
                L = mid + 1;

                // a[mid] - a[i] + 1 := mid부터 i까지 며칠?
                // p - blank := 이어붙인 다음 남은 해킹 개수
                ans = max(ans, (a[mid] - a[i] + 1) + (p - blank));
            }
        }
    }

    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int max_date = 1000001;
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> n >> p;
        a = new int[n];

        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        cout << "#" << t << " " << solve() << "\n";
    }
}