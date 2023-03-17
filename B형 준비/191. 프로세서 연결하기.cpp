// 가장자리 애들은 신경쓸 필요가 없음
// 최대한 많은 core에 연결 -> 전선의 길이 최소
// core 개수가 12개 이하로 매우 작음 -> 완탐!!!

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ans := 최대 코어 연결 방법 중 최소 전선 길이
// maxCnt := 탐색한 방법 중, 연결한 최대 코어 개수
int ans, N, maxCnt;
int** map;
vector<pair<int, int>> core_list;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool in_range(int x, int y){
    return 0 <= x && x < N && 0 <= y && y < N;
}

int extend(pair<int, int> point, int d){ // 어떤 위치에서 어떤 방향으로 끝까지 갈 수 있는지
    int nx = point.first + dx[d];
    int ny = point.second + dy[d];
    int res = 0;

    while (in_range(nx, ny)) {
        if (map[nx][ny] != 0) { // 벽에 도달하기 전 core나 전선을 만남
            return -1;
        }
        nx += dx[d];
        ny += dy[d];
    }

    // 여기까지 나오면 벽까지 연결 가능하다는 의미임
    // 벽까지 전선 연결
    nx = point.first + dx[d];
    ny = point.second + dy[d];
    while (in_range(nx, ny)) {
        map[nx][ny] = 2; // 현재 위치에 전선이 놓여있다는 것을 표시
        nx += dx[d];
        ny += dy[d];
        res++;
    }

    return res; // 전선 길이
}

// 전선 연결한거 회수하기
void rollback(pair<int, int> point, int d){
    int nx = point.first + dx[d];
    int ny = point.second + dy[d];
    while (in_range(nx, ny)) {
        map[nx][ny] = 0;
        nx += dx[d];
        ny += dy[d];
    }
}

// idx := 코어 번호
// length := 현재 사용한 전산 총길이
// cnt := 코어 연결 성공 개수
void backtracking(int idx=0, int length=0, int cnt=0){
    if (cnt > maxCnt) { // 코어 연결 성공 개수가 전에 기록한것보다 많다면
        maxCnt = cnt; // 최대 코어 개수를 갱신
        ans = length; // 최소 전선 길이를 갱신
    } else if (cnt == maxCnt) { // 코어 연결 성공 개수가 전에 기록했던것과 같다면
        ans = min(ans, length); // 둘 중 전선 길이가 작은걸로 바꿈
    }

    if(idx == core_list.size()){ // 만약 모든 코어를 다 돌았다면 끝냄
        return;
    }

    for (int d = 0; d < 4; d++) {
        int wire_length = extend(core_list[idx], d);
        if (wire_length == -1) {
            continue;
        }

        backtracking(idx + 1, length + wire_length, cnt + 1);
        rollback(core_list[idx], d);
    }

    backtracking(idx + 1, length, cnt); // 지금 core를 연결하지 말자
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        ans = 0;
        cin >> N;

        // map 초기화
        ans = 0;
        maxCnt = 0;
        map = new int*[N];
        for (int i = 0; i < N; i++) {
            map[i] = new int[N];
        }

        core_list = vector<pair<int, int>>();

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> map[i][j];
                if (i == 0 || j == 0 || i == N - 1 || j == N - 1) { // 끝에 있으면 지나감
                    continue;
                }
                if (map[i][j] == 1) {
                    core_list.emplace_back(i, j); // core가 있는 좌표 넣어둠
                }
            }
        }

        backtracking();

        cout << "#" << t << " " << ans << "\n";
    }
}