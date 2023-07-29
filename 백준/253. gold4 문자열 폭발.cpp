#include <iostream>
#include <string>
#include <deque>

using namespace std;

string inp, bomb;
deque<pair<char, int>> inp_que;

void pop_bomb();

// ���� ���ڿ��� ���� ���ڸ� �� �� �̻� �������� �ʴ´� -> ���� ���ڿ� �� ���� ��ĥ ���� ����.
void find_bomb(){
    int idx = 0;
    for (char ch: inp) {
        if(bomb[0] == ch) idx = 1;
        else if(bomb[idx] == ch) idx += 1;
        else idx = 0;

        inp_que.emplace_back(ch, idx);

        if (idx == bomb.size()) {
            pop_bomb();
            if(!inp_que.empty()) idx = inp_que.back().second;
            else idx = 0;
        }
    }
}

void pop_bomb() {
    for (int i = 0; i < bomb.size(); i++) {
        inp_que.pop_back();
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> inp >> bomb;

    find_bomb();

    if(inp_que.empty()) cout << "FRULA";
    else {
        while(!inp_que.empty()){
            cout << inp_que.front().first;
            inp_que.pop_front();
        }
    }
}