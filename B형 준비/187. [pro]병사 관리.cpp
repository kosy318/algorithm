// author: 류호석(rhs0266)

/*
1. 각 테스트 케이스 시작 시 init() 함수가 호출된다.
2. 각 테스트 케이스에서 hire() 함수의 호출 횟수는 100,000 이하이다.
3. 각 테스트 케이스에서 fire() 함수의 호출 횟수는 100,000 이하이다.
4. 각 테스트 케이스에서 updateSoldier() 함수의 호출 횟수는 100,000 이하이다.
5. 각 테스트 케이스에서 updateTeam() 함수의 호출 횟수는 100,000 이하이다.
6. 각 테스트 케이스에서 bestSoldier() 함수의 호출 횟수는 100 이하이다.
 */

/*
Linked List를 사용한 이유
hire, fire, updateSoldier, updateTeam 함수의 호출 횟수는 100,000 이하이다.
bestSoldier 함수의 호출 횟수는 100 이하이다.

bestSoldier 함수의 속도는 생각하지 않아도 된다. -> 최대값 찾기

update Team -> 배열 통째로 옮기기, 배열 합치기
hire -> 원소 삽입
fire -> 원소 삭제(무효화)
update soldier -> 특정 ID은 soldier의 점수를 업데이트

최대값 찾기는 느려도됨. 나머지는 빨라야함. -> linked list 사용
*/

struct Node {
    int id;
    int v; // version: 굳이 병사를 찾아가서 업데이트 하는 것이 아니라 버전을 더 높게 해서 다시 삽입한다. 다음에 높은 버전의 같은 아이디가 있으면 갱신해주면 된다.
    Node* nxt;

    Node() {}
    Node(int id, int v) :id(id), v(v), nxt(nullptr) {}
    Node(int id, int v, Node* nxt) : id(id), v(v), nxt(nxt) {}
}node[500055];

int cnt; // 현재까지의 노드의 개수
int version[100055]; // 각 사람마다 최신 버전이 몇인지 기억; version[i] := ID가 i인 사람의 최신 버전
int num[100055]; // num[i] := ID가 i인 사람의 team 번호

Node* getNewNode(int id, Node* nxt = nullptr) {
    Node* ret = &node[cnt++];
    ret->id = id;
    ret->nxt = nxt;
    ret->v = ++version[id]; // 기존 버전보다 1 증가한 버전으로 삽입
    return ret;
}

struct Team {
    Node* head[6]; // head[i] := i점의 head
    Node* tail[6]; // tail[i] := i점의 tail
}t[6]; // 1점을 위한 linked list, 2점을 위한 linked list ...

//각 테스트 케이스의 처음에 호출된다.
//테스트 케이스의 시작 시 고용된 병사는 없다.
void init() {
    cnt = 0;
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            t[i].tail[j] = t[i].head[j] = getNewNode(0); // 모든 head와 tail을 초기화
        }
    }

    for (int i = 0; i <= 100000; i++) { // 모든 사람들에 대해서 최신버전과, 팀 번호도 초기화
        version[i] = 0;
        num[i] = 0;
    }
}

/*
고유번호가 mID, 소속팀이 mTeam, 평판 점수가 mScore인 병사를 고용한다.
한 테스트 케이스 내에서 동일한 mID를 가진 병사가 여러 번 고용되는 경우는 없음이 보장된다.

Parameters
mID : 고유번호 (1 ≤ mID ≤ 100,000)
mTeam : 소속팀 (1 ≤ mTeam ≤ 5)
mScore : 평판 점수 (1 ≤ mScore ≤ 5)
 */
// O(1)
void hire(int mID, int mTeam, int mScore) {
    Node* newNode = getNewNode(mID); // 새로운 정점을 만듦

    // mTeam메 맞는 팀으로 가서 mScore에 맞는리스트에 추가
    t[mTeam].tail[mScore]->nxt = newNode;
    t[mTeam].tail[mScore] = newNode;
    num[mID] = mTeam;
}

/*
고유번호가 mID인 병사를 해고한다.
fire() 함수 호출 시, 고유번호가 mID인 병사가 고용되어 있음이 보장된다.

Parameters
mID : 고유번호 (1 ≤ mID ≤ 100,000)
 */
