#include<iostream>
#include<cmath>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        long long x, y;
        cin >> x >> y;

        long long distance = y - x;
        int N = (int)sqrt(distance);
        distance -= N*N;

        cout << N*2 - 1 + ceil((double)distance / N) << '\n';
    }
}