/// Tree Set == set in C++

#define nullptr		(0)

#define MAXN		(50001)
#define MAXM		(50001)
#define MAXK		(200001)

template <typename T>
void zwap(T &a, T &b)
{
    T t = a; a = b; b = t;
}

struct Robot {
    int rID;     // 로봇의 아이디
    int IQ;      // 지능
    int wID;     // 일하고 있는 작업 번호
    int begin;   // 일을 시작한 시각
    bool broken; // 고장 여부

    int maxidx, minidx; // max_heap과 min_heap에서의 위치 기억
};

Robot robot[MAXN];

struct Job { // 작업에 대한 정보
    Robot** arr; // 작업에 투입된 로봇 정보
    int n;
};

Job jobs[MAXM];

int mm;
Robot* mem[MAXK];

Robot** getRobot(int n)
{
    Robot** ret = &mem[mm];
    mm += n;

    return ret;
}

struct maxcomp
{
    void set(Robot* a, int idx) { // max heap에서의 idx setting
        a->maxidx = idx;
    }

    bool operator() (Robot* a, Robot* b) { // 가장 똑똑한 친구를 먼저 선택
        return a->IQ != b->IQ ? a->IQ < b->IQ : a->rID > b->rID;
    }
};

struct mincomp
{
    void set(Robot* a, int idx) { // min heap에서의 idx setting
        a->minidx = idx;
    }

    bool operator() (Robot* a, Robot* b) { // 가장 멍청한 친구를 먼저 선택
        return a->IQ != b->IQ ? a->IQ > b->IQ : a->rID > b->rID;
    }
};

template<typename C>
struct Que { // priority queue 직접 구현
    Robot* arr[MAXN + 1];
    int size;

    C comp;

    void init() {
        size = 0;
    }

    void init(int n, Robot heapifed[]) { // 초기화
        for (int i = 0; i < n; ++i) {
            arr[i] = &heapifed[i + 1];
            comp.set(arr[i], i);
        }

        size = n;
    }

    void push(Robot* v) { // 삽입
        arr[size] = v;
        comp.set(arr[size], size);

        int cur = size++;

        while (cur > 0)
        {
            int par = (cur - 1) / 2;
            if (comp(arr[cur], arr[par]))
                break;
            zwap(arr[cur], arr[par]);
            comp.set(arr[cur], cur);
            comp.set(arr[par], par);
            cur = par;
        }
    }

    Robot* pop() { // 제일 높은 우선순위 제거
        if (size == 0) return nullptr;

        Robot* ret = arr[0];
        arr[0] = arr[--size];
        comp.set(arr[0], 0);

        int cur = 0;
        while (cur * 2 + 1 < size)
        {
            int child = cur * 2 + 2 < size && comp(arr[cur * 2 + 1], arr[cur * 2 + 2]) ? cur * 2 + 2 : cur * 2 + 1;
            if (comp(arr[child], arr[cur]))
                break;
            zwap(arr[cur], arr[child]);
            comp.set(arr[cur], cur);
            comp.set(arr[child], child);
            cur = child;
        }

        return ret;
    }

    void remove(int idx) { // 임의의 위치 제거 O(log N)
        if (idx >= size) return;

        arr[idx] = arr[--size];
        comp.set(arr[size], idx);

        // heapify
        int cur = idx;
        while (cur * 2 + 1 < size) {
            int child = cur * 2 + 2 < size && comp(arr[cur * 2 + 1], arr[cur * 2 + 2]) ? cur * 2 + 2 : cur * 2 + 1;
            if (comp(arr[child], arr[cur]))
                break;
            zwap(arr[cur], arr[child]);
            comp.set(arr[cur], cur);
            comp.set(arr[child], child);
            cur = child;
        }

        while (cur > 0) {
            int par = (cur - 1) / 2;
            if (comp(arr[cur], arr[par]))
                break;
            zwap(arr[cur], arr[par]);
            comp.set(arr[cur], cur);
            comp.set(arr[par], par);
            cur = par;
        }
    }
};

Que<maxcomp> maxque;
Que<mincomp> minque;

/*
[제약사항]
1. 각 테스트 케이스 시작 시 init() 함수가 한 번 호출된다.
2. 로봇의 총 대수 N은 10 이상 50,000 이하의 정수이다.
3. 시각 cTime은 1 이상 1,000,000,000 이하의 정수이다.
4. 각 테스트 케이스에서 init()을 제외한 함수가 호출될 때마다 cTime은 증가하는 값으로 주어진다.
5. 각 테스트 케이스에서 callJob() 함수를 통해 투입되는 로봇 대수의 총합은 200,000 이하이다.
6. 각 테스트 케이스에서 init() 을 제외한 함수의 호출 횟수의 총합은 50,000 이하이다.
*/