// O(1)
void fire(int mID) {
    version[mID] = -1; // 삭제하지 않고, 최신버전을 -1로 처리
}

/*
고유번호가 mID인 병사의 평판 점수를 mScore로 변경한다.
고유번호가 mID인 병사가 고용되어 있음이 보장된다.

Parameters
mID : 고유번호 (1 ≤ mID ≤ 100,000)
mScore : 평판 점수 (1 ≤ mScore ≤ 5)
*/
// O(1)
void updateSoldier(int mID, int mScore) {
    hire(mID, num[mID], mScore); // 업데이트하지 않고, 새로운 버전으로 추가
}

/*
소속팀이 mTeam인 병사들의 평판 점수를 모두 변경한다.
소속팀이 mTeam인 병사가 한 명 이상 고용되어 있음이 보장된다.

updateTeam() 함수에서의 평판 점수 변경은 아래의 규칙에 따른다.
‘변경 전 평판 점수 + mChangeScore’가 5보다 클 경우, 평판 점수를 5로 변경한다.
‘변경 전 평판 점수 + mChangeScore’가 1보다 작을 경우, 평판 점수를 1로 변경한다.
그 외의 경우, 평판 점수를 ‘변경 전 평판 점수 + mChangeScore’로 변경한다.

Parameters
mTeam : 소속팀 (1 ≤ mTeam ≤ 5)
mChangeScore : 평판 점수의 변화량 (-4 ≤ mChangeScore ≤ 4)
*/
// O(1)
void updateTeam(int mTeam, int mChangeScore) {
    if (mChangeScore < 0) {// 음수만큼 변경한다면
        for (int j = 1; j <= 5; j++) { // j점인 사람들이 k점으로 바뀌게됨
            int k = j + mChangeScore;
            if (k < 1) k = 1;
            if (k > 5) k = 5;
            // j -> k
            if (j == k) continue;

            if (t[mTeam].head[j]->nxt == nullptr) continue;
            // j점의 리스트를 k점의 리스트에 붙이면 됨
            t[mTeam].tail[k]->nxt = t[mTeam].head[j]->nxt;
            t[mTeam].tail[k] = t[mTeam].tail[j];
            t[mTeam].head[j]->nxt = nullptr;
            t[mTeam].tail[j] = t[mTeam].head[j];
        }
    }
    if (mChangeScore > 0) {
        for (int j = 5; j >= 1; j--) {
            int k = j + mChangeScore;
            if (k < 1) k = 1;
            if (k > 5) k = 5;
            // j -> k
            if (j == k) continue;

            if (t[mTeam].head[j]->nxt == nullptr) continue;
            t[mTeam].tail[k]->nxt = t[mTeam].head[j]->nxt;
            t[mTeam].tail[k] = t[mTeam].tail[j];
            t[mTeam].head[j]->nxt = nullptr;
            t[mTeam].tail[j] = t[mTeam].head[j];
        }
    }
}

/*
소속팀이 mTeam인 병사들 중 평판 점수가 가장 높은 병사의 고유번호를 반환한다.
평판 점수가 가장 높은 병사가 여러 명일 경우, 고유번호가 가장 큰 병사의 고유번호를 반환한다.
소속팀이 mTeam인 병사가 한 명 이상 고용되어 있음이 보장된다.

Parameters
mTeam : 소속팀 (1 ≤ mTeam ≤ 5)

Returns
평판 점수가 가장 높은 병사의 고유번호
*/
// O(N)
int bestSoldier(int mTeam) {
    for (int j = 5; j >= 1; j--) { // 5점부터 시작해서 차례대로 순회
        Node* node = t[mTeam].head[j]->nxt;
        if (node == nullptr) continue;

        int ans = 0;
        while (node) {
            if (node->v == version[node->id]) { // 이 node의 version이 최신 버전과 같아야함
                ans = ans < node->id ? node->id : ans;
            }
            node = node->nxt;
        }
        if (ans != 0) return ans; // ans에 값이 들어갔다면 돌려줌
    }
    return 0;
}