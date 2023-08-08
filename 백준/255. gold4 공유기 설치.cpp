#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int N, C; // N := 집 개수, C:= 설치할 공유기 개수
vector<int> house;

void input() {
    cin >> N >> C;
    house = vector<int>(N);

    for(int i=0; i<N; i++){
        cin >> house[i];
    }

    sort(house.begin(), house.end());

    // [debug] sorting test
//    for(int i : house) cout << i << endl;
}

int binary_search(){
    int left = 1; // 집 여러개가 같은 좌표를 가지는 일은 없다
    int right = house[N-1] - house[0];

    while(true){
        int answer = right;
        int cnt = 1; // 첫번째 집 무조건 포함
        int mid = (left + right) / 2;
        int dis = 0;

        for(int i=1; i<N; i++){
            dis += house[i] - house[i-1];
            if(dis >= mid) {
                cnt += 1;
                answer = min(answer, dis);

                dis = 0;
            }

            // 시간초과 대응책 2 : 실패
            if(cnt < C && N - i - 1 < C - cnt) break; // 남은 공유기 개수보다 남은 집 개수가 적을 때
            // 공유기를 다 설치했는데, 이후 더 설치할 수 있는 집이 존재할 때
            else if(cnt == C && i < N - 1 && house[N-1] - house[i+1] >= mid) {
                cnt += 1;
                break;
            }
            // 공유기를 다 설치했는데, 이후 더 설치할 수 있는 집이 없을 때
            else if(cnt == C && i < N - 1 && house[N-1] - house[i+1] < mid){
                break;
            }
        }

        if(cnt < C) right = mid; // mid - 1일 경우 틀림
        else if(cnt > C) left = mid + 1;
        else return answer;
    }
}

int get_min_dis(){
    int answer = INT_MAX;

    for(int i=1; i<N; i++){
        answer = min(answer, house[i] - house[i-1]);
    }

    return answer;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // input 받기 + sorting
    input();

    if(N == C){ // 시간초과 대응책 1 : N과 C가 동일할 때, O(N)으로 처리하기위함 - 실패
        cout << get_min_dis();
    }
    else cout << binary_search();
}