/*
 * 격자 모양의 섬, 섬의 크기는 NxN이며, 바다에 둘러쌓여 있다.
 * 숫자는 각 지역의 고도를 나타내고
 * 해수면이 mSeaLevel만큼 상승하면, 바닷물은 고도가 mSeaLevel-1이하인 지역으로 침투할 수 있게 된다.
 * 단, 바닷물은 상하좌우 4방향으로만 육지에 침투할 수 있다.
 *
 * 1xM크기의 구조물을 통해, 섬을 어느정도 지킬 수 있을지??
 * 구조물의 각 숫자는 각 부분의 높이를 나타낸다.
 * 구조물은 섬에 설치핡 수 있고, 섬의 M개 지역에 딱 들어맞도록 설치돼야한다.
 * 구조물이 설치된 M개의 지역의 고도는 모두 일치해야한다.
 * 일치하지 않을거 같으면 구조물을 설치할 수 없다.
 * 구조물은 90도씩 회전 할 수 있다.
 */

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 1
#define CMD_NUMBER_OF_CANDIDATE 2
#define CMD_MAX_AREA 3

extern void init(int N, int mMap[20][20]);
extern int numberOfCandidate(int M, int mStructure[5]);
extern int maxArea(int M, int mStructure[5], int mSeaLevel);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static int mMap[20][20];
static int mStructure[5];

static bool run()
{
    int numQuery;
    int N, M, mSeaLevel;
    int userAns, ans;

    bool isCorrect = false;

    scanf("%d", &numQuery);

    for (int i = 0; i < numQuery; ++i)
    {
        int cmd;
        scanf("%d", &cmd);

        switch (cmd)
        {
            case CMD_INIT:
                scanf("%d", &N);
                for (int j = 0; j < N; j++)
                    for (int k = 0; k < N; k++)
                        scanf("%d", &mMap[j][k]);
                init(N, mMap);
                isCorrect = true;
                break;
            case CMD_NUMBER_OF_CANDIDATE:
                scanf("%d", &M);
                for (int j = 0; j < M; j++)
                    scanf("%d", &mStructure[j]);
                userAns = numberOfCandidate(M, mStructure);
                scanf("%d", &ans);
                if (userAns != ans)
                {
                    isCorrect = false;
                }
                break;
            case CMD_MAX_AREA:
                scanf("%d", &M);
                for (int j = 0; j < M; j++)
                    scanf("%d", &mStructure[j]);
                scanf("%d", &mSeaLevel);
                userAns = maxArea(M, mStructure, mSeaLevel);
                scanf("%d", &ans);
                if (userAns != ans)
                {
                    isCorrect = false;
                }
                break;
            default:
                isCorrect = false;
                break;
        }
    }
    return isCorrect;
}

