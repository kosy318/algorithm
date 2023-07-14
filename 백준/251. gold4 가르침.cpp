#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

int N, K; // N := 단어의 개수, K := 배울 수 있는 글자 수
int* string_list;

int get_chars(const string& word){
    int res = 0;
    for(char ch : word){
        if(ch != 'a' && ch != 'n' && ch != 't' && ch != 'i' && ch != 'c')
            res |= (1 << (ch - 'a'));
    }

    return res;
}

// O(logN)
int count_bits(int num) { // Brian Kernighan의 알고리즘 -> 이진수의 1의 개수 계산
    int count = 0;
    while (num != 0) {
        num = num & (num - 1);
        count++;
    }
    return count;
}

int picked = 0;
void print_picked(int chars){
    for(int i = 0; i < 26; i++){
        if(chars & 1 << i){
            cout << char('a' + i) << " ";
        }
    }
    cout << endl;
}

int count_possible(){
//    print_picked(picked);

    int res = 0;
    for(int i=0; i<N; i++){
        int flag = true;
        for (int j = 0; j < 26; j++) {
            if(string_list[i] & 1 << j && !(picked & 1 << j)){
                flag = false;
            }
        }
        if(flag) res += 1;
    }

    return res;
}

int answer = 0;
void comb(const int& chars, int cnt = 0, int start = 0){ // cnt := 현재까지 뽑은 조합 원소 개수, start := 조합 시도할 원소의 시작 인덱스
    if(cnt == K){ ////////// 틀린 부분 : K가 chars의 1의 개수보다 크면 절대 count가 K가 될 때까지 증가할 수 없다.
        int res = count_possible();
        answer = max(answer, res);
        return;
    }

    for (int i = start; i < 26; i++) {
        if(chars & 1 << i){
            picked |= 1 << i;
            comb(chars, cnt + 1, i + 1);
            ///////////////// 틀린 부분 : 0 << i를 하면 그냥 0임 ㅋㅋㅋㅋㅋㅋㅋ ~(1<<i)랑 해야함
            picked &= ~(1 << i);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K;

    K -= 5;

    string_list = new int[N];
    int chars = 0;
    for (int i = 0; i < N; i++) {
        string word;
        cin >> word;

        string_list[i] = get_chars(word);

        chars |= string_list[i];
    }
    K = min(count_bits(chars), K); //////////// 틀린 부분 : 위의 count == K 부분의 틀린 이유 때문에 추가했다.

//    print_picked(chars);

    comb(chars);
    cout << answer;
}