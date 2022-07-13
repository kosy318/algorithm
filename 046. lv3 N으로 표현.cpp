#include <string>
#include <vector>
#include <set>

using namespace std;

int nnn(int N, int num){
    int result = N;
    for(int i=1; i<num; i++){
        result = result*10 + N;
    }
    return result;
}

int solution(int N, int number) {
    vector<set<int>> dp(9);

    for(int i=1; i<=8; i++){
        dp[i].insert(nnn(N, i)); // 숫자 i개 사용

        for(int x=1; x<=i; x++){
            for(int y=1; y<=i; y++){
                if(x+y > 8) break;

                for(int a: dp[x]){
                    for(int b: dp[y]){
                        if(a+b <= 32000) dp[x+y].insert(a+b);
                        if(a-b >= 1) dp[x+y].insert(a-b);
                        if(a*b <= 32000) dp[x+y].insert(a*b);
                        if(a/b >= 1) dp[x+y].insert(a/b);
                    }
                }
            }
        }
        for(int a: dp[i]){
            if(a == number) return i;
        }
    }
    return -1;
}
