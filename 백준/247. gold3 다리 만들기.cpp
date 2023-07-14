#include <iostream>
#include <queue>
#include <set>

using namespace std;

int N;
int map[100][100];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

set<pair<int, int>> beside_sea;

void coloring(){
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if(map[i][j] == 0 || map[i][j] < 0) continue; // 이미 들렸거나 들릴 필요가 없음

            cnt += 1;

            queue<pair<int, int>> que;
            map[i][j] = -cnt;
            que.emplace(i, j);
            while (!que.empty()) {
                pair<int, int> cur = que.front();
                que.pop();

                for (int d = 0; d < 4; d++) {
                    int nx = cur.first + dx[d];
                    int ny = cur.second + dy[d];

                    if(nx < 0 || ny < 0 || nx >= N || ny >= N || map[nx][ny] < 0) continue;
                    if(map[nx][ny] == 0) {
                        beside_sea.emplace(cur.first, cur.second);
                        continue;
                    }

                    map[nx][ny] = -cnt;
                    que.emplace(nx, ny);
                }
            }
        }
    }
}

int find_route(){
    int res = 20000;

    for (pair<int, int> p: beside_sea) {
        int island = map[p.first][p.second];

        vector<vector<bool>> visited(N, vector<bool>(N, false));

        queue<pair<pair<int, int>, int>> que;
        visited[p.first][p.second] = true;
        que.emplace(p, 0);
        while (!que.empty()) {
            pair<int, int> cur = que.front().first;
            int length = que.front().second;
            que.pop();

            if(length >= res) break;

            for (int d = 0; d < 4; d++) {
                int nx = cur.first + dx[d];
                int ny = cur.second + dy[d];

                if(nx < 0 || ny < 0 || nx >= N || ny >= N || visited[nx][ny]) continue;

                visited[nx][ny] = true;

                if(map[nx][ny] < 0 && map[nx][ny] != island) {
                    res = length;
                    break;
                }
                else if(map[nx][ny] == 0) {
                    que.emplace(make_pair(nx, ny), length + 1);
                }
            }
        }
    }

    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }

    coloring();

    // check
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < N; j++) {
//            cout << map[i][j] << "\t";
//        }
//        cout << "\n";
//    }

    cout << find_route();
}