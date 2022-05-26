// https://jolly-note.tistory.com/27

#include <bits/stdc++.h>

using namespace std;

int solution(string s) {
    vector<string> nums = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    string answer;
    for(int i=0; i<s.length(); i++){
        if(isdigit(s[i])){ // 숫자면 answer에 추가하고 돌아감
            answer += s[i];
            continue;
        }
        switch(s[i]){ // 숫자가 아니면 해당 숫자를 찾아가서 answer에 추가
            case 'z':
                answer += '0';
                break;
            case 'o':
                answer += '1';
                break;
            case 't':
                if(s[i+1] == 'w') answer += '2';
                else answer += '3';
                break;
            case 'f':
                if(s[i+1] == 'o') answer += '4';
                else answer += '5';
                break;
            case 's':
                if(s[i+1] == 'i') answer += '6';
                else answer += '7';
                break;
            case 'e':
                answer += '8';
                break;
            case 'n':
                answer += '9';
                break;
        }
        i += nums[answer.back() - '0'].length() - 1; // 추가한 숫자의 영단어 길이-1만큼 index 이동
    }
    return stoi(answer);
}