/*
테스트 케이스에 대한 초기화하는 함수. 각 테스트 케이스의 처음에 1회 호출된다.

N은 로봇의 개수이다. 각 로봇은 1부터 N까지 서로 다른 고유 번호가 부여되어 있다.

현재 시각은 0이다.
초기에 모든 로봇은 센터에 있고 지능지수는 0이다. 고장 난 로봇은 없다.

Parameters
N : 로봇의 대수 (10 ≤ N ≤ 50,000)
*/
void init(int N) {
    for (int i = 1; i <= N; ++i) { // 로봇 초기화
        robot[i].rID = i;
        robot[i].IQ = 0;
        robot[i].wID = 0;
        robot[i].begin = 0;
        robot[i].broken = false;
    }

    maxque.init(N, robot);
    minque.init(N, robot);

    mm = 0;
}

/*
현재 시각이 cTime이다. ID가 wID인 작업에 mNum대의 로봇을 투입한다.

해당 작업에 투입된 로봇들의 고유 번호를 모두 합한 값을 반환한다.

mOpt = 0인 경우, 높은 지능 우선 방식으로 로봇을 투입한다.
mOpt = 1인 경우, 낮은 지능 우선 방식으로 로봇을 투입한다.

각 투입 방식의 자세한 설명은 본문 내용을 참조하라.

고장 나거나 작업 중인 로봇은 해당 작업에 투입되지 않는다.

작업에 투입 가능한 로봇의 수보다 더 많이 투입을 요청하는 경우는 발생하지 않음을 보장한다.

각 테스트 케이스에서 wID는 해당 함수가 처음 호출할 때 1이고 호출될 때마다 1씩 증가한다.

Parameters
cTime : 현재 시각 (1 ≤ cTime ≤ 1,000,000,000)
wID : 작업 ID (1 ≤ wID ≤ 50,000)
mNum : 작업에 투입할 로봇의 대수 (1 ≤ mNum ≤ N)
mOpt : 로봇을 투입하는 방식 (mOpt = 0 or 1)

Returns
투입된 로봇들의 고유 번호 총합
*/
int callJob(int cTime, int wID, int mNum, int mOpt) {
    jobs[wID].arr = getRobot(mNum);
    jobs[wID].n = mNum;

    int ret = 0;
    if (mOpt == 0) { // 가장 똑똑한 robot
        int cnt = 0;
        while (cnt < mNum) {
            Robot* p = maxque.pop();

            p->wID = wID; // 어떤 작업에 할당
            p->begin = cTime; // 언제 일 시작
            jobs[wID].arr[cnt++] = p; // wID 작업에 p 가 속해있다

            // min_heap에서도 제거해줘야함
            minque.remove(p->minidx);
            ret += p->rID;
        }
    }
    else { // 가장 멍정한 robot
        int cnt = 0;
        while (cnt < mNum) {
            Robot* p = minque.pop();

            p->wID = wID;
            p->begin = cTime;
            jobs[wID].arr[cnt++] = p;

            maxque.remove(p->maxidx);
            ret += p->rID;
        }
    }

    return ret;
}

/*
현재 시각이 cTime이다. ID가 wID인 작업에 투입된 로봇들이 센터로 복귀하고 트레이닝을 바로 시작한다.

callJob 함수로 호출된 적이 있는 wID 값만 입력으로 들어오는 것을 보장한다.
같은 wID 값으로 두 번 이상 들어오는 경우도 없다.

투입된 로봇들이 모두 고장 나 복귀하는 로봇이 없는 경우도 있다.

Parameters
cTime : 현재 시각 (1 ≤ cTime ≤ 1,000,000,000)
wID : 작업 ID (1 ≤ wID ≤ 50,000)
*/
void returnJob(int cTime, int wID) {
    int n = jobs[wID].n;
    for (int i = 0; i < n; ++i) {
        Robot* p = jobs[wID].arr[i]; // 로봇을 꺼내서
        if (p->broken || p->wID != wID) // 고장이 난 적이 있으면 수리가 끝나고 돌아갈 수 있다
            continue;

        p->IQ -= cTime - p->begin; // 지금 시간과 일을 시작한 시간만큼의 차이를 빼줘야함
        p->wID = 0;

        // max, min heap에 돌려줌
        maxque.push(p);
        minque.push(p);
    }
}

