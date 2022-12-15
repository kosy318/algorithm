https://jolly-note.tistory.com/79

#include <string>
#include <vector>

using namespace std;

int solution(int n, vector<int> lost, vector<int> reserve) {
    int answer = 0;

    vector<int> lost_chk(n+1, 0);
    for(int l: lost)
        lost_chk[l] = 1;

    vector<int> reserve_chk(n+1, 0);
    for(int r: reserve){
        if(lost_chk[r] == 1){
            lost_chk[r] = 0;
            continue;
        }
        reserve_chk[r] = 1;
    }

    bool repeat = true;
    vector<bool> both_side;
    while(repeat){
        both_side = vector<bool>(n+1, false);
        repeat = false;
        for(int i=1; i<=n; i++){
            if(lost_chk[i] == 0) continue;

            if(reserve_chk[i-1] == 1 && reserve_chk[i+1] == 1){
                both_side[i] = true;
            }else if(reserve_chk[i-1] == 1){
                reserve_chk[i-1] = 0;
                lost_chk[i] = 0;
                repeat = true;
            }else if(reserve_chk[i+1] == 1){
                reserve_chk[i+1] = 0;
                lost_chk[i] = 0;
                repeat = true;
            }
        }
    }

    for(int i=1; i<=n; i++){
        if(lost_chk[i] == 0) answer += 1;
        else if(both_side[i]) answer += 1;
    }

    return answer;
}
