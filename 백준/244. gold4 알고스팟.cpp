#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>

using namespace std;

struct Room{
    int x, y;
    int broke;

    Room(int x, int y, int broke): x{x}, y{y}, broke{broke}{}
};

int N, M;
vector<vector<int>> maze;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int bfs(){
    vector<vector<int>> broke_cnt(N, vector<int>(M, 10000));
    deque<Room> deq;
    deq.push_back(Room(0, 0, 0));

    while(!deq.empty()) {
        Room cur = deq.front();
        deq.pop_front();

        if(cur.x == N-1 && cur.y == M-1) return cur.broke;

        for (int d = 0; d < 4; d++) {
            int nx = cur.x + dx[d];
            int ny = cur.y + dy[d];

            if (nx < 0 || ny < 0 || nx >= N || ny >= M) continue; // ¹üÀ§ ¹þ¾î³²
            if(broke_cnt[nx][ny] != 10000) continue;

            if(maze[nx][ny] == 0){
                broke_cnt[nx][ny] = min(broke_cnt[nx][ny], broke_cnt[cur.x][cur.y]);
                deq.push_front(Room(nx, ny, cur.broke));
            } else {
                broke_cnt[nx][ny] = min(broke_cnt[nx][ny], broke_cnt[cur.x][cur.y] + 1);
                deq.push_back(Room(nx, ny, cur.broke + 1));
            }
        }
    }

    return -1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;

    maze = vector<vector<int>>(N, vector<int>(M));

    for (int i = 0; i < N; i++) {
        string str;
        cin >> str;
        for (int j = 0; j < M; j++) {
            maze[i][j] = str[j] - '0';
        }
    }

    cout << bfs();
}