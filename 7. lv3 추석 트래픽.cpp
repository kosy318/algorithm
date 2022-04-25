// https://jolly-note.tistory.com/30

#include <bits/stdc++.h>

using namespace std;

pair<long, long> time_difference(string s, int t){
    long t_sec = 0;

    istringstream iss(s);
    string buff;
    int i = 2;
    while(getline(iss, buff, ':')){
        buff.erase(remove(buff.begin(), buff.end(), '.'), buff.end());
        t_sec += pow(60, i)*stoi(buff);
        if(i==1) t_sec *= 1000;
        i--;
    }

    return {t_sec - t + 1, t_sec};
}

vector<pair<long, long>> logs;

int compute(long start, long end){
    int cnt = 0, idx = 0;
    while(true){
        long log_start = logs[idx].first;
        long log_end = logs[idx].second;
        if(end >= log_start && start <= log_end) {
            cnt++;
        }

        idx++;
        if(idx == logs.size()) break;
    }

    return cnt;
}

int solution(vector<string> lines) {

    for(string line : lines){
        istringstream iss(line);
        string date, s, t;
        iss >> date >> s >> t;
        t.pop_back();

        logs.push_back(time_difference(s, stof(t)*1000));
    }

    int answer = 0;
    for(int i=0; i<logs.size(); i++){
        long start = logs[i].first;
        long end = start + 999;

        int cnt = compute(start, end);
        if(answer < cnt) answer = cnt;

        start = logs[i].second;
        end = start + 999;

        cnt = compute(start, end);
        if(answer < cnt) answer = cnt;
    }

    return answer;
}
