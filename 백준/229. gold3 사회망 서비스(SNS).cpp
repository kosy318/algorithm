#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// dp[i][0] := i번째 node가 얼리어답터가 아닌 경우 자식 중 얼리어답터인 것들의 개수의 최소
// dp[i][1] := i번째 node가 얼리어답터인 경우 자식 중 얼리어답터인 것들의 개수의 최소
vector<vector<int>> dp;
vector<vector<int>> adj_list;

///////////// 2 1 2 인 경우 틀림 : adj_list size가 1인 경우 leaf node라고 판단한 부분이 틀림. 따로 판단할 필요 x
void dfs(int cur){
    dp[cur] = {0, 1};

    for (int adj: adj_list[cur]) {
        if(dp[adj][0] == -1){ // 자식 node
            dfs(adj);
            dp[cur][0] += dp[adj][1];
            dp[cur][1] += min(dp[adj][0], dp[adj][1]);
        }
    }

    // cout << "dp[" << cur << "] " << dp[cur][0] << ", " << dp[cur][1] << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    dp = vector<vector<int>>(N + 1, vector<int>(2, -1));
    adj_list = vector<vector<int>>(N + 1);

    for (int i = 0; i < N-1; i++) {
        int u, v;
        cin >> u >> v;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    dfs(1);

    cout << min(dp[1][0], dp[1][1]);
}