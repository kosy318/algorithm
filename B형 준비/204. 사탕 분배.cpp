// A와 B의 연산을 동일하게 만들 수 있다.
// 뭉뚱그려서 할 수 있다.
// A -> (A*2)%(A+B)
// B -> (B*2)%(A+B)

#include <iostream>

using namespace std;

long long solution(int num1, int num2, int cnt);
// 분할정복
int get_2_power(int cnt, int mod);

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for(int t=1; t<=T; t++){
        int num1, num2;
        cin >> num1 >> num2;

        int cnt;
        cin >> cnt; // 적용해야하는 횟수

        cout << "#" << t << " " << solution(num1, num2, cnt) << "\n";
    }
}

long long solution(int num1, int num2, int cnt){
    int sum = num1 + num2;
    int pow = get_2_power(cnt, sum);
    long long result1 = (pow * (long long) num1) % sum;
    long long result2 = (pow * (long long) num2) % sum;
    return result1 > result2 ? result2 : result1;
}

int get_2_power(int cnt, int mod){ // 2^cnt % mod
    long long res = 1;
    long long num = 2;
    while(cnt > 0){
        if(cnt % 2 == 1){
            res = (res * num) % mod;
        }
        num = (num * num) % mod;
        cnt /= 2;
    }
    return (int) res;
}