int main()
{
    setbuf(stdout, NULL);
    freopen("sample_input.txt", "r", stdin);

    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////


#include <algorithm>
#include <queue>

using namespace std;

const int MAX_N = 20;
const int MAX_HASH = 9999;

int n;
int init_map[MAX_N + 2][MAX_N + 2];
int modified_map[MAX_N + 2][MAX_N + 2];

struct Candidate {
    int r;
    int c;
    bool is_horizontal;
    bool is_reverse;

    Candidate(int r, int c, bool is_horizontal, bool is_reverse):
        r(r), c(c), is_horizontal(is_horizontal), is_reverse(is_reverse){}
};

vector<vector<Candidate>> candidate(MAX_HASH + 1);

/*
 * 각 테스트 케이스의 처음에 호출된다.
 * 섬은 NxN 크기의 정사각형 모양이며, 1x1 크기의 정사각형 모양인 지역들로 이루어져 있다.
 */
// N := 섬의 한 변의 길이; 5 ≤ N ≤ 20              => 매우 작은 숫자!
// mMap := 섬의 각 지역의 고도; 1 ≤ mMap[][] ≤ 5
void init(int N, int mMap[20][20]) {
    n = N; // 섬의 한 변의 길이를 저장

    // mMap 배열을 modified_map과 init_map으로 복사
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            modified_map[i+1][j+1] = init_map[i+1][j+1] = mMap[i][j];
        }
    }

    // 전처리: 모든 1*L짜리 구조물에 대해 hash값 미리 계산 해놓기
    // O(20*N^3)
    for (int length = 2; length <= 5; length++) { // 구조물의 길이를 2부터 5까지 반복
        // 구조물을 탐색하여 hash 값을 계산하고 후보 구조물로 등록
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j + length - 1 <= n; j++) {
                int hash = 0; // 구조물의 hash 값
                // 구조물 내 각 블록의 높이 차이를 계산하여 hash 값을 구함
                // [4, 2, 3, 2] -> [2, -1, 1] -> [7, 4, 6] -> 746
                for (int k = 0; k + 1 < length; k++) {
                    // 10을 곱하는 이유 -> 10진수로 만드려고
                    // 5를 더하는 이유는 10진수를 만들기 위함임, 4를 더하면 0때문에 안됨 -> 0이 앞자리에 나오면 안되기 때문
                    hash = hash*10 + (init_map[i][j+k+1] - init_map[i][j+k] + 5);
                }
                // 구조물 후보 리스트에 구조물 정보를 저장
                // i, j 위치에서 가로로 순서대로
                candidate[hash].emplace_back(i, j, true, false);

                int reverse_hash = 0; // 좌우 반전 구조물의 hash 값
                // 구조물 내 각 블록의 높이 차이를 계산하여 대칭 구조물의 hash 값을 구함
                for (int k = length - 1; k - 1 >= 0; k--) {
                    reverse_hash = reverse_hash*10 + (init_map[i][j+k-1] - init_map[i][j+k] + 5);
                }
                // 구조물이 대칭이 아닌 경우에만 구조물 후보 리스트에 저장
                if (reverse_hash != hash) { // 구조물이 대칭이 아닌 경우에만 저장
                    candidate[reverse_hash].emplace_back(i, j, true, true);
                }
            }
        }
        // 구조물을 탐색하여 hash 값을 계산하고 후보 구조물로 등록
        for (int i = 1; i + length - 1 <= n; i++) {
            for (int j = 1; j <= n; j++) {
                int hash = 0; // 구조물의 hash 값
                // 구조물 내 각 블록의 높이 차이를 계산하여 hash 값을 구함
                for (int k = 0; k + 1 < length; k++) {
                    hash = hash * 10 + (init_map[i + k + 1][j] - init_map[i + k][j] + 5);
                }
                // 구조물 후보 리스트에 구조물 정보를 저장
                // i, j 위치에서 세로로 순서대로
                candidate[hash].emplace_back(i, j, false, false);

                int reverse_hash = 0; // 상하 반전 구조물의 hash 값
                // 구조물 내 각 블록의 높이 차이를 계산하여 대칭 구조물의 hash 값을 구함
                for (int k = length - 1; k - 1 >= 0; k--) {
                    reverse_hash = reverse_hash * 10 + (init_map[i + k - 1][j] - init_map[i + k][j] + 5);
                }
                // 구조물이 대칭이 아닌 경우에만 구조물 후보 리스트에 저장
                if (reverse_hash != hash) { // 구조물이 대칭이 아닌 경우에만 저장
                    candidate[reverse_hash].emplace_back(i, j, false, true);
                }
            }
        }
    }
}

/*
 * 구조물 mStructure를 1개 설치했을 때, 나타날 수 있는 경우의 수를 반환한다.
 * 설치 지역이 모두 동일하면, 같은 경우로 취급한다.
 * 설치 지역이 1개라도 다르다면, 다른 경우로 취급한다.
 */
// M := 구조물의 크기 (1 ≤ M ≤ 5)
// mStructure := 구조물의 각 부분의 높이 (1 ≤ mStructure[] ≤ 5)
// O(M)
int numberOfCandidate(int M, int mStructure[5]) {
    if (M == 1) {
        return n * n;
    }

    // [4, 2, 3, 2] -> [2, -1, 1] -> [7, 4, 6] -> 746
    int hash = 0;
    for (int i = 0; i + 1 < M; i++)
        // 10을 곱하는 이유 -> 10진수로 만드려고
        // 5를 더하는 이유는 10진수를 만들기 위함임, 4를 더하면 0때문에 안됨 -> 0이 앞자리에 나오면 안되기 때문
        hash = hash * 10 + (mStructure[i] - mStructure[i + 1] + 5);
    return candidate[hash].size(); // 구조물을 설치할 수 있는 경우의 수
}

bool check[MAX_N + 2][MAX_N + 2];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

/*
 * 이차원 배열 mMap을 탐색하면서, 높이가 mSeaLevel보다 낮은 지점을 방문하며 연결된 구역을 찾는다.
 * 방문한 지점은 check 배열에 true를 저장하여 중복 방문을 방지한다.
 * 탐색이 끝난 후, check 배열에 false가 저장된 지점들의 개수를 반환하여 최대 지역 개수를 계산한다.
 */
