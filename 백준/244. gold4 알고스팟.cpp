#include <iostream>
#include <vector>
#include <string>
#include <deque>

using namespace std;

int N, M;
vector<string> maze;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int bfs(){
    vector<vector<int>> broke_cnt(N, vector<int>(M, 10000));
    broke_cnt[0][0] = 0;

    deque<pair<int, int>> deq;
    deq.emplace_back(0, 0);

    while(!deq.empty()) {
        auto cur = deq.front();
        deq.pop_front();

        if(cur.first == N-1 && cur.second == M-1) return broke_cnt[cur.first][cur.second];

        for (int d = 0; d < 4; d++) {
            int nx = cur.first + dx[d];
            int ny = cur.second + dy[d];

            if (nx < 0 || ny < 0 || nx >= N || ny >= M) continue; // 범위 벗어남

            if(broke_cnt[nx][ny] > broke_cnt[cur.first][cur.second] + (maze[nx][ny] - '0')) {
                broke_cnt[nx][ny] = broke_cnt[cur.first][cur.second] + (maze[nx][ny] - '0');
                if(maze[nx][ny] == '0') deq.emplace_front(nx, ny);
                else deq.emplace_back(nx, ny);
            }
        }
    }

    return -1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //////////// 틀린 부분 : 입력 제대로 보자...
    cin >> M >> N;

    maze = vector<string>(N);

    for (int i = 0; i < N; i++) {
        cin >> maze[i];
    }

    cout << bfs();
}