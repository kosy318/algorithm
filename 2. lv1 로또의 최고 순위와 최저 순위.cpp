// https://jolly-note.tistory.com/25?category=1025701

#include <bits/stdc++.h>

using namespace std;

vector<int> solution(vector<int> lottos, vector<int> win_nums) {
    sort(lottos.begin(), lottos.end());
    sort(win_nums.begin(), win_nums.end());

    int idx = 0, cnt = 0, same = 0;
    for(int i=0; i<6; i++){
        if(lottos[i] == 0){
            cnt++;
            continue;
        }
        while(lottos[i] > win_nums[idx])
            idx++;

        if(lottos[i] == win_nums[idx])
            same++;
    }

    vector<int> answer;
    answer.push_back(same == 0 && cnt == 0 ? 6 : 7-(same+cnt));
    answer.push_back(same == 0? 6 : 7-same);
    return answer;
}
