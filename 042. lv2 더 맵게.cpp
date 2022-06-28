https://jolly-note.tistory.com/78?category=1025701

/* map 사용
#include <vector>
#include <map>

using namespace std;

int solution(vector<int> scoville, int K) {
    int answer = 0;

    map<int, int> scov;
    for(auto s: scoville)
        scov[s]++;

    while(scov.begin()->first < K){
        int first = scov.begin()->first;
        scov.begin()->second--;
        if(scov.begin()->second == 0) scov.erase(first);

        int second = scov.begin()->first;
        scov.begin()->second--;
        if(scov.begin()->second == 0) scov.erase(second);

        scov[first + second*2]++;
        answer++;

        if(scov.size() == 1 && scov.begin()->second == 1 && scov.begin()->first < K) return -1;
    }

    return answer;
}
*/

// priority queue 사용
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> scoville, int K) {
    int answer = 0;

    priority_queue<int, vector<int>, greater<int>> scov;
    for(auto s: scoville)
        scov.push(s);

    while(scov.top() < K){
        int first = scov.top(); scov.pop();
        int second = scov.top(); scov.pop();

        scov.push(first + second*2);
        answer++;

        if(scov.size() == 1 && scov.top() < K) return -1;
    }

    return answer;
}
