#include <deque>

using namespace std;

#define MAX_CARD 50000

struct Table {
    int joker; // 현재 조커가 몇점
    int begin, end; // 제일 왼쪽과 오른쪽 카드 기억
    int cards[MAX_CARD * 2 + 5];
    deque<int> idx_list[20][20]; // idx_list[joker][score] := 조커의 점수가 joker일 때, 점수가 score인 인덱스 리스트
    // 예를 들어, 현재 joker = 9점이고, findNumber의 타겟 점수가 19점이라면, 우리는 idx_list[9][19] => 원하는 인덱스 리스트를 바로 알 수 있다.

    void update_idx(int idx, int mdir) {
        int sum = 0;
        int joker_cnt = 0;
        for (int i = 0; i < 4; i++) {
            if (cards[idx + i] == -1)
                joker_cnt++; // 초커 카드 개수 세기
            else
                sum += cards[idx + i]; // 조커를 제외한 카드 값을 추가
        }
        for (int i = 0; i < 20; i++) { // 조커 점수가 i라고 가정하자
            int num = (sum + (joker_cnt * i)) % 20;
            if (mdir == 0)
                idx_list[i][num].push_front(idx); // 왼쪽에 붙임
            else
                idx_list[i][num].push_back(idx); // 오른쪽에 붙임
        }
    }

    void init(int mJoker, int mNumbers[5]) { // mJorker는 1~30까지 가지는데
        joker = mJoker % 20; // 우리는 어차피 20으로 나눌거니까 20으로 하면됨
        begin = end = MAX_CARD; // 처음엔 50000에서 시작하도록 세팅
        for (int i = 0; i < 20; i++) { // 모든 idxList를 초기화
            for (int j = 0; j < 20; j++) {
                idx_list[i][j].clear();
            }
        }
        for (int i = 0; i < 5; i++) { // 최초 5장 추가
            cards[end + i] = mNumbers[i];
        }
        end += 5; // end가 5장만큼 증가
        for (int i = 0; i < 2; i++) {
            update_idx(MAX_CARD + i, 1);
        }
    }

    void push_front(int mNumbers[5]) { // 카드를 왼쪽에 추가
        begin -= 5; // begin을 5칸 땡겨줌
        for (int i = 0; i < 5; i++) { // 땡겨준 위치에 카드 추가
            cards[begin + i] = mNumbers[i];
        }
        int target = begin;
        for (int i = 4; i >= 0; i--) {
            update_idx(target + i, 0);
        }
    }

    void push_back(int mNumbers[5]) { // 카드를 오른쪽에 추가
        for (int i = 0; i < 5; i++) {
            cards[end + i] = mNumbers[i];
        }
        int target = end - 3;
        end += 5;
        for (int i = 0; i < 5; i++) {
            update_idx(target + i, 1);
        }
    }

    int find(int mNum, int mNth) { // mNum을 만족하는 리스트 중 mNth번째 리스트 구하기
        auto &list = idx_list[joker][mNum]; // joker값이고 mNum을 만족하는 리스트 맨 앞 index들
        if (mNth > list.size())
            return -1;
        return list[mNth - 1];
    }

    void change_joker(int mJoker) { // 조커 점수 바꾸기
        joker = mJoker % 20;
    }
};

Table t; // 테이블 생성

/*
각 테스트 케이스의 처음에 호출된다.
처음 테이블에 나열할 카드 5장의 정보가 mNumbers 배열로 주어진다.
나열 시에는 5장의 카드를 배열 내의 순서대로 왼쪽에서 오른쪽으로 나열한다.
그리고, 조커 값이 mJoker로 주어진다.

Parameters
mJoker : 조커 카드에서 사용할 조커 값 (1 ≤ mJoker ≤ 30)
mNumbers[] : 주어지는 카드에 적혀있는 수 (1 ≤ mNumbers[] ≤ 30 or mNumbers[] = -1)
*/
void init(int mJoker, int mNumbers[5]) {
    t.init(mJoker, mNumbers);
}

