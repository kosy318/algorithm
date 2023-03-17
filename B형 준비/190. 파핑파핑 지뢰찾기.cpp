/*
 * 그래프 : 정점과 간선이 존재하는 것
 * 정점과 간선을 저장하는 법 -> 인접 행렬/리스트
 * 인접 행렬 : 임의의 두 점에 대해서 간선이 존재하는지 빠르게 확인이 가능 -> 메모리 초과 주의
 * 인접 리스트 : 메모리 괜찮 -> 두 점에 대해 간선이 존재하는지 확인 어려움
 */
/*
 * DFS : SCC
 * BFS : 탐색 + 최소 간선 개수
 */
#include<iostream>
#include<string>
#include<queue>

using namespace std;

string* map;
int N, ans; // N : 지뢰찾기 표의 크기

int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
int dy[] = {0, 0, -1, 1, 1, -1, -1, 1};

bool noMine(int x, int y){
    for(int i=0; i<8; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];

        if(nx<0 || ny<0 || nx>=N || ny>=N) continue;
        if(map[nx][ny] == '*') return false; // 주변에 지뢰가 있으면 false
    }

    return true; // 주변에 지뢰가 없으면 true
}

void click(int x, int y){
    queue<pair<int, int>> que;
    que.push({x, y});
    map[x][y] = '-'; // 방문했음을 표시

    while(!que.empty()){
        pair<int, int> cur = que.front(); que.pop();
        map[cur.first][cur.second] = '-';

        for(int i=0; i<8; i++){
            int nx = cur.first + dx[i];
            int ny = cur.second + dy[i];
            if(nx<0 || ny<0 || nx>=N || ny>=N || map[nx][ny]!='.') continue; // 넘치거나 지뢰가 없는 곳이 아니면

            if(noMine(nx, ny)) que.push({nx, ny}); // 주변에 지뢰가 없으면 또 돌아야하므로 que에 넣음
            map[nx][ny] = '-';
        }
    }
}

void solve(){
    //TODO::0인 부분을 먼저 클릭한다!!
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(map[i][j] == '.' && noMine(i, j)){ // 지뢰가 없는 곳이고 주변에도 지뢰가 없으면
                click(i, j);  // 거기를 클릭해서 주변의 숫자들을 표시해준다.
                ans++; // 답 증가
            }
        }
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(map[i][j] == '.'){
                ans++; // 주변에 지뢰가 0개인 곳은 다 눌렀으므로 나머지를 눌러주면된다.
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for(int t=1; t<=T; t++){
        cin >> N;

        map = new string[N];
        ans = 0;

        for(int i=0; i<N; i++){
            cin >> map[i]; // * : 지뢰가 있음, . : 지뢰가 없음
        }
        solve();

        cout << "#" << t << " " << ans << "\n";
    }
}