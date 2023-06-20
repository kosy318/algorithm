#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int N; // 도시의 개수
int M; // 버스의 개수
vector<vector<int>> adj(101, vector<int>(101)); // 도시에서 도시로 아무것도 거치지 않고 가는 비용
vector<vector<int>> cost(101, vector<int>(101, 0)); // 도시에서 도시로 가는 최소 비용

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        int a, b, c; // a 에서 b로 가는 비용 c(>0)
        cin >> a >> b >> c; // a != b

        if(adj[a][b] == 0 || adj[a][b] > c) adj[a][b] = c;
    }

    // 플로이드 워셜
    // cost 배열 초기화
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if(i == j) {
                cost[i][j] = 0;
            } else if (adj[i][j] > 0) {
                cost[i][j] = adj[i][j];
            } else cost[i][j] = INT_MAX;
        }
    }

    // 기존 cost[i][j]랑 cost[i][k] + (k->j)랑 비교
    for (int k = 1; k <= N; k++) { // 중간 노드가 될 번호 k
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (cost[i][k] == INT_MAX || cost[k][j] == INT_MAX) continue;
                else if (cost[i][j] == INT_MAX || cost[i][j] > cost[i][k] + cost[k][j]) {
                    cost[i][j] = cost[i][k] + cost[k][j];
                }
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (cost[i][j] == INT_MAX) cout << "0 ";
            else cout << cost[i][j] << " ";
        }
        cout << "\n";
    }
}