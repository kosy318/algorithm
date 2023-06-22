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
        } else return mid; //////////// ���� ���ڰ� temp�� ������ ���� �� ����
    }

    return left;
}

void LIS(){
    vector<int> temp;
    vector<int> lis_idx(N, -1); // lis_idx[i] := i��° num�� temp�� ��� ��ġ���ִ���

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
    ///////// Ʋ�� �κ� : lis_idx�� �ѹ��� ���ƾ���
    for (int i = N - 1; i >= 0; i--) {
        if(lis_idx[i] == answer_idx){
            ans.push_back(nums[i]);
            answer_idx -= 1;

            if(answer_idx < 0) break;
        }
    }
    for (int i = length - 1; i >= 0; i--) { ////////// Ʋ�� �κ� : ������ ����߾���ߴµ� ����������..
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