#include<string>
#include<stack>

using namespace std;

int solution(string s) {
    stack<char> ch_stack;
    for(char ch: s){
        if(ch_stack.empty() || ch_stack.top() != ch)
            ch_stack.push(ch);
        else if(ch_stack.top() == ch){
            ch_stack.pop();
        }
    }

    return (ch_stack.empty())? 1 : 0;
}
