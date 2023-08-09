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
    int answer = 0;

    while(left <= right){
        int cnt = 1; // 첫번째 집 무조건 포함
        int mid = (left + right) / 2;
        int set = house[0]; // 마지막으로 공유기가 설치된 장소

        for(int i=1; i<N; i++){
            if(house[i] - set >= mid) {
                cnt += 1;
                set = house[i]; // 마지막으로 공유기가 설치된 장소 갱신
            }
        }

        if(cnt < C) {
            right = mid - 1;
        }
        else if(cnt >= C) {
            left = mid + 1;
            answer = max(answer, mid);
        }
    }

    return answer;
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