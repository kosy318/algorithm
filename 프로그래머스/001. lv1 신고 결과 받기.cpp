// https://jolly-note.tistory.com/23?category=1025701

#include <bits/stdc++.h>

using namespace std;

// string split
vector<string> split(string str){
    istringstream iss(str);
    string buff;

    vector<string> result;

    while(getline(iss, buff, ' ')){
        result.push_back(buff);
    }
    return result;
}

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    unordered_map<string, int> id_map;
    for(int i=0; i<id_list.size(); i++)
        id_map.insert(pair<string, int>(id_list[i], 0));

    map<string, set<string>> cnt; // 신고한 유저들의 set
    for(string ids: report){
        vector<string> id = split(ids); // split
        cnt[id[1]].insert(id[0]);
    }

    for(int i=0; i<id_list.size(); i++){
        if(cnt[id_list[i]].size() >= k){
            for(string id: cnt[id_list[i]]){
                id_map[id]++;
            }
        }
    }

    vector<int> answer;
    for(int i=0; i<id_list.size(); i++){
        answer.push_back(id_map[id_list[i]]);
    }

    return answer;
}
