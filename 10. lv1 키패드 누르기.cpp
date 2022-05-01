// https://jolly-note.tistory.com/35?category=1025701

#include <string>
#include <vector>

using namespace std;

string solution(vector<int> numbers, string hand) {
    string answer = "";
    vector<int> l_cur = {3, 0}, r_cur = {3, 2};
    vector<vector<int>> keypads{{3,1}, {0,0}, {0,1}, {0,2}, {1,0}, {1,1}, {1,2}, {2,0}, {2,1}, {2,2}};

    for (int num : numbers){
        switch(num){
            case 1:
            case 4:
            case 7:
                l_cur = keypads[num];
                answer += 'L';
                break;
            case 3:
            case 6:
            case 9:
                r_cur = keypads[num];
                answer += 'R';
                break;
            case 2:
            case 5:
            case 8:
            case 0:
                int l_dist = abs(l_cur[0] - keypads[num][0]) + abs(l_cur[1] - keypads[num][1]);
                int r_dist = abs(r_cur[0] - keypads[num][0]) + abs(r_cur[1] - keypads[num][1]);

                if(l_dist < r_dist || (l_dist == r_dist && hand == "left")) {
                    l_cur = keypads[num];
                    answer += 'L';
                }
                else if(l_dist > r_dist || (l_dist == r_dist && hand == "right")) {
                    r_cur = keypads[num];
                    answer += 'R';
                }
                break;
        }
    }

    return answer;
}​
