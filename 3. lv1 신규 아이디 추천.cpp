// https://jolly-note.tistory.com/26?category=1025701

#include <string>
#include <vector>

using namespace std;

string solution(string new_id) {
    string answer = "";
    for(int i=0; i<new_id.length(); i++){
        new_id[i] = tolower(new_id[i]); // 대문자 소문자로 바꿔주기


        if(isalnum(new_id[i]) || new_id[i] == '-' || new_id[i] == '_'){
            answer += new_id[i]; // 알파벳, 숫자, -, _ 이면 answer에 넣음
            continue;
        }

        if(new_id[i] == '.' && answer.length() != 0 && answer.back() != '.')
            answer += new_id[i];  // .가 맨앞이거나 2번 이상 연속되면 answer에 넣지않음
    }
    if(answer.back() == '.') // .가 answer 마지막에 있으면 제거
        answer.pop_back();

    if(answer.length() == 0) // answer 길이가 0이면 "aaa" 리턴
        return "aaa";
    else if(answer.length() >= 16) // answer 길이가 16보다 크면 길이 15로 자름
        answer = answer.substr(0, 15);

    if(answer.back() == '.') // .가 answer 마지막에 있으면 제거
        answer.pop_back();

    while(answer.length() <= 2) // answer 길이가 2보다 작거나 같으면 마지막 글자를 길이가 3이 될때까지 추가
        answer += answer.back();

    return answer;
}
