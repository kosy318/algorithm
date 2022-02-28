// https://jolly-note.tistory.com/26?category=1025701

#include <string>
#include <vector>

using namespace std;

string solution(string new_id) {
    string answer = "";
    for(int i=0; i<new_id.length(); i++){
        new_id[i] = tolower(new_id[i]); // �빮�� �ҹ��ڷ� �ٲ��ֱ�


        if(isalnum(new_id[i]) || new_id[i] == '-' || new_id[i] == '_'){
            answer += new_id[i]; // ���ĺ�, ����, -, _ �̸� answer�� ����
            continue;
        }

        if(new_id[i] == '.' && answer.length() != 0 && answer.back() != '.')
            answer += new_id[i];  // .�� �Ǿ��̰ų� 2�� �̻� ���ӵǸ� answer�� ��������
    }
    if(answer.back() == '.') // .�� answer �������� ������ ����
        answer.pop_back();

    if(answer.length() == 0) // answer ���̰� 0�̸� "aaa" ����
        return "aaa";
    else if(answer.length() >= 16) // answer ���̰� 16���� ũ�� ���� 15�� �ڸ�
        answer = answer.substr(0, 15);

    if(answer.back() == '.') // .�� answer �������� ������ ����
        answer.pop_back();

    while(answer.length() <= 2) // answer ���̰� 2���� �۰ų� ������ ������ ���ڸ� ���̰� 3�� �ɶ����� �߰�
        answer += answer.back();

    return answer;
}
