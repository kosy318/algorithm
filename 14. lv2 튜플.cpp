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

// map�� cnt ���� ǥ���ϴ� ���
vector<int> solution(string s) {
    vector<int> answer;
    map<int, int> cnt;

    smatch match;
    while(regex_search(s, match, regex("(\\d)+"))){
        int number = stoi(match.str());
        s = match.suffix().str();

        // �ʿ� �ش� ���� cnt�� ����
        cnt[number]++;
    }
    vector<pair<int, int>> cnt_vec(cnt.begin(), cnt.end());
    // ���� ���� ���ڰ� ���� ���� ��޵��� ��
    sort(cnt_vec.begin(), cnt_vec.end(), cmp);

    for(auto vec : cnt_vec)
        answer.push_back(vec.first);

    return answer;
}

// vector�� cnt���� ǥ���ϴ� ���
vector<int> solution(string s) {
    vector<int> answer;
    vector<int> cnt(100001, 0);
    vector<int> number; // � ���ڰ� ����ִ��� Ȯ���������

    smatch match;
    while(regex_search(s, match, regex("(\\d)+"))){
        int num = stoi(match.str());
        s = match.suffix().str();

        if(cnt[num]==0) number.push_back(num); // ó�� ���ڰ� �߰ߵ��� �� �߰����ָ� ��
        cnt[num]++;
    }
    vector<pair<int, int>> cnt_vec;
    // �� ������ cnt ���� pair�� ���� cnt_vec�� ������ְ� �������� ���� ����
    for(int n: number){
        cnt_vec.push_back({n, cnt[n]});
    }
    sort(cnt_vec.begin(), cnt_vec.end(), cmp);

    for(auto vec : cnt_vec)
        answer.push_back(vec.first);

    return answer;
}
*/
