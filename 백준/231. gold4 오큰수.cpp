#include <iostream>
#include <vector>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> nums(N);
    vector<int> dp(N); // dp[i] := i번째 숫자보다 큰 오른쪽에 있는 가장 가까운 숫자

    for (int i = 0; i < N; i++) {
        cin >> nums[i];
    }

    dp[N - 1] = -1;
    for (int i = N - 2; i >= 0; i--) {
        for (int j = i + 1; j < N; j++) {
            if (dp[j] == -1) { // dp[j] == -1 인 경우
                // nums[j]보다 nums[i]가 더 크면 nums[i]보다 큰 애는 없음
                if(nums[j] <= nums[i]) dp[i] = -1;
                // nums[j]보다 nums[i]가 더 작으면 가장 가까운 nums[i]보다 큰 수는 하여튼 nums[j]임
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