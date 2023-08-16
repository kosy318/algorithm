#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct To{
    int to, time;

    To() {}
    To(int to, int time) : to(to), time(time) {}
};

int N, M, W; // N개의 지점, M개의 도로, W개의 웜홀

void input(vector<vector<To>> &spots) {
    cin >> N >> M >> W;
    spots = vector<vector<To>>(N + 1);

    for (int i = 0; i < M; i++) {
        int from, to, time;
        cin >> from >> to >> time;

        // 양방향
        spots[from].emplace_back(to, time);
        spots[to].emplace_back(from, time);
    }

    for (int i = 0; i < W; i++) {
        int from, to, time;
        cin >> from >> to >> time;

        // 단방향
        spots[from].emplace_back(to, -time);
    }
}

// https://www.acmicpc.net/board/view/72995
bool solve(vector<vector<To>> &spots) {
    vector<bool> visited(N + 1, false);
    for(int start=1; start<=N; start++){
        if(visited[start]) continue;
        vector<int> dist(N + 1, INT_MAX);

        // 출발 노드 설정
        dist[start] = 0;

        // 전체 v번의 round를 반복, v번째에서 음수 사이클 존재 여부 확인
        for (int round = 1; round <= N; round++) {
            for (int i = 1; i <= N; i++) {
                for (auto next: spots[i]) { // from 'i' to 'To'
                    // 저장되어있는 1번에서 next.to로 가는 값 vs 저장되어있는 1번에서 i번으로 가는 값 + i에서 next.to로 가는 값
                    if (dist[i] != INT_MAX && dist[next.to] > dist[i] + next.time) {
                        // 비용이 더 적게 나오면 갱신
                        dist[next.to] = dist[i] + next.time;
                        visited[next.to] = true;

                        // v번째 round
                        if (round == N) return true;
                    }
                }
            }
        }
    }
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        vector<vector<To>> spots;
        input(spots);

        // 음수 사이클이 존재하는지 확인하면 됨
        cout << (solve(spots)? "YES": "NO") << "\n";
    }
}