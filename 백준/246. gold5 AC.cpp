#include <iostream>
#include <string>
#include <sstream>
#include <deque>

using namespace std;

deque<int> split(string str){
    istringstream iss(str);
    string buff;

    deque<int> result;

    while(getline(iss, buff, ',')){
        result.push_back(stoi(buff));
    }

    return result;
}

bool reversed = false;
bool resolve(string op, deque<int>& nums){
    // R : 뒤집기
    // D : 맨 처음 숫자 버리기
    for(char ch : op){
        if (ch == 'R') {
            reversed = !reversed;
        } else if (ch == 'D'){
            if(nums.empty()){
                cout << "error\n";
                return false;
            }

            if (!reversed) {
                nums.pop_front();
            } else{
                nums.pop_back();
            }
        }
    }

    return true;
}

void print_answer(deque<int>& nums){
    cout << "[";
    if (!reversed) {
        for (int i=0; i<nums.size(); i++) {
            cout << nums[i];
            if(i != nums.size()-1) cout << ",";
        }
    } else {
        for (int i = nums.size() - 1; i >= 0; i--) {
            cout << nums[i];
            if(i != 0) cout << ",";
        }
    }
    cout << "]\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        string op;
        cin >> op;

        int N;
        cin >> N;

        string str;
        cin >> str;
        deque<int> nums = split(str.substr(1, str.size() - 2));

        reversed = false;
        if(resolve(op, nums))
            print_answer(nums);
    }
}