int unsubmergedArea(int mMap[MAX_N + 2][MAX_N + 2], int mSeaLevel) {
    queue<pair<int, int>> q; // bfs 탐색을 위한 큐
    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= n + 1; j++) {
            // 지도의 가장자리는 모두 바다로 취급하여 q에 추가하고, 방문 표시를 한다.
            if (i == 0 || i == n + 1 || j == 0 || j == n + 1) {
                q.emplace(i, j);
                check[i][j] = true;
            } else
                check[i][j] = false;
        }
    }
    while (!q.empty()) {
        pair<int, int> front = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            pair<int, int> rear = {front.first + dx[i], front.second + dy[i]};
            if (rear.first >= 1 && rear.first <= n && rear.second >= 1 && rear.second <= n) {
                if (!check[rear.first][rear.second] && mMap[rear.first][rear.second] < mSeaLevel) {
                    // 높이가 mSeaLevel보다 낮은 지역을 발견하면 q에 추가하고, 방문 표시를 한다.
                    q.push(rear);
                    check[rear.first][rear.second] = true;
                }
            }
        }
    }

    int ret = 0;
    // check 배열에서 false가 저장된 지점들의 개수를 세어 최대 지역 개수를 계산한다.
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (!check[i][j])
                ret++;
    return ret;
}

/*
 * 해수면이 mSeaLevel만큼 상승하여도 바다에 잠기지 않고 남아있는 지역의 개수가 최대가 되도록 구조물 mStructure를 1개 설치했을 때, 그 개수를 반환한다.
 * 구조물 mStructure를 설치할 방법이 없는 경우에는, -1을 반환한다.
 * 실제로 설치하지는 않음에 유의하라.
 * 즉, 각 테스트 케이스에서 섬의 각 지역의 고도는 init()에서의 상태 그대로 유지된다.
 */
// M := 구조물의 크기 (1 ≤ M ≤ 5)
// mStructure := 구조물의 각 부분의 높이 (1 ≤ mStructure[] ≤ 5)
// mSeaLevel := 해수면의 상승 폭 (1 ≤ mSeaLevel ≤ 10)
int maxArea(int M, int mStructure[5], int mSeaLevel) {
    int ret = -1; // 최대 지역 개수
    if (M == 1) { // 구조물 크기가 1인 경우
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                modified_map[i][j] = init_map[i][j] + mStructure[0];
                // 구조물을 설치했을 때, 최대 지역 개수를 받아서 원래 ret에 들어있던 최대 지역 개수를 계산하여 갱신
                ret = max(ret, unsubmergedArea(modified_map, mSeaLevel));
                modified_map[i][j] = init_map[i][j];// 구조물을 제거하여 원래 지도로 복원
            }
        }
        return ret;
    }

    int hash = 0;
    for (int i = 0; i + 1 < M; i++)
        hash = hash * 10 + (mStructure[i] - mStructure[i + 1] + 5);

    for (Candidate wall : candidate[hash]) { // 가능한 위치에 대해서
        if (wall.is_horizontal) { // 가로 방향으로 구조물을 설치하는 경우
            // 구조물 높이 계산
            int height = mStructure[0] + (wall.is_reverse ? init_map[wall.r][wall.c + M - 1] : init_map[wall.r][wall.c]);
            // 구조물 설치; 구조물 놓일 곳을 height로 갱신
            for (int i = 0; i < M; i++)
                modified_map[wall.r][wall.c + i] = height;
            // 구조물 설치 후 남은 지역 개수와 ret 값을 비교하여 갱신
            ret = max(ret, unsubmergedArea(modified_map, mSeaLevel));
            // 구조물 제거
            for (int i = 0; i < M; i++)
                modified_map[wall.r][wall.c + i] = init_map[wall.r][wall.c + i];
        } else {
            // 구조물 높이 계산
            int height = mStructure[0] + (wall.is_reverse ? init_map[wall.r + M - 1][wall.c] : init_map[wall.r][wall.c]);
            // 구조물 설치; 구조물 놓일 곳을 height로 갱신
            for (int i = 0; i < M; i++)
                modified_map[wall.r + i][wall.c] = height;
            // 구조물 설치 후 남은 지역 개수와 ret 값을 비교하여 갱신
            ret = max(ret, unsubmergedArea(modified_map, mSeaLevel));
            // 구조물 제거
            for (int i = 0; i < M; i++)
                modified_map[wall.r + i][wall.c] = init_map[wall.r + i][wall.c];
        }
    }
    return ret; // 최대 지역 개수
}