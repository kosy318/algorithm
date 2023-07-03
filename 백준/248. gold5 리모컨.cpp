#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>

using namespace std;

bool button[10]; // button[i] == true : i��ư�� ���峪�� ����

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

    int target; // �̵��ϰ��� �ϴ� ä��
    int cur = 100;

    cin >> target;

    int M; // ���峭 ��ư�� ����
    cin >> M;

    memset(button, true, 10);
    for (int i = 0; i < M; i++) {
        int num;
        cin >> num;
        button[num] = false;
    }

    // answer �ʱ�ȭ
    int answer = abs(target - cur);

    if (check(to_string(target))) {
        answer = min((int)to_string(target).length(), answer);
    }
    else{
        // �Ʒ��� ã��
        int num = target;
        for (int cnt = 1; cnt + to_string(num).length() < answer; cnt++) {
            num -= 1;
            if(num < 0) break;
            if(check(to_string(num))) {
                answer = cnt + to_string(num).length();
                break;
            }
        }

        // ���� ã��
        ////////////// Ʋ�� �κ� : cnt�� answer���� �Ʒ����� + to_string(num).length�� �ϱ� ������ ���� answer���� Ŀ�� �� ���� ����
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