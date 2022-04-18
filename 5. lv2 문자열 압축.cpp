#include <string>
#include <vector>

using namespace std;

vector<string> tokenizing(string s, int N){
    vector<string> tokens;
    for(int j=0; s.length()>=N; j+N){
        tokens.push_back(s.substr(j, j+N));
        s = s.substr(j+N);
        if (s.length()<N) tokens.push_back(s);
    }
    return tokens;
}

int solution(string s) {
    int answer = s.length();

    for(int i=s.length()/2; i != 0; i--){
        vector<string> tok = tokenizing(s, i);
        string bf_t = "", cur_t, zip;
        int cnt=0;
        for(int j=0; j<tok.size(); j++){
            cur_t = tok[j];
            if (bf_t == "") {
                bf_t = cur_t;
                continue;
            }
            if (bf_t == cur_t){
                cnt++;
            }else{
                if(cnt != 0) zip += to_string(cnt+1);
                zip += bf_t;
                cnt = 0;
            }
            if(j+1 == tok.size()){
                if(cnt != 0) zip += to_string(cnt+1);
                zip += cur_t;
            }
            bf_t = cur_t;
        }
        if(answer >= zip.length()) answer = zip.length();
    }

    return answer;
}
