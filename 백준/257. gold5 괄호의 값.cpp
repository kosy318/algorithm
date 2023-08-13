#include <iostream>
#include <string>
#include <stack>

using namespace std;

// ()  : 2
// []  : 3
// (x) : 2x값(x)
// [x] : 3x값(x)
// xy  : x + y

bool is_open_bracket(char& ch){
    return (ch == '(' || ch == '[');
}

bool is_close_bracket(char& ch){
    return (ch == ')' || ch == ']');
}

void extract_nums(stack<string> &bracket, const string& open_bracket, int point) {
    int num = point;

    string top = bracket.top(); bracket.pop();
    if(top != open_bracket){ // 맨 위가 숫자인 경우
        num = stoi(top);

        // 틀린 부분 : segment fault -> 앞에서 pop을 한 뒤 bracket이 비어있을 수가 있음.
        if(bracket.empty() || bracket.top() != open_bracket) throw invalid_argument("invalid bracket");

        // 괄호 순서가 올바르면
        num *= point;
        bracket.pop();
    }

    //cout << "[Debug] cur num is : " << num << endl;

    while(!bracket.empty()){
        try {
            int num2 = stoi(bracket.top());
            bracket.pop();

            num += num2;
        }
        catch (invalid_argument const& ex) {
            break;
        }
    }
    bracket.push(to_string(num));
    //cout << "[Debug] calc num : " << num << endl;
}

void calculate(stack<string>& bracket, char& ch) {
    if(ch == ')'){
        extract_nums(bracket, "(", 2);
    } else { // ']'
        extract_nums(bracket, "[", 3);
    }
}

void print_stack(stack<string> stk){
    cout << "[Debug] ";
    while(!stk.empty()){
        cout << stk.top() << " ";
        stk.pop();
    }
    cout << endl;
}

int solve(string& inp){
    stack<string> bracket;

    for(char& ch : inp){
        //cout << "[Debug] next ch : " << ch << endl;
        if(is_open_bracket(ch)){
            bracket.emplace(1, ch);
        }
        else if(is_close_bracket(ch) && !bracket.empty()) { // 틀린 부분 : segment fault -> bracket이 비어있는 상태에서 닫는 bracket이 들어올 수 있음
            calculate(bracket, ch);
        }
        else return 0;

//        print_stack(bracket);
    }

    return (bracket.size() != 1)? 0 : stoi(bracket.top());
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string bracket_string;
    cin >> bracket_string;

    try {
        cout << solve(bracket_string);
    }
    catch (invalid_argument const& ex) {
        //cout << "[Debug] " << ex.what() << endl;
        cout << 0;
    }
}