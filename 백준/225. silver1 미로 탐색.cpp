/////////// 메모리 초과 틀린 이유
// 항상 넣을 때 visited check를 하다가
// 종종 수업을 들을 때 뺄 때 visited를 check하는 것이 기억나서
// 갑자기 그렇게 하고싶어서 그렇게 했더니... 틀렸음 ㅎㅎㅎㅎ

#include <iostream>
#include <string>
#include <queue>

using namespace std;

int N, M;
string* board;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int bfs(){
    queue<pair<int, int>> que;
    que.emplace(0, 0);
    board[0][0] = '0'; /////////////////// 틀린 부분

    int cnt = 0;
    while(!que.empty()){
        cnt += 1;
        for (int i = 0, size = que.size(); i < size; i++) {
            pair<int, int> cur = que.front(); que.pop();

            for (int d = 0; d < 4; d++) {
                int nx = cur.first + dx[d];
                int ny = cur.second + dy[d];

                if(nx < 0 || ny < 0 || nx >= N || ny >= M || board[nx][ny] == '0') continue;

                // 도착했으면
                if(nx == N-1 && ny == M-1) return cnt + 1;

                // 아직 도착 안함
                que.emplace(nx, ny);
                board[nx][ny] = '0'; /////////////////// 틀린 부분
            }
        }
    }

    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie();

    cin >> N >> M;
    board = new string[N];

    for (int i = 0; i < N; i++) {
        cin >> board[i];
    }

    cout << bfs();
}