https://jolly-note.tistory.com/77?category=1025701

#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;

    int idx = 0;
    while(idx < progresses.size()){
        while(progresses[idx] < 100){
            for(int i=idx; i< progresses.size(); i++){
                progresses[i] += speeds[i];
            }
        }

        answer.push_back(0);
        while(idx < progresses.size() && progresses[idx] >= 100){
            idx++;
            answer.back()++;
        }
    }

    return answer;
}
