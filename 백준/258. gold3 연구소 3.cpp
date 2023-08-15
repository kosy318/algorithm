#include <iostream>
#include <queue>

using namespace std;

/* 내가 틀린 부분
 * * 바이러스가 연속으로 있는 경우도 다음 것을 활성화 시키는 데에 시간이 1 씩 더 든다
 * * 활성화 되지 않은 바이러스더라도 퍼져있는 것으로 본다.
 * * que가 empty인 것도 다 퍼뜨린 조건으로 생각했는데, 빈 칸을 다 채우고 비활성화된 바이러스만 que에 남아있는 경우도 존재할 수 있으므로 que.empty()는 조건에 넣으면 안된다.
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

void spread(vector<vector<bool>> &visited, priority_queue<pair<Point, int>, vector<pair<Point, int>>, comp> &que, const Point &cur, int time, int& cnt) {
    for (int d = 0; d < 4; d++) {
        int nx = cur.x + dx[d];
        int ny = cur.y + dy[d];

        if(nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
        if(visited[nx][ny] || lab[nx][ny] == 1) continue;

        visited[nx][ny] = true;

        que.emplace(Point(nx, ny), time + 1);
    }
}

int spread_virus() { // bfs
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    priority_queue<pair<Point, int>, vector<pair<Point, int>>, comp> que; // second := 시간
    int cnt = 0;

    for(Point& p: activate){
        que.emplace(p, 0);
        visited[p.x][p.y] = true;
    }

    while (true) {
        auto [cur, time] = que.top(); que.pop();
//        cout << cur.x << ", " << cur.y << " time: " << time << endl;
        if(lab[cur.x][cur.y] == 0) cnt += 1;

        spread(visited, que, cur, time, cnt);

        if(cnt == totalCnt){ // 틀린 부분 : que가 empty일 필요가 없음 (비활성 virus가 남아있을 수 있음)
//            cout << time << endl;
            return time;
        } else if(time >= answer || que.empty()){
//            cout << -1 << endl;
            return 3000;
        }
    }
}

void comb(int cnt = 0, int start = 0){
    if(cnt == M){
        // TODO: 조합 생성 완료 -> 선택한 바이러스 기준으로 퍼트리기
//        cout << "start" << endl;
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
            // 틀린 부분 : 활성화된 바이러스가 아니라 비활성화된 바이러스가 놓여있는 것도 퍼뜨린 것에 해당됨
            if(lab[i][j] == 0) totalCnt += 1;
        }
    }
//    cout << "totalCnt: " << totalCnt << endl;

    if(totalCnt == 0){
        cout << 0;
        exit(0);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    input();

    comb();

    cout << ((answer == 3000? -1 : answer));
}