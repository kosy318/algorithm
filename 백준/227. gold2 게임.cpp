#include<iostream>
#include<string>
#include<cstring> // memset

using namespace std;

int N, M;
int board[50][50];
int cnt[50][50];
bool visited[50][50];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int dfs(int x = 0, int y = 0) {
    if(cnt[x][y] != -1) return cnt[x][y]; // 이미 방문한 곳
    cnt[x][y] = 0; // 방문 처리

    visited[x][y] = true;
    for (int d = 0; d < 4; d++) {
        int nx = x + board[x][y]*dx[d];
        int ny = y + board[x][y]*dy[d];

        if(nx < 0 || ny < 0 || nx >= N || ny >= M || board[nx][ny] == 0) {
            cnt[x][y] = max(cnt[x][y], 1); // 최대를 구해야하기 때문
            continue;
        }

        if(visited[nx][ny]){ // 이 루트에 한번이라도 nx, ny에 방문한 적이 있었다면 cycle이 생기는 것
            cout << -1;
            exit(0);
        }
        cnt[x][y] = max(cnt[x][y], dfs(nx, ny) + 1); // 최대를 구해야하기 때문
    }
    visited[x][y] = false;

    return cnt[x][y]; // 리턴을 빼먹음;;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        string inp_str;
        cin >> inp_str;
        for (int j = 0; j < M; j++) {
            if(inp_str[j] == 'H') board[i][j] = 0;
            else board[i][j] = inp_str[j] - '0';
        }
    }

    // 초기화하는 법을 잘못 알고있었다..? 지금까지..?
    memset(cnt, -1, sizeof(cnt));

    cout << dfs();
}