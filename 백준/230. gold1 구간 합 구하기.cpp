#include <iostream>
#include <vector>

using namespace std;

int N; // ���� ����
int M; // ���� ������ �Ͼ�� Ƚ��
int K; // ������ ���� ���ϴ� Ƚ��
vector<long long> nums; // �Է¹��� ���ڵ�
vector<long long> seg_tree; // segment tree

// root node�� 1�� �����ϴ� ���
void make_seg(int cur, int start, int end){ // cur : ���� ���, [start, end] : ����
    if(start == end) { // leaf node
        seg_tree[cur] = nums[start];
        //cout << cur << "[" << start << ", " << end << "]" << " : " << seg_tree[cur] << endl;
        return;
    }

    int mid = (start + end) / 2;
    // ���� ����
    make_seg(cur*2, start, mid);
    // ������ ����
    make_seg(cur*2 + 1, mid + 1, end);

    // ���� ��� �� ����
    seg_tree[cur] = seg_tree[cur*2] + seg_tree[cur*2 + 1];
    //cout << cur << "[" << start << ", " << end << "]" << " : " << seg_tree[cur] << endl;
}

void update(int cur, int start, int end, int idx, long long diff){ // cur : ���� �����ִ� node, [start, end] : ���� �����ִ� ����, idx : �ٲٷ����ϴ� ����� idx, diff : �ٲ� ���� ����
    // �ٲٷ��� idx�� ���� �����ִ� ���� [start, end] �ܺο� �����ϸ� �� �ʿ� ����
    if(idx < start || idx > end) return;

    //cout << "[" << start << ", " << end << "]" << endl;
    // ���� �����ִ� ������ idx �� ������
    seg_tree[cur] += diff;
    //cout << cur << " : " << seg_tree[cur] << endl;

    if(start != end) { // leaf node�� �ƴ�. �� ��� ���� update �������
        int mid = (start + end) / 2;
        update(cur*2, start, mid, idx, diff);
        update(cur*2 + 1, mid + 1, end, idx, diff);
    }
}

long long get(int cur, int start, int end, int get_s, int get_e) { // cur : ���� ��� ��ġ, [start, end] : ���� �����ִ� ����, [get_s, get_e] : ���ϰ����ϴ� ����
    if(get_s > end || get_e < start) return 0; // ���� �����ִ� ������ ���ϰ��� �ϴ� ������ ���
    else if(get_s <= start && end <= get_e) return seg_tree[cur]; // ���� �����ִ� ������ ���ϰ��� �ϴ� ���� ���� ����

    // ���� �����ִ� ������ ���ϰ��� �ϴ� ������ ��������
    // ���� �ɰ��� ����
    int mid = (start + end) / 2;
    long long left_sum = get(cur*2, start, mid, get_s, get_e);
    long long right_sum = get(cur*2 + 1, mid + 1, end, get_s, get_e);

    // ������ ������� 0�� �������� ���̱� ������ �Ű澲�� ���� ���ؼ� �����ϸ��
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
    // segment tree �ʱ�ȭ
    //cout << "make seg -----------------\n";
    make_seg(1, 1, N);
    //cout << "make end -----------------\n";

    for (int i = 0; i < M + K; i++) {
        int a, b;
        ////////////////// Ʋ�� �κ� : �ٲ�� ���ڰ� �� ���� ������ c�� long long���� �޾ƾ���
        long long c;
        cin >> a >> b >> c;

        switch (a) {
        case 1: // b��° ���� c�� �ٲ�
            //cout << "update seg -----------------\n";
            //cout << "idx : " << b << ", add diff " << c - nums[b] << endl;
            update(1, 1, N, b, c - nums[b]);
            ///////////////////// Ʋ�� �κ� : ���� ���ڸ� �ٲ����� ����...
            nums[b] = c;
            //cout << "update end -----------------\n";
            break;
        case 2: // b��° ������ c��° �������� ��
            cout << get(1, 1, N, b, c) << "\n";
            break;
        default:
            cout << "�߸��� �Է�\n";
            exit(0);
        }
    }
}