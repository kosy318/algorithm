// https://jolly-note.tistory.com/29?category=1025701

#include <bits/stdc++.h>

using namespace std;

vector<string> solution(vector<string> record) {
    vector<string> answer;
    map<string, string> id_nickname; // id 별 닉네임 관리
    queue<string> enter_leave; // enter/leave, id가 순서대로 들어감

    for(string r: record){
        istringstream iss(r);
        string op, id, nickname;
        iss >> op >> id >> nickname; // spilt

        if(op == "Enter" || op == "Change") id_nickname[id] = nickname;
        if(op == "Enter" || op == "Leave"){
            enter_leave.push(op);
            enter_leave.push(id);
        }
    }

    while(1){
        string op = enter_leave.front();
        enter_leave.pop();
        string str = (op == "Enter")? "님이 들어왔습니다." : "님이 나갔습니다.";

        string id = enter_leave.front();
        enter_leave.pop();

        answer.push_back(id_nickname[id] + str);
        if(enter_leave.size() == 0) break;
    }
    return answer;
}
