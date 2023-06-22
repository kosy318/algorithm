#include <iostream>
#include <vector>

using namespace std;

int N;
vector<int> nums;

// 이분 탐색
int find_idx(int num, int length, vector<int>& temp){ // num 이상인 숫자가 처음 발견되는 곳을 찾으려고 함
    int left = 0, right = length-1;
    // temp는 이미 정렬된 상태이기 때문에 이분 탐색 가능
    while (left < right) {
        int mid = (left + right) / 2;
        if(temp[mid] > num) right = mid;
        else if(temp[mid] < num) left = mid + 1;
        else return mid;
    }

    return left;
}

int LIS(){
    vector<int> temp;

    int length = 0;
    for (int i = 0; i < N; i++) {
        if (i == 0 || temp[length - 1] < nums[i]) {
            temp.push_back(nums[i]);
            length += 1;
        }
        else {
            temp[find_idx(nums[i], length, temp)] = nums[i]; // nums[i]가 들어갈 idx 찾기(lower_bound)
        }
    }

    return length;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    nums = vector<int>(N);
    for (int i = 0; i < N; i++) {
        cin >> nums[i];
    }

    cout << LIS();
}