#include <iostream>
#include <queue>

using namespace std;

/* 내가 틀린 예제
4 2
0 1 1 0
2 1 1 2
2 1 1 2
0 1 1 0
*/

struct Point{
    int x, y;

    Point(int x, int y) : x(x), y(y) {}
    Point() {}
};

struct comp {
    bool operator()(const std::pair<Point, int>& a, const std::pair<Point, int>& b) {
        return a.second > b.second; // 오름차순으로 정렬
    }
};

int N, M; // N := 연구실 사이즈, M := 활성화 시킬 수 있는 바이러스 개수
vector<vector<int>> lab;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int totalCnt = 0;
vector<Point> virus_point;
vector<Point> activate;

int answer = 3000;

void activate_virus(vector<vector<bool>> &visited, priority_queue<pair<Point, int>, vector<pair<Point, int>>, comp> &que, const Point &next, int time, int& cnt) {
    visited[next.x][next.y] = true;
    cnt += 1;

    bool pushed = false;
    for (int d = 0; d < 4; d++) {
        int nx = next.x + dx[d];
        int ny = next.y + dy[d];

        if(nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
        if(visited[nx][ny] || lab[nx][ny] == 1) continue;

        if(lab[nx][ny] == 0 && !pushed) {
            que.emplace(next, time);
            pushed = true;
        }
        else if(lab[nx][ny] == 2){ // 비활성 바이러스가 있는 곳
            activate_virus(visited, que, Point(nx, ny), time, cnt);
        }
    }
}

void spread(vector<vector<bool>> &visited, priority_queue<pair<Point, int>, vector<pair<Point, int>>, comp> &que, const Point &cur, int time, int& cnt) {
    for (int d = 0; d < 4; d++) {
        int nx = cur.x + dx[d];
        int ny = cur.y + dy[d];

        if(nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
        if(visited[nx][ny] || lab[nx][ny] == 1) continue;

        visited[nx][ny] = true;

        if(lab[nx][ny] == 0) {
            cnt += 1;
            que.emplace(Point(nx, ny), time + 1);
        }
        // 비활성 바이러스가 활성상태로 변한다면 닿자마자 바로 사방으로 또 퍼져야하는걸까?
        else if(lab[nx][ny] == 2){ // 비활성 바이러스가 있는 곳
            // 첫번째 틀린 곳. 문제가 이해하기 너무 어려움..
            activate_virus(visited, que, Point(nx, ny), time + 1, cnt);
        }
    }
}

int spread_virus() { // bfs
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    priority_queue<pair<Point, int>, vector<pair<Point, int>>, comp> que; // second := 시간
    int cnt = 0;

    for(Point& p: activate){
        que.emplace(p, 0);
        visited[p.x][p.y] = true;
        cnt += 1;
    }

    while (true) {
        auto [cur, time] = que.top(); que.pop();
        if(time >= answer) return answer;

        spread(visited, que, cur, time, cnt);

        if(cnt == totalCnt && que.empty()){
//            cout << time << endl;
            return time;
        } else if(cnt != totalCnt && que.empty()){
//            cout << -1 << endl;
            return 3000;
        }
    }
}

void comb(int cnt = 0, int start = 0){
    if(cnt == M){
        // TODO: 조합 생성 완료 -> 선택한 바이러스 기준으로 퍼트리기
//        cout << "start" << endl;
//        for (Point p: activate) {
//            cout << p.x << ", " << p.y << endl;
//        }
        answer = min(spread_virus(), answer);
    }
    else {
        for(int i = start; i < virus_point.size(); i++){
            activate[cnt] = virus_point[i];
            comb(cnt + 1, i + 1);
        }
    }
}

void input() {
    cin >> N >> M;

    activate = vector<Point>(M);
    lab = vector<vector<int>>(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> lab[i][j];

            if(lab[i][j] == 2){
                virus_point.emplace_back(i, j);
            }
            if(lab[i][j] != 1) totalCnt += 1;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    input();

    comb();

    cout << ((answer == 3000? -1 : answer));
}