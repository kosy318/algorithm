#include <iostream>
#include <queue>

using namespace std;

struct Info{
    int idx;
    int num;
    int dp;

    Info(int idx, int num, int dp) : idx{idx}, num{num}, dp{dp}{}
};

struct comp{

};

int find_max(int num, priority_queue<Info> que){

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    int *nums = new int[N];
    for (int i = 0; i < N; i++) {
        cin >> nums[i];
    }

    int *dp = new int[N];
    priority_queue<Info> que;

    int max_len = 0;
    for (int i = 0; i < N; i++) {
        dp[i] = find_max(nums[i], que);
        que.emplace(i, nums[i], dp[i]);
        if (max_len < dp[i]) max_len = dp[i];
    }

//    for (int i = 0; i < N; i++) {
//        cout << dp[i] << " ";
//    }
//    cout << endl;

    cout << max_len;
}