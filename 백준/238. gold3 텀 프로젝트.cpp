#include <iostream>
#include <vector>

using namespace std;

const int MAX_NUM = 100000;

int N; // 학생 수
vector<int> selected; // 선택된 학생들의 번호(1이상)
vector<int> team; // 팀을 만들었는지 여부

int dfs(int start, int num){
//    cout << start << " " << num << endl;
    if(team[num] > MAX_NUM) return MAX_NUM + 1;
    if (start == num || team[num] == 0) {
        return num;
    }

    team[num] = 0; // 방문 체크

    team[num] = dfs(start, selected[num]);
    if(team[num] == num) return MAX_NUM + 1;

    return team[num];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T;
    cin >> T;
    while(T--) {
        cin >> N;

        // 초기화
        selected = vector<int>(N+1);
        team = vector<int>(N+1, -1);

        for (int i = 1; i <= N; i++) {
            cin >> selected[i];
        }

        int answer = 0;
        for (int i = 1; i <= N; i++) {
            if(team[i] >= 0) {
                answer += (team[i] == MAX_NUM + 1)? 1 : 0;
                continue;
            }
            team[i] = dfs(i, selected[i]);
            answer += (team[i] == MAX_NUM + 1)? 1 : 0;
//            cout << i << " : " << team[i] << endl;
        }

        cout << answer << endl;
    }
}