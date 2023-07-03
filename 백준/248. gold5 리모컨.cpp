#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>

using namespace std;

bool button[10]; // button[i] == true : i버튼은 고장나지 않음

bool check(string str){
    bool is_possible = true;
    for (char& ch: str) {
        if(!button[ch - '0']){
            is_possible = false;
            break;
        }
    }

    return is_possible;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int target; // 이동하고자 하는 채널
    int cur = 100;

    cin >> target;

    int M; // 고장난 버튼의 개수
    cin >> M;

    memset(button, true, 10);
    for (int i = 0; i < M; i++) {
        int num;
        cin >> num;
        button[num] = false;
    }

    // answer 초기화
    int answer = abs(target - cur);

    if (check(to_string(target))) {
        answer = min((int)to_string(target).length(), answer);
    }
    else{
        // 아래로 찾기
        int num = target;
        for (int cnt = 1; cnt + to_string(num).length() < answer; cnt++) {
            num -= 1;
            if(num < 0) break;
            if(check(to_string(num))) {
                answer = cnt + to_string(num).length();
                break;
            }
        }

        // 위로 찾기
        ////////////// 틀린 부분 : cnt가 answer보다 아래지만 + to_string(num).length를 하기 때문에 기존 answer보다 커질 수 있음 주의
        num = target;
        for (int cnt = 1; cnt + to_string(num).length() < answer; cnt++) {
            num += 1;
            if(check(to_string(num))) {
                answer = cnt + to_string(num).length();
                break;
            }
        }
    }


    cout << answer;
}