/*
테이블에 나열할 5장의 카드 정보가 mNumbers 배열에 주어진다.
나열 시에는 5장의 카드를 배열 내의 순서대로 왼쪽에서 오른쪽으로 나열한다.
mDir이 0인 경우 테이블에 나열되어 있는 카드들 가장 왼쪽에, 1인 경우 가장 오른쪽에 나열한다.

Parameters
mDir : 카드를 나열할 방향 (0 ≤ mDir ≤ 1)
mNumbers[] : 주어지는 카드에 적혀있는 수 (1 ≤ mNumbers[] ≤ 30 or mNumbers[] = -1)
*/
void putCards(int mDir, int mNumbers[5]) {
    if (mDir == 0) { // 카드를 왼쪽에 추가
        t.push_front(mNumbers);
    }
    else { // 카드를 오른쪽에 추가
        t.push_back(mNumbers);
    }
}

/*
테이블에 나열된 카드들 중에서 인접한 카드의 계산 결과가 mNum인 mNth 번째 카드를 찾고 그 카드와 오른쪽 3개의 카드에 적힌 수를 ret 배열에 기록한다.
조건에 맞는 카드들을 찾은 경우 1을, 찾을 수 없는 경우 0을 반환한다.
0을 반환하는 경우 ret 배열은 무시해도 된다.
※ 자세한 계산 방법은 문제 윗부분에 설명되어 있다.

Parameters
mNum : 찾아야 하는 계산 결과값 (0 ≤ mNum ≤ 19)
mNth : 찾아야 하는 결과값이 나와야 하는 횟수 (1 ≤ mNth ≤ 1,000)
ret[] : 찾은 카드에 적힌 수 (조커 카드의 경우 -1)

return
조건에 맞는 카드를 찾았으면 1, 아니면 0
*/
int findNumber(int mNum, int mNth, int ret[4]) {
    int idx = t.find(mNum, mNth); // 찾은 index 값
    if (idx == -1)
        return 0;

    // 구하고자 하는 값이 있다면
    for (int i = 0; i < 4; i++) {
        ret[i] = t.cards[idx + i]; // 찾은 index값에서부터 4개의 값을 ret에 담음
    }
    return 1;
}

/*
조커 카드에서 사용할 조커 값을 mValue로 변경한다.

Parameters
mValue : 변경할 조커 값 (1 ≤ mValue ≤ 30)
*/
void changeJoker(int mValue) {
    t.change_joker(mValue);
}

///////////////////////////////////////////////////////////////

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int mJoker, int mNumbers[5]);
extern void putCards(int mDir, int mNumbers[5]);
extern int findNumber(int mNum, int mNth, int ret[4]);
extern void changeJoker(int mValue);

#define CMD_INIT 100
#define CMD_PUT 200
#define CMD_FIND 300
#define CMD_CHANGE 400

#define MAX_CARD_NUM 5
#define MAX_RET_NUM 4

static bool run()
{
    int query_num;
    scanf("%d", &query_num);

    int ret, ans;
    int numbers[MAX_CARD_NUM];
    bool ok = false;

    for (int q = 0; q < query_num; q++)
    {
        int query;
        scanf("%d", &query);

        if (query == CMD_INIT)
        {
            int joker;
            scanf("%d", &joker);
            for (int i = 0; i < MAX_CARD_NUM; i++)
                scanf("%d", &numbers[i]);
            init(joker, numbers);
            ok = true;
        }
        else if (query == CMD_PUT)
        {
            int dir;
            scanf("%d", &dir);
            for (int i = 0; i < MAX_CARD_NUM; i++)
                scanf("%d", &numbers[i]);
            putCards(dir, numbers);
        }
        else if (query == CMD_FIND)
        {
            int num, Nth;
            int ret_numbers[MAX_RET_NUM];
            int ans_numbers[MAX_RET_NUM];
            scanf("%d %d %d", &num, &Nth, &ans);
            ret = findNumber(num, Nth, ret_numbers);
            if (ans != ret)
            {
                ok = false;
            }
            if (ans == 1)
            {
                for (int i = 0; i < MAX_RET_NUM; i++)
                {
                    scanf("%d", &ans_numbers[i]);
                    if (ans_numbers[i] != ret_numbers[i])
                    {
                        ok = false;
                    }
                }
            }
        }
        else if (query == CMD_CHANGE)
        {
            int value;
            scanf("%d", &value);
            changeJoker(value);
        }
    }
    return ok;
}
int main()
{
    setbuf(stdout, NULL);
    freopen("sample_input_calc_game.txt", "r", stdin);

    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }
    return 0;
}