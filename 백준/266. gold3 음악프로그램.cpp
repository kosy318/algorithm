#include <iostream>
#include <queue>

using namespace std;

int N; // 가수의 수
int M; // 보조 PD의 수

vector<int> topology_sort(vector<vector<int>>& conn, vector<int>& in_degree) {
    vector<int> answer;

    for (int i = 1; i <= N; i++) {
        if(in_degree[i] == 0) {
            answer.push_back(i);
        }
    }

    int idx = 0;
    while (answer.size() != N && idx < answer.size()) {
        for (int i: conn[answer[idx]]) {
            in_degree[i] -= 1;
            if (in_degree[i] == 0) {
                answer.push_back(i);
            }
        }

        idx += 1;
    }

    return answer;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;

    vector<vector<int>> conn(N + 1);
    vector<int> in_degree(N + 1, 0);

    for (int i = 0; i < M; i++) {
        int K, cur, next;
        cin >> K >> cur;
        for (int j = 1; j < K; j++) {
            cin >> next;
            in_degree[next] += 1;
            conn[cur].push_back(next);

            cur = next;
        }
    }

    vector<int> answer = topology_sort(conn, in_degree);

    if (answer.size() == N) {
        for (int i: answer) {
            cout << i << "\n";
        }
    } else cout << 0;
}