#include <iostream>
#include <vector>

using namespace std;

int N; // 숫자 개수
int M; // 수의 변경이 일어나는 횟수
int K; // 구간의 합을 구하는 횟수
vector<long long> nums; // 입력받은 숫자들
vector<long long> seg_tree; // segment tree

// root node가 1로 시작하는 경우
void make_seg(int cur, int start, int end){ // cur : 현재 노드, [start, end] : 범위
    if(start == end) { // leaf node
        seg_tree[cur] = nums[start];
        //cout << cur << "[" << start << ", " << end << "]" << " : " << seg_tree[cur] << endl;
        return;
    }

    int mid = (start + end) / 2;
    // 왼쪽 범위
    make_seg(cur*2, start, mid);
    // 오른쪽 범위
    make_seg(cur*2 + 1, mid + 1, end);

    // 현재 노드 값 저장
    seg_tree[cur] = seg_tree[cur*2] + seg_tree[cur*2 + 1];
    //cout << cur << "[" << start << ", " << end << "]" << " : " << seg_tree[cur] << endl;
}

void update(int cur, int start, int end, int idx, long long diff){ // cur : 현재 보고있는 node, [start, end] : 현재 보고있는 범위, idx : 바꾸려고하는 노드의 idx, diff : 바뀐 값의 차이
    // 바꾸려는 idx가 현재 보고있는 범위 [start, end] 외부에 존재하면 볼 필요 없음
    if(idx < start || idx > end) return;

    //cout << "[" << start << ", " << end << "]" << endl;
    // 현재 보고있는 범위가 idx 를 포함함
    seg_tree[cur] += diff;
    //cout << cur << " : " << seg_tree[cur] << endl;

    if(start != end) { // leaf node가 아님. 더 깊게 들어가서 update 해줘야함
        int mid = (start + end) / 2;
        update(cur*2, start, mid, idx, diff);
        update(cur*2 + 1, mid + 1, end, idx, diff);
    }
}

long long get(int cur, int start, int end, int get_s, int get_e) { // cur : 현재 노드 위치, [start, end] : 현재 보고있는 범위, [get_s, get_e] : 구하고자하는 범위
    if(get_s > end || get_e < start) return 0; // 현재 보고있는 범위가 구하고자 하는 범위를 벗어남
    else if(get_s <= start && end <= get_e) return seg_tree[cur]; // 현재 보고있는 범위가 구하고자 하는 범위 내에 있음

    // 현재 보고있는 범위가 구하고자 하는 범위에 걸쳐있음
    // 따라서 쪼개서 접근
    int mid = (start + end) / 2;
    long long left_sum = get(cur*2, start, mid, get_s, get_e);
    long long right_sum = get(cur*2 + 1, mid + 1, end, get_s, get_e);

    // 범위를 벗어났으면 0을 리턴했을 것이기 때문에 신경쓰지 말고 더해서 리턴하면됨
    return left_sum + right_sum;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> K;
    nums = vector<long long>(N + 1);
    seg_tree = vector<long long>(4 * N);

    for (int i = 1; i <= N; i++) {
        cin >> nums[i];
    }
    // segment tree 초기화
    //cout << "make seg -----------------\n";
    make_seg(1, 1, N);
    //cout << "make end -----------------\n";

    for (int i = 0; i < M + K; i++) {
        int a, b;
        ////////////////// 틀린 부분 : 바뀌는 숫자가 될 수도 있으니 c는 long long으로 받아야함
        long long c;
        cin >> a >> b >> c;

        switch (a) {
        case 1: // b번째 수를 c로 바꿈
            //cout << "update seg -----------------\n";
            //cout << "idx : " << b << ", add diff " << c - nums[b] << endl;
            update(1, 1, N, b, c - nums[b]);
            ///////////////////// 틀린 부분 : 기존 숫자를 바꿔주지 않음...
            nums[b] = c;
            //cout << "update end -----------------\n";
            break;
        case 2: // b번째 수부터 c번째 수까지의 합
            cout << get(1, 1, N, b, c) << "\n";
            break;
        default:
            cout << "잘못된 입력\n";
            exit(0);
        }
    }
}