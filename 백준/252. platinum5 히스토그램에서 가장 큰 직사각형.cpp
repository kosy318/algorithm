#include <iostream>
#include <vector>

using namespace std;

struct Node{
    int start;
    int end;
    int min_height_idx;

    Node(int start = -1, int end = -1, int min_height_idx = -1)
        : start(start), end(end), min_height_idx(min_height_idx) {}
};

int N; // number of rectangles
vector<long long> heights;
vector<Node> seg_tree;
long long answer;

void make_seg(int cur, int start, int end);
int min_height_idx(int cur);

Node get_range(int cur, int start, int end, int get_s, int get_e);

Node union_node(Node node1, Node node2);

void calculate_area(int start, int end);

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(true) {
        cin >> N;
        if(N == 0) break;

        heights = vector<long long>(N + 1); // 1부터 넣도록 만듦
        seg_tree = vector<Node>(4 * N); // 널널하게 사이즈 잡음
        answer = -1;
        
        for (int i = 1; i <= N; i++) {
            cin >> heights[i];
        }

        make_seg(1, 1, N);

        calculate_area(1, N);

        cout << answer << "\n";
    }
}

void calculate_area(int start, int end) {
//    cout << "cal area " << start << ", " << end << endl;
    if(start == end){
        answer = max(answer, heights[start]);
        return ;
    }

    Node node = get_range(1, 1, N, start, end);
    if(answer < (node.end - node.start + 1)*heights[node.min_height_idx]){
        answer = (node.end - node.start + 1)*heights[node.min_height_idx];
    }

    int mid = node.min_height_idx;
//    cout << "mid " << mid << endl;

    if(mid - 1 > 0 && start <= mid - 1) calculate_area(start, mid - 1);
    if(mid + 1 <= N && mid + 1 <= end) calculate_area(mid + 1, end);
}

// cur : 현재 노드 위치, [start, end] : 현재 보고있는 범위, [get_s, get_e] : 구하고자하는 범위
Node get_range(int cur, int start, int end, int get_s, int get_e) {
    if(get_s > end || get_e < start) return Node();  // 현재 보고있는 범위가 구하고자 하는 범위를 벗어남
    else if(get_s <= start && end <= get_e) return seg_tree[cur]; // 현재 보고있는 범위가 구하고자 하는 범위 내에 있음

    // 현재 보고있는 범위가 구하고자 하는 범위에 걸쳐있음
    // 따라서 쪼개서 접근
    int mid = (start + end) / 2;
    Node left_node = get_range(cur * 2, start, mid, get_s, get_e);
    Node right_node = get_range(cur * 2 + 1, mid + 1, end, get_s, get_e);

    // 범위를 벗어난 리턴 값을 거르고 합쳐서 리턴
    if(left_node.min_height_idx == -1 && right_node.min_height_idx == -1) return Node();
    else if(left_node.min_height_idx == -1 && right_node.min_height_idx != -1) return right_node;
    else if(left_node.min_height_idx != -1 && right_node.min_height_idx == -1) return left_node;
    else{
        return union_node(left_node, right_node);
    }
}

Node union_node(Node node1, Node node2) {
    if(node1.start < node2.start) {
        int min_height_idx;
        if(heights[node1.min_height_idx] <= heights[node2.min_height_idx]){
            min_height_idx = node1.min_height_idx;
        }
        else {
            min_height_idx = node2.min_height_idx;
        }
        return Node(node1.start, node2.end, min_height_idx);
    }
}

void make_seg(int cur, int start, int end) { // cur: 현재 노드, [strat, end]
    if(start == end){ // leaf node
        seg_tree[cur] = Node(start, end, end);
        return;
    }

    int mid = (start + end) / 2;
    // 왼쪽 범위
    make_seg(cur * 2, start, mid);
    // 오른쪽 범위
    make_seg(cur * 2 + 1, mid + 1, end);

    // 현재 노드 값 갱신
    seg_tree[cur] = Node(start, end, min_height_idx(cur));
}

int min_height_idx(int cur) {
    Node left_child = seg_tree[cur * 2];
    Node right_child = seg_tree[cur * 2 + 1];

    if(heights[left_child.min_height_idx] <= heights[right_child.min_height_idx]){
        return left_child.min_height_idx;
    }
    return right_child.min_height_idx;
}
