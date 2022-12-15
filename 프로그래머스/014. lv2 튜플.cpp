// https://jolly-note.tistory.com/39?category=1025701

#include <string>
#include <vector>
#include <regex>

using namespace std;

vector<vector<int>> split(string str){
    smatch match;
    vector<vector<int>> res;
    while(regex_search(str, match, regex("(\\d|,)+"))){
        string matched = match.str();
        str = match.suffix().str();
        str = str.substr(2);

        smatch number;
        vector<int> inside;
        while(regex_search(matched, number, regex("\\d+"))){
            inside.push_back(stoi(number.str()));
            matched = number.suffix().str();
        }
        res.push_back(inside);
    }
    return res;
}

bool cmp(vector<int> v1, vector<int> v2){
    return v1.size() < v2.size();
}

vector<int> solution(string s) {
    vector<int> answer;
    vector<vector<int>> splited = split(s);
    sort(splited.begin(), splited.end(), cmp);

    for(auto vec : splited){
        for(auto v: vec){
            if(find(answer.begin(), answer.end(), v) == answer.end())answer.push_back(v);
        }
    }

    return answer;
}

/*
// another codes

#include <string>
#include <vector>
#include <regex>
#include <map>

using namespace std;

bool cmp(pair<int, int> m1, pair<int, int> m2){
    return m1.second > m2.second;
}

// map에 cnt 값을 표시하는 방법
vector<int> solution(string s) {
    vector<int> answer;
    map<int, int> cnt;

    smatch match;
    while(regex_search(s, match, regex("(\\d)+"))){
        int number = stoi(match.str());
        s = match.suffix().str();

        // 맵에 해당 값의 cnt를 증가
        cnt[number]++;
    }
    vector<pair<int, int>> cnt_vec(cnt.begin(), cnt.end());
    // 가장 앞의 숫자가 가장 많이 언급됐을 것
    sort(cnt_vec.begin(), cnt_vec.end(), cmp);

    for(auto vec : cnt_vec)
        answer.push_back(vec.first);

    return answer;
}

// vector에 cnt값을 표시하는 방법
vector<int> solution(string s) {
    vector<int> answer;
    vector<int> cnt(100001, 0);
    vector<int> number; // 어떤 숫자가 들어있는지 확인해줘야함

    smatch match;
    while(regex_search(s, match, regex("(\\d)+"))){
        int num = stoi(match.str());
        s = match.suffix().str();

        if(cnt[num]==0) number.push_back(num); // 처음 숫자가 발견됐을 때 추가해주면 됨
        cnt[num]++;
    }
    vector<pair<int, int>> cnt_vec;
    // 각 숫자의 cnt 값을 pair로 만들어서 cnt_vec로 만들어주고 나머지는 위와 동일
    for(int n: number){
        cnt_vec.push_back({n, cnt[n]});
    }
    sort(cnt_vec.begin(), cnt_vec.end(), cmp);

    for(auto vec : cnt_vec)
        answer.push_back(vec.first);

    return answer;
}
*/
