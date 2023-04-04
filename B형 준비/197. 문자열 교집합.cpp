#include <iostream>
#include <set>
#include <string>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int N, M; // 두 집합의 원소의 개수
        cin >> N >> M;

        set<string> first;

        for (int i = 0; i < N; i++) {
            string str;
            cin >> str;
            first.insert(str);
        }

        int ans = 0;
        for (int i = 0; i < M; i++) {
            string str;
            cin >> str;
            if(first.find(str) != first.end()) ans += 1;
        }

        cout << "#" << t << " " << ans << "\n";
    }
}