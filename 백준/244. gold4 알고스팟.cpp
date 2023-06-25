#include <iostream>
#include <vector>
#include <string>
#include <deque>

using namespace std;

struct Room{
    int x, y;
    int broke;

    Room(int x, int y, int broke): x{x}, y{y}, broke{broke}{}
};

int N, M;
vector<string> maze;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int bfs(){
    vector<vector<int>> broke_cnt(N, vector<int>(M, 10000));
    broke_cnt[0][0] = 0;

    deque<Room> deq;
    deq.push_back(Room(0, 0, 0));

    while(!deq.empty()) {
        Room cur = deq.front();
        deq.pop_front();

        if(cur.x == N-1 && cur.y == M-1) return cur.broke;

        for (int d = 0; d < 4; d++) {
            int nx = cur.x + dx[d];
            int ny = cur.y + dy[d];

            if (nx < 0 || ny < 0 || nx >= N || ny >= M) continue; // 범위 벗어남

            if(broke_cnt[nx][ny] > cur.broke + (maze[nx][ny] - '0')) {
                broke_cnt[nx][ny] = cur.broke + (maze[nx][ny] - '0');
                if(maze[nx][ny] == '0') deq.push_front(Room(nx, ny, cur.broke));
                else deq.push_back(Room(nx, ny, cur.broke + 1));
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