// https://jolly-note.tistory.com/29?category=1025701

#include <bits/stdc++.h>

using namespace std;

vector<string> solution(vector<string> record) {
    vector<string> answer;
    map<string, string> id_nickname; // id �� �г��� ����
    queue<string> enter_leave; // enter/leave, id�� ������� ��

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
        string str = (op == "Enter")? "���� ���Խ��ϴ�." : "���� �������ϴ�.";

        string id = enter_leave.front();
        enter_leave.pop();

        answer.push_back(id_nickname[id] + str);
        if(enter_leave.size() == 0) break;
    }
    return answer;
}
