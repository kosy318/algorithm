/////////// �޸� �ʰ� Ʋ�� ����
// �׻� ���� �� visited check�� �ϴٰ�
// ���� ������ ���� �� �� �� visited�� check�ϴ� ���� ��ﳪ��
// ���ڱ� �׷��� �ϰ�; �׷��� �ߴ���... Ʋ���� ��������

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
    board[0][0] = '0'; /////////////////// Ʋ�� �κ�

    int cnt = 0;
    while(!que.empty()){
        cnt += 1;
        for (int i = 0, size = que.size(); i < size; i++) {
            pair<int, int> cur = que.front(); que.pop();

            for (int d = 0; d < 4; d++) {
                int nx = cur.first + dx[d];
                int ny = cur.second + dy[d];

                if(nx < 0 || ny < 0 || nx >= N || ny >= M || board[nx][ny] == '0') continue;

                // ����������
                if(nx == N-1 && ny == M-1) return cnt + 1;

                // ���� ���� ����
                que.emplace(nx, ny);
                board[nx][ny] = '0'; /////////////////// Ʋ�� �κ�
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