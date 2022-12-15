https://jolly-note.tistory.com/76?category=1025701

#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

bool is_prime(int num){
    if(num <= 1) return false;

    for(int i=2; i<=sqrt(num); i++){
        if(num%i == 0) return false;
    }

    return true;
}

int solution(vector<int> nums) {
    int answer = 0;

    vector<int> pick(nums.size(), 0);
    for(int i=pick.size()-3; i<pick.size(); i++)
        pick[i] = 1;

    do{
        int sum = 0;
        for(int i=0; i<pick.size(); i++){
            if(pick[i] == 1) sum += nums[i];
        }

        if(is_prime(sum)) answer += 1;
    }while(next_permutation(pick.begin(), pick.end()));

    return answer;
}
