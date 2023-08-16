#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

struct MinMax {
    int min = INT_MAX, max = INT_MIN;

    MinMax() {}
    MinMax(int num) : min(num), max(num) {}
    MinMax(int min, int max) : min(min), max(max) {}

    string to_string() const {
        return std::to_string(min) + " " + std::to_string(max) + "\n";
    }
};

int N;
vector<int> nums;
vector<MinMax> seg_tree;

MinMax get_min_max(int cur) {
    MinMax left = seg_tree[cur * 2];
    MinMax right = seg_tree[cur * 2 + 1];

    MinMax new_minmax;
    new_minmax.max = max(left.max, right.max);
    new_minmax.min = min(left.min, right.min);

    return new_minmax;
}

void make_seg(int cur, int start, int end) { // cur: 현재 노드, [start, end]
    if (start == end) { // leaf node
        seg_tree[cur] = MinMax(nums[start]);
        return;
    }

    int mid = (start + end) / 2;
    // 왼쪽
    make_seg(cur * 2, start, mid);
    // 오른쪽
    make_seg(cur * 2 + 1, mid + 1, end);

    seg_tree[cur] = get_min_max(cur);
}

MinMax get_range(int cur, int start, int end, int target_s, int target_e) {
    if(target_s > end || target_e < start) return MinMax();
    else if(target_s <= start && end <= target_e) return seg_tree[cur];

    int mid = (start + end) / 2;
    MinMax left = get_range(cur * 2, start, mid, target_s, target_e);
    MinMax right = get_range(cur * 2 + 1, mid + 1, end, target_s, target_e);

    return MinMax(min(left.min, right.min), max(left.max, right.max));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> N >> T;
    nums = vector<int>(N + 1);
    seg_tree = vector<MinMax>(4 * N);

    for (int i = 1; i <= N; i++) {
        cin >> nums[i];
    }

    make_seg(1, 1, N);

    while (T--) {
        int a, b;
        cin >> a >> b;

        // cur : 현재 노드 위치, [start, end] : 현재 보고있는 범위, [get_s, get_e] : 구하고자하는 범위
        cout << get_range(1, 1, N, a, b).to_string();
    }
}