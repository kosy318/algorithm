#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// dp[i][0] := i��° node�� �󸮾���Ͱ� �ƴ� ��� �ڽ� �� �󸮾������ �͵��� ������ �ּ�
// dp[i][1] := i��° node�� �󸮾������ ��� �ڽ� �� �󸮾������ �͵��� ������ �ּ�
vector<vector<int>> dp;
vector<vector<int>> adj_list;

void dfs(int cur){
    dp[cur] = {0, 1};

    if (adj_list[cur].size() == 1) {
        // cout << "dp[" << cur << "] " << dp[cur][0] << ", " << dp[cur][1] << endl;
        return; // leaf node
    }

    for (int adj: adj_list[cur]) {
        if(dp[adj][0] == -1){ // �ڽ� node
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

    queue<int> que;
    for (int i = 1; i <= N; i++) {
        if (adj_list[i].size() == 1) {
            que.push(i);
        }
    }

    dfs(1);

    cout << min(dp[1][0], dp[1][1]);
}