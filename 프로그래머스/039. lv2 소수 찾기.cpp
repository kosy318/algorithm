https://jolly-note.tistory.com/75?category=1025701

#include <string>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

bool is_prime(int num){
    if(num <= 1) return false;

    for(int i=2; i<num/2 + 1; i++){
        if(num%i == 0) return false;
    }

    return true;
}

int solution(string numbers) {
    int answer = 0;
    sort(numbers.begin(), numbers.end());

    set<int> nums;
    do{
        string temp = numbers;
        while(!temp.empty()){
            nums.insert(stoi(temp));
            temp.pop_back();
        }
    }while(next_permutation(numbers.begin(), numbers.end()));

    for(auto s : nums){
        if(is_prime(s)) answer += 1;
    }

    return answer;
}
