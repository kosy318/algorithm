// https://jolly-note.tistory.com/36

#include <string>
#include <vector>
#include <regex>
#include <map>

using namespace std;


vector<string> add(vector<string> str){
    auto iter = find(str.begin(), str.end(), "+");
    while(iter != str.end()){
        long long a = stoll(*(iter-1)), b = stoll(*(iter+1));
        str.erase(iter-1, iter+2);
        str.insert(iter-1, to_string(a+b));
        iter = find(str.begin(), str.end(), "+");
    }
    return str;
}

vector<string> subtract(vector<string> str){
    auto iter = find(str.begin(), str.end(), "-");
    while(iter != str.end()){
        long long a = stoll(*(iter-1)), b = stoll(*(iter+1));
        str.erase(iter-1, iter+2);
        str.insert(iter-1, to_string(a-b));
        iter = find(str.begin(), str.end(), "-");
    }
    return str;
}

vector<string> multiply(vector<string> str){
    auto iter = find(str.begin(), str.end(), "*");
    while(iter != str.end()){
        long long a = stoll(*(iter-1)), b = stoll(*(iter+1));
        str.erase(iter-1, iter+2);
        str.insert(iter-1, to_string(a*b));
        iter = find(str.begin(), str.end(), "*");
    }
    return str;
}

long long solution(string expression) {
    long long answer = 0;
    long long res = 0;

    // split
    vector<string> split_expr;
    smatch match;
    while(regex_search(expression, match, regex("\\d+"))){
        split_expr.push_back(match.str());
        expression = match.suffix().str();
        string op{expression[0]};
        split_expr.push_back(op);
    }


    // * + -
    answer = abs(stoll(subtract(add(multiply(split_expr)))[0]));
    // * - +
    res = abs(stoll(multiply(add(subtract(split_expr)))[0]));
    if(answer < res) answer = res;
    // + - *
    res = abs(stoll(multiply(subtract(add(split_expr)))[0]));
    if(answer < res) answer = res;
    // - + *
    res = abs(stoll(subtract(add(multiply(split_expr)))[0]));
    if(answer < res) answer = res;
    // + * -
    res = abs(stoll(subtract(multiply(add(split_expr)))[0]));
    if(answer < res) answer = res;
    // - * +
    res = abs(stoll(add(multiply(subtract(split_expr)))[0]));
    if(answer < res) answer = res;

    return answer;
}

/*
#include <string>
#include <vector>
#include <regex>

using namespace std;

string add(string str){
    smatch match;

    while(regex_search(str, match, regex("(\\d+[+](-)?\\d+)|(^(-)\\d+[+](-)?\\d+)"))){
        long long a, b;
        sscanf(match.str().c_str(), "%lld+%lld", &a, &b);
        str.replace(str.find(match.str()), match.str().length(), to_string(a+b));
    }
    return str;
}

string subtract(string str){
    smatch match;

    while(regex_search(str, match, regex("(\\d+[-](-)?\\d+)|(^(-)?\\d+[-](-)?\\d+)"))){
        long long a, b;
        sscanf(match.str().c_str(), "%lld-%lld", &a, &b);
        str.replace(str.find(match.str()), match.str().length(), to_string(a-b));
    }
    return str;
}

string multiply(string str){
    smatch match;

    while(regex_search(str, match, regex("(\\d+[*](-)?\\d+)|(^(-)?\\d+[*](-)?\\d+)"))){
        long long a, b;
        sscanf(match.str().c_str(), "%lld*%lld", &a, &b);
        str.replace(str.find(match.str()), match.str().length(), to_string(a*b));
    }
    return str;
}

long long solution(string expression) {
    long long answer = 0;
    long long res = 0;

    // * + -
    answer = abs(stoll(subtract(add(multiply(expression)))));
    // * - +
    res = abs(stoll(multiply(add(subtract(expression)))));
    if(answer < res) answer = res;
    // + - *
    res = abs(stoll(multiply(subtract(add(expression)))));
    if(answer < res) answer = res;
    // - + *
    res = abs(stoll(multiply(add(subtract(expression)))));
    if(answer < res) answer = res;
    // + * -
    res = abs(stoll(subtract(multiply(add(expression)))));
    if(answer < res) answer = res;
    // - * +
    res = abs(stoll(add(multiply(subtract(expression)))));
    if(answer < res) answer = res;
    return answer;
}
*/
