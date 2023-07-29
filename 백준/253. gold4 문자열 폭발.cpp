#include <iostream>
#include <string>
#include <list>

using namespace std;

string inp, bomb;
list<char> inp_list;

// 폭발 문자열은 같은 문자를 두 개 이상 포함하지 않는다 -> 폭발 문자열 두 개가 겹칠 일이 없다.
bool find_bomb(){
    bool found = false;

    list<char>::iterator start_iter;
    int idx = 0;
    int inp_list_idx = 0;
    for(auto iter = inp_list.begin(); iter != inp_list.end(); iter++){
        if(idx == bomb.size()){
            inp_list.erase(start_iter, iter);
            idx = 0;
            found = true;
        }

        if(*iter == bomb[0]) {
            start_iter = iter;
            idx = 1;
        } else if(*iter == bomb[idx]) {
            idx += 1;
        } else {
            idx = 0;
        }
        inp_list_idx++;
    }

    if(idx == bomb.size()){
        inp_list.erase(start_iter, inp_list.end());
        found = true;
    }

    return found;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> inp >> bomb;

    inp_list.assign(inp.begin(), inp.end());

    while(find_bomb()){}

    if(inp_list.empty()) cout << "FRULA";
    else {
        for (char ch: inp_list)
            cout << ch;
    }
}