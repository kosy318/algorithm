#include<iostream>
#include<vector>

using namespace std;

const int MOD = 1000000;

void decode(vector<int>& dp, const string& code);

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string code;
    cin >> code;

    // dp[i] := i번째 숫자까지 읽었을 때 경우의 수
    vector<int> dp(code.size() + 1, 0);

    decode(dp, code);

    cout << dp[code.size()];
}

void decode(vector<int>& dp, const string& code) {
    if(code[0] - '0' == 0) return; // 첫번째 문자가 0이면 decode 불가능
    dp[0] = dp[1] = 1; // 첫번째 숫자는 무조건 한개의 문자로만 decode 가능
    // dp[0]을 1로 초기화 하는 이유는 2번째 자리 숫자에서 두자리 숫자가 가능한 경우 dp[0]의 값을 가져와서 사용해야하기 때문임

    // 두번째 암호부터 확인
    for (int i = 2; i <= code.size(); i++) {
        if(code[i-1] - '0' != 0){ // i번째 문자가 0이 아니면
            dp[i] = dp[i-1]; // i번째 문자를 알파벳으로 변경해서 decode 가능한데, 경우의 수가 늘어나는 것이 아니라 이전까지 가능한 경우의 수와 동일하게됨
        }

        int num = (code[i-2] - '0')*10 + (code[i-1] - '0');
        ///////// 틀린 부분 : 10~26으로 비교해야하는데 1부터 비교함. 이렇게 하면 01,,, 09까지 들어가게 되는데 그러면 앞 조건이랑 다를것이 없음
        if(num >= 10 && num <= 26) { // 두자리 숫자가 알파벳으로 변경 가능한 경우
            dp[i] = (dp[i] + dp[i - 2]) % MOD;
        }
    }
}
