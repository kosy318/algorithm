#include <iostream>
#include <vector>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> nums(N);
    vector<int> dp(N); // dp[i] := i��° ���ں��� ū �����ʿ� �ִ� ���� ����� ����

    for (int i = 0; i < N; i++) {
        cin >> nums[i];
    }

    dp[N - 1] = -1;
    for (int i = N - 2; i >= 0; i--) {
        for (int j = i + 1; j < N; j++) {
            if (dp[j] == -1) { // dp[j] == -1 �� ���
                // nums[j]���� nums[i]�� �� ũ�� nums[i]���� ū �ִ� ����
                if(nums[j] <= nums[i]) dp[i] = -1;
                // nums[j]���� nums[i]�� �� ������ ���� ����� nums[i]���� ū ���� �Ͽ�ư nums[j]��
                else dp[i] = nums[j];

                break;
            }
            else if(dp[j] > nums[i]){
                if(nums[j] > nums[i]) dp[i] = nums[j];
                else dp[i] = dp[j];

                break;
            }
        }
    }

    for(int i : dp)
        cout << i << " ";
}