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
    if(cnt[x][y] != -1) return cnt[x][y]; // �̹� �湮�� ��
    cnt[x][y] = 0; // �湮 ó��

    visited[x][y] = true;
    for (int d = 0; d < 4; d++) {
        int nx = x + board[x][y]*dx[d];
        int ny = y + board[x][y]*dy[d];

        if(nx < 0 || ny < 0 || nx >= N || ny >= M || board[nx][ny] == 0) {
            cnt[x][y] = max(cnt[x][y], 1); // �ִ븦 ���ؾ��ϱ� ����
            continue;
        }

        if(visited[nx][ny]){ // �� ��Ʈ�� �ѹ��̶� nx, ny�� �湮�� ���� �־��ٸ� cycle�� ����� ��
            cout << -1;
            exit(0);
        }
        cnt[x][y] = max(cnt[x][y], dfs(nx, ny) + 1); // �ִ븦 ���ؾ��ϱ� ����
    }
    visited[x][y] = false;

    return cnt[x][y]; // ������ ������;;
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

    // �ʱ�ȭ�ϴ� ���� �߸� �˰��־���..? ���ݱ���..?
    memset(cnt, -1, sizeof(cnt));

    cout << dfs();
}