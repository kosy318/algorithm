/*
 * LCA(Lowest common ancestor)
 */

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct Node{
    vector<int> children;
    int parents = 0;
};

Node* nodes;   // node[i] := i번 정점의 자식 정점들

void traverse(int idx, vector<int>& ancestor){
    int parent = nodes[idx].parents;
    if(parent != 0){ // root node가 아니라면, 부모 노드가 존재한다면
        traverse(parent, ancestor); // 조상을 더 찾으라고 재귀 호출 수행
    }
    ancestor.push_back(idx); // ancestor에 root노드부터 들어가게됨
}

// 한 tree에 대해 한번만 탐색하므로 굳이 크기를 저장해놓을 필요가 없어서 그때그때 계산
int dfs(int idx){ // idx를 root로 갖는 subtree의 크기를 계산하는 함수
    int res = 1;
    for(int child : nodes[idx].children){
        res += dfs(child);
    }
    return res;
}

// O(N)
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for(int t=1; t<=T; t++){
        int ans; // 정답
        int N, M; // 정점과 간선의 개수
        int A, B; // 궁금한 두 정점
        vector<int> ancestorA, ancestorB; // A또는 B의 조상 리스트

        cin >> N >> M >> A >> B;
        nodes = new Node[N+1];

        for(int i=0; i<M; i++){
            int p, c;
            cin >> p >> c;
            nodes[p].children.push_back(c); // 부모쪽에 자식 추가
            nodes[c].parents = p; // 자식에 부모를 알려줌
        }

        // A와 B의 조상 찾기
        traverse(A, ancestorA);
        traverse(B, ancestorB);

        // 차례대로 보면서 처음으로 달라지는 위치 가져옴
        for(int i=0; i<min(ancestorA.size(), ancestorB.size()); i++){
            if(ancestorA[i] != ancestorB[i]) break; // ancestor에 root노드부터 들어가서 차례대로 비교해도 괜찮음
            ans = ancestorA[i];
        }

        cout << "#" << t << " " << ans << " " << dfs(ans) << "\n";
    }
}