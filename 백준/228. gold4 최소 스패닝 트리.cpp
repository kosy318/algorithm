#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int from, to;
    int cost;

    Edge(int from = 0, int to = 0, int cost = 0) : from(from), to(to), cost(cost) {}

    string toString() {
        return "from = " + to_string(from) + ", to = " + to_string(to) + ", cost = " + to_string(cost);
    }
};

bool comp(Edge e1, Edge e2) {
    return e1.cost < e2.cost;
}

int V, E;
int* parent;
vector<Edge> edges;

void make_set(){
    parent = new int[V + 1];
    edges = vector<Edge>(E);

    for (int i = 1; i <= V; i++) {
        parent[i] = i;
    }
}

int find_set(int node){
    if(parent[node] == node) return node; // parent가 본인이면 리턴
    return parent[node] = find_set(parent[node]); // 아니면 parent의 parent의 찾아서 넣어서 리턴
}

bool union_set(int a, int b){
    int a_root = find_set(a);
    int b_root = find_set(b);

    if(a_root == b_root) return false; // 이미 같은 집합

    parent[b_root] = a_root;
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> V >> E;

    make_set();

    for (int i = 0; i < E; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;
        edges[i] = Edge(from, to, cost);
    }

    sort(edges.begin(), edges.end(), comp);

    // sorting check
//    for (auto e: edges) {
//        cout << e.toString() << endl;
//    }

    int answer = 0;
    int cnt = 0;
    for (auto e: edges) {
        if(union_set(e.from, e.to)){
            answer += e.cost;
            if(++cnt == V-1) break;
        }
    }

    cout << answer;
}