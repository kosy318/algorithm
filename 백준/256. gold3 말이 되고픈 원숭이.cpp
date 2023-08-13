#include <iostream>
#include <queue>

using namespace std;

struct Node{
    int x, y;
    int cnt;
    int k;

    Node(int x, int y, int cnt, int k = 0) : x{x}, y{y}, cnt{cnt}, k{k}{}
};

int K; // K번만 말의 움직임으로 이동 가능하다
int N, M; // NxM 격자
vector<vector<bool>> blocked;

vector<pair<int, int>> horse_move = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int bfs(){
    vector<vector<vector<bool>>> visited(N, vector<vector<bool>>(M, vector<bool>(K+1, false)));

    queue<Node> que;
    que.emplace(0, 0, 0, K);
    visited[0][0][K] = true;

    while(!que.empty()){
        Node cur = que.front(); que.pop();

        if(cur.x == N-1 && cur.y == M-1) return cur.cnt;

        if(cur.k > 0 ){
            // TODO: 말 움직임으로 움직임
            for(pair<int, int> move: horse_move) {
                int nx = cur.x + move.first;
                int ny = cur.y + move.second;

                if (nx < 0 || ny < 0 || nx >= N || ny >= M || blocked[nx][ny] || visited[nx][ny][cur.k - 1])continue;

                que.emplace(nx, ny, cur.cnt + 1, cur.k - 1);
                visited[nx][ny][cur.k - 1] = true;
            }
        }

        for(int d = 0; d < 4; d++){
            int nx = cur.x + dx[d];
            int ny = cur.y + dy[d];

            if (nx < 0 || ny < 0 || nx >= N || ny >= M || blocked[nx][ny] || visited[nx][ny][cur.k])continue;

            que.emplace(nx, ny, cur.cnt + 1, cur.k);
            visited[nx][ny][cur.k] = true;
        }
    }

    return -1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> K >> M >> N;

    blocked = vector<vector<bool>>(N, vector<bool>(M));

    {
        int num;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cin >> num;
                blocked[i][j] = (num == 1);
            }
        }
    }

    cout << bfs();
}