/*
현재 시각이 cTime이다. 작업 중이고 고유 번호가 rID인 로봇이 고장 난다.

해당 로봇은 즉시 센터로 복귀한다. 해당 로봇은 수리가 되기 전까지 작업에 투입할 수 없다.

해당 로봇이 이미 고장 난 로봇이거나 센터에서 트레이닝 중인 경우 이 함수가 호출되면 무시된다.

Parameters
cTime : 현재 시각 (1 ≤ cTime ≤ 1,000,000,000)
rID : 로봇 번호 (1 ≤ rID ≤ N)
*/
void broken(int cTime, int rID) { // rID 로봇이 cTime에 고장이났다.
    if (robot[rID].wID != 0) {
        robot[rID].wID = 0;
        robot[rID].broken = true;
    }
}

/*
현재 시각이 cTime이다. 번호가 rID인 로봇의 수리가 완료된다.

해당 로봇은 다시 작업에 투입될 수 있다.

수리가 완료된 로봇은 지능지수가 0이 되고 트레이닝을 시작한다.

해당 로봇이 고장 난 로봇이 아닌 경우 이 함수가 호출되면 무시된다.

Parameters
cTime : 현재 시각 (1 ≤ cTime ≤ 1,000,000,000)
rID : 로봇 번호 (1 ≤ rID ≤ N)
*/
void repair(int cTime, int rID) {
    if (robot[rID].broken) { // 고장이 나있었다면
        robot[rID].IQ = -cTime; // IQ가 0으로 초기화됨을 나타냄
        robot[rID].broken = false;

        // 센터로 다시 돌려보냄
        maxque.push(&robot[rID]);
        minque.push(&robot[rID]);
    }
}

/*
현재 시각이 cTime이다. 고유 번호가 rID인 로봇의 상태를 확인한다.

로봇의 상태에 따라 다음 중 한가지 값을 반환한다.
1) 만약 로봇이 고장 난 상태이면 0을 반환한다.
2) 만약 로봇이 작업에 투입되어 있으면, (투입된 작업의 ID) * (-1)을 반환한다.
3) 그 외의 경우는 로봇의 지능지수를 반환한다.

Parameters
cTime : 현재 시각 (1 ≤ cTime ≤ 1,000,000,000)
rID : 로봇의 고유 번호 (1 ≤ rID ≤ N)

Returns
로봇의 상태를 나타내는 값
*/
int check(int cTime, int rID) { // cTime에 rID가 뭐하고 있음?
    int ret;
    if (robot[rID].broken) // 고장이 났는지
        ret = 0;
    else if (robot[rID].wID != 0) // 일을 하는지
        ret = -robot[rID].wID;
    else // 일을 안하고 있을 때, 현재 지능
        ret = cTime + robot[rID].IQ;

    return ret;
}

//////////////////////////////////////////////////////////////////////////////////

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CALL_JOB	(100)
#define RETURN_JOB	(200)
#define BROKEN		(300)
#define REPAIR		(400)
#define CHECK		(500)

extern void init(int N);
extern int callJob(int cTime, int wID, int mNum, int mOpt);
extern void returnJob(int cTime, int wID);
extern void broken(int cTime, int rID);
extern void repair(int cTime, int rID);
extern int check(int cTime, int rID);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static int N, Q, cmd;

static int run(int score)
{
    int wIDCnt = 1;
    int cTime, mNum, rID, wID, mOpt;
    int res, ans;

    scanf("%d", &N);
    init(N);

    scanf("%d", &Q);

    while (Q--)
    {
        scanf("%d", &cmd);

        switch (cmd)
        {
            case CALL_JOB:
                scanf("%d %d %d", &cTime, &mNum, &mOpt);
                res = callJob(cTime, wIDCnt, mNum, mOpt);
                scanf("%d", &ans);
                if (ans != res)
                    score = 0;
                wIDCnt++;
                break;
            case RETURN_JOB:
                scanf("%d %d", &cTime, &wID);
                returnJob(cTime, wID);
                break;
            case BROKEN:
                scanf("%d %d", &cTime, &rID);
                broken(cTime, rID);
                break;
            case REPAIR:
                scanf("%d %d", &cTime, &rID);
                repair(cTime, rID);
                break;
            case CHECK:
                scanf("%d %d", &cTime, &rID);
                res = check(cTime, rID);
                scanf("%d", &ans);
                if (ans != res)
                    score = 0;
                break;
            default:
                score = 0;
                break;
        }
    }

    return score;
}

int main()
{
    setbuf(stdout, NULL);
    freopen("sample_input_ai_robot.txt", "r", stdin);

    int T, score;

    scanf("%d %d", &T, &score);

    for (int tc = 1; tc <= T; tc++)
        printf("#%d %d\n", tc, run(score));

    return 0;
}