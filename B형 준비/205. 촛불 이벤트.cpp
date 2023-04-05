#include <iostream>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for(int t=1; t<=T; t++){
        long long N;
        cin >> N;

        long long L = 1; // 정답이 존재하는 가능성이 있는 왼쪽 끝
        long long R = 10000000000L; // 정답이 존재하는 가능성이 있는 오른쪽 끝
        long long res = 0; // 내가 찾은 최고의 정답
        while(L <= R){
            long long mid = (L+R) / 2;
            long long value = mid * (mid + 1) / 2;

            if(N >= value) { // * 가능한 케이스
                res = mid;   // 정답을 갱신
                L = mid + 1; // 오른쪽 절반에 대해 추가 탐색
            } else {         // * 불가능한 케이스
                R = mid - 1; // 왼쪽 절반에 대해 추가 탐색
            }
        }

        long long value = res * (res + 1) / 2;
        if(N != value) {
            res = -1;
        }

        cout << "#" << t << " " << res << "\n";
    }
}