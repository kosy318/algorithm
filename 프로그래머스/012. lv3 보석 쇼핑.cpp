// https://jolly-note.tistory.com/37?category=1025701

#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

vector<int> solution(vector<string> gems) {
    map<string, int> check;
    vector<int> pos;
    for(int i=0; i< gems.size(); i++){
        check[gems[i]] = 0;
        if(i+1 != gems.size() && gems[i] != gems[i+1]) pos.push_back(i);
        if(i == gems.size()-2) pos.push_back(i+1);
    }

    set<int> range = {1};
    vector<int> answer = {1, (int)gems.size()};
    if(check.size() == gems.size()) return answer;
    else if (check.size() == 1) return {1, 1};

    int cnt = 0;
    for(int p: pos){
        if(check[gems[p]] == 0) cnt++;
        else range.erase(check[gems[p]]);
        range.insert(p+1);
        check[gems[p]] = p+1;

        if(cnt == check.size() && answer[1]-answer[0] > *range.rbegin()-*range.begin())
            answer = {*range.begin(), *range.rbegin()};
    }
    return answer;
}

/*
// O(n^2) slow code
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

vector<int> solution(vector<string> gems) {
    map<string, int> check;
    vector<int> pos;
    for(int i=0; i< gems.size(); i++){
        check[gems[i]] = 0;
        if(i+1 != gems.size() && gems[i] != gems[i+1]) pos.push_back(i);
    }

    vector<int> answer = {1, (int)gems.size()};
    if(check.size() == gems.size()) return answer;
    else if (check.size() == 1) return {1, 1};

    for(int i=0; i<pos.size(); i++){
        int cnt = 0;
        for(int j=pos[i]; j<gems.size(); j++){
            if(check[gems[j]]==i){
                cnt++;
                check[gems[j]] += 1;
            }
            if(cnt == check.size() &&
               (answer[1] - answer[0] > j-pos[i] ||
                (answer[1]-answer[0] == j-pos[i] && pos[i] < answer[0]))){
                answer = {pos[i]+1, j+1};
                break;
            }else if(j == gems.size()-1 && cnt < check.size()) return answer;
        }
    }
    return answer;
}
*/
