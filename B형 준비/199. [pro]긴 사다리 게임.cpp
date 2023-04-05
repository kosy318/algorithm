/*
 * Tree Map vs Hash Map
 * Hash Map : key값이 주어지면 value값을 알려줌.
 *            key값을 hash 숫자로 바꿔서 기억함.
 *            삽입, 삭제, 조회가 가능. O(1)
 *            key값에 대해 순서대로 보는 것이 안됨
 * Tree Map : 삽입, 삭제, 조회가 O(log N)
 *            key에 대해서 순차 조회가 가능
 *            key에 대해 lower upper를 지원
 */

#include <map>

using namespace ::std;

const int N = 100;
const int MAX_NUM_NODE = 400210;
const int LAST_START_NODE = N;
const int FIRST_END_NODE = MAX_NUM_NODE - N - 5;

struct Node { // doubly linked list
    Node *prev;
    Node *next;
} node[MAX_NUM_NODE]; // 정점 배열

void link(Node *front, Node *back) {
    front->next = back;
    back->prev = front;
}

// 세로 줄마다 만들어줌
map<int, Node *> node_map[N + 1]; // 어떤 y좌표가 어느 정점에 연결되는지
Node *new_node;

/*
[제약사항]
1. 각 테스트 케이스 시작 시 init() 함수가 호출된다.
2. 각 테스트 케이스에서 add() 함수의 호출 횟수는 200,000 이하이다.
3. 각 테스트 케이스에서 remove() 함수의 호출 횟수는 5,000 이하이다.
4. 각 테스트 케이스에서 numberOfCross() 함수의 호출 횟수는 500 이하이다. -> 시뮬을 해도 되겠다..
5. 각 테스트 케이스에서 participant() 함수의 호출 횟수는 500 이하이다. -> 시뮬을 해도 되겠다..
6. 사다리 게임을 진행했을 때, 한 참가자가 지나게 되는 가로줄의 개수는 항상 5,000개 이하이다. -> numberOfCross랑 participant를 시뮬해도 되겠다..
*/

/// 세로줄과 가로줄이 만나는 위치를 기억하자

/*
각 테스트 케이스의 처음에 호출된다.
테스트 케이스의 시작 시, 모든 세로줄이 그어져 있다.
테스트 케이스의 시작 시, 가로줄은 없다.
 */
void init() {
    for (int i = 1; i <= N; i++) {
        node_map[i].clear();
        node_map[i][0] = node + i;
        node_map[i][1000000000] = node + FIRST_END_NODE + i - 1;
        link(node + i, node + FIRST_END_NODE + i - 1);
    }
    new_node = node + N + 1;
}

/*
Y 좌표가 mY인 가로줄이 존재하지 않음이 보장된다.

(mX, mY)와 (mX+1, mY)를 잇는 가로줄을 추가한다.

Parameters
mX : X 좌표 (1 ≤ mX ≤ 99)
mY : Y 좌표 (1 ≤ mY ≤ 999,999,999) -> 배열로 잡을 수 없다!!!!!
*/
void add(int mX, int mY) { // O(log N)
    Node *now_left = new_node++;
    Node *now_right = new_node++;

    Node *prev_left = (--node_map[mX].upper_bound(mY))->second;
    Node *prev_right = (--node_map[mX + 1].upper_bound(mY))->second;

    Node *next_left = prev_left->next;
    Node *next_right = prev_right->next;

    link(prev_left, now_right);
    link(now_right, next_right);

    link(prev_right, now_left);
    link(now_left, next_left);

    node_map[mX][mY] = now_left;
    node_map[mX + 1][mY] = now_right;
}

/*
(mX, mY)와 (mX+1, mY)를 잇는 가로줄이 존재함이 보장된다.

(mX, mY)와 (mX+1, mY)를 잇는 가로줄을 삭제한다.

Parameters
mX : X 좌표 (1 ≤ mX ≤ 99)
mY : Y 좌표 (1 ≤ mY ≤ 999,999,999)
*/
void remove(int mX, int mY) { // O(log N)
    Node *now_left = node_map[mX][mY];
    Node *now_right = node_map[mX + 1][mY];

    Node *prev_left = now_right->prev;
    Node *prev_right = now_left->prev;

    Node *next_left = now_left->next;
    Node *next_right = now_right->next;

    link(prev_left, next_left);
    link(prev_right, next_right);

    node_map[mX].erase(mY);
    node_map[mX + 1].erase(mY);
}

/*
현재 맵에서 사다리 게임을 진행했을 때, mID번 참가자가 지나게 되는 가로줄의 개수를 반환한다.

mID번 참가자는 (mID, 0)에서 출발한다.

Parameters
mID : 참가자의 번호 (1 ≤ mID ≤ 100)

Returns
mID번 참가자가 지나게 되는 가로줄의 개수
*/
int numberOfCross(int mID) { // O(5000)
    int ret = -1;
    Node *now = node + mID;
    while (now < node + FIRST_END_NODE) {
        ret++; // 이동할 때마다 가로줄 하나씩 지나가는 것임
        now = now->next;
    }
    return ret;
}

/*
현재 맵에서 사다리 게임을 진행했을 때, (mX, mY)를 지나게 되는 참가자의 번호를 반환한다.

(mX, mY)는 가로줄과 세로줄이 만나는 지점이 아님이 보장된다.
(mX, mY)를 지나게 되는 참가자는 항상 존재하며, 유일하다.

Parameters
mX : X 좌표 (1 ≤ mX ≤ 100)
mY : Y 좌표 (1 ≤ mY ≤ 1,000,000,000)

Returns
(mX, mY)를 지나게 되는 참가자의 번호
*/
int participant(int mX, int mY) { // O(5000)
    Node *now = (--node_map[mX].upper_bound(mY))->second; // mY 위쪽에 가로줄이 놓인 node를 찾음(그 가로줄을 지나는 애들이 mY를 지남)
    while (now > node + LAST_START_NODE)
        now = now->prev;
    return now - node;
}

//////////////////////////////////////////////////////////////////////

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 1
#define CMD_ADD 2
#define CMD_REMOVE 3
#define CMD_NUMBER_OF_CROSS 4
#define CMD_PARTICIPANT 5

extern void init();
extern void add(int mX, int mY);
extern void remove(int mX, int mY);
extern int numberOfCross(int mID);
extern int participant(int mX, int mY);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static bool run()
{
    int numQuery;

    int mX, mY, mID;

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
                init();
                isCorrect = true;
                break;
            case CMD_ADD:
                scanf("%d %d", &mX, &mY);
                add(mX, mY);
                break;
            case CMD_REMOVE:
                scanf("%d %d", &mX, &mY);
                remove(mX, mY);
                break;
            case CMD_NUMBER_OF_CROSS:
                scanf("%d", &mID);
                userAns = numberOfCross(mID);
                scanf("%d", &ans);
                if (userAns != ans)
                {
                    isCorrect = false;
                }
                break;
            case CMD_PARTICIPANT:
                scanf("%d %d", &mX, &mY);
                userAns = participant(mX, mY);
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
    freopen("sample_input_long_ladder.txt", "r", stdin);

    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}