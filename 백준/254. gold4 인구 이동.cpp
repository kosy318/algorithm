#include <iostream>
#include <queue>
#include <map>

using namespace std;

int N, L, R;
int A[50][50];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

map<int, pair<int, vector<pair<int, int>>>> color_cnt; // color에 따른, <총 인구수, 위치 값들>

void push(int color, vector<vector<int>> &visited, int &x, int &y, queue<pair<int, int>> &que) {
    que.emplace(x, y);
    visited[x][y] = true;
    color_cnt[color].first += A[x][y];
    color_cnt[color].second.emplace_back(x, y);
}

void coloring(int &color, vector<vector<int>> &visited, int &i, int &j) {
    color_cnt.emplace(color, make_pair(0, vector<pair<int, int>>()));

    queue<pair<int, int>> que;

    push(color, visited, i, j, que);

    while(!que.empty()){
        int x = que.front().first;
        int y = que.front().second;
        que.pop();

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if(nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
            if(visited[nx][ny]) continue;
            if(abs(A[x][y] - A[nx][ny]) < L || abs(A[x][y] - A[nx][ny]) > R) continue;

            push(color, visited, nx, ny, que);
        }
    }

    color += 1;
}

bool open(){
    color_cnt.clear();

    vector<vector<int>> visited(N, vector<int>(N, false));
    int color = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if(!visited[i][j]) coloring(color, visited, i, j);
        }
    }

    return color != N * N;
}

void move(){
    for (auto color: color_cnt) {
        for(auto point : color.second.second){
            A[point.first][point.second] = color.second.first / color.second.second.size();
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> L >> R;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> A[i][j];
        }
    }

    int cnt = 0;
    while (open()) {
        move();

        cnt += 1;
    }

    cout << cnt;
}