#include <iostream>
#include <vector>

using namespace std;

int N;
vector<int> parent;

void init(){
    parent = vector<int>(N + 1);
    for(int i=0; i<=N; i++){
        parent[i] = i;
    }
}

int find_parent(int a){
    if(parent[a] == a) return a;

    return parent[a] = find_parent(parent[a]);
}

bool union_num(int a, int b){
    int a_root = find_parent(a);
    int b_root = find_parent(b);

    if(a_root == b_root) return false; // 이미 같은 집합

    parent[b_root] = a_root;

    return true;
}

bool is_same_set(int a, int b){
    int a_root = find_parent(a);
    int b_root = find_parent(b);

    return a_root == b_root;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int M;
    cin >> N >> M;

    init();

    while (M--) {
        int order, a, b;
        cin >> order >> a >> b;

        switch (order) {
            case 0:
                union_num(a, b);
                break;
            case 1:
                cout << (is_same_set(a, b)? "YES\n":"NO\n");
                break;
            default:
                break;
        }
    }
}