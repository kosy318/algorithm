#include <iostream>
#include <vector>

using namespace std;

int N;
vector<int> nums;

int find_idx(int num, int length, vector<int>& temp){
    int left = 0, right = length - 1;

    while (left < right) {
        int mid = (left + right) / 2;
        if (temp[mid] > num) {
            right = mid;
        } else if (temp[mid] < num) {
            left = mid + 1;
        } else return mid; //////////// 같은 숫자가 temp에 여러개 있을 수 없음
    }

    return left;
}

void LIS(){
    vector<int> temp;
    vector<int> lis_idx(N, -1); // lis_idx[i] := i번째 num이 temp의 어디에 위치해있는지

    int length = 0;
    for (int i = 0; i < N; i++) {
        if (i == 0 || temp[length - 1] < nums[i]) {
            temp.push_back(nums[i]);
            length += 1;

            lis_idx[i] = length - 1;
        }
        else {
            int idx = find_idx(nums[i], length, temp);
            temp[idx] = nums[i];

            lis_idx[i] = idx;
        }
    }

    cout << length << "\n";
    vector<int> ans;
    int answer_idx = length - 1;
    ///////// 틀린 부분 : lis_idx는 한번만 돌아야함
    for (int i = N - 1; i >= 0; i--) {
        if(lis_idx[i] == answer_idx){
            ans.push_back(nums[i]);
            answer_idx -= 1;

            if(answer_idx < 0) break;
        }
    }
    for (int i = length - 1; i >= 0; i--) { ////////// 틀린 부분 : 역으로 출력했어야했는데 ㅋㅋㅋㅋㅋ..
        cout << ans[i] << " ";
    }
    cout << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    nums = vector<int>(N);
    for (int i = 0; i < N; i++) {
        cin >> nums[i];
    }

    LIS();
}