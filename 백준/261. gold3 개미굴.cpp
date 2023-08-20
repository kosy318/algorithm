#include <iostream>
#include <string>
#include <map>

using namespace std;

int N, M;

struct Node{
    map<string, Node> child;

    Node() {}
} head;

void insert_name(Node& node = head, int idx = 0);

void print_tree(const Node& node = head, int depth = 0) {
    for(const auto& child: node.child){
        for(int i=0; i<depth; i++) cout << "--";
        cout << child.first << "\n";

        print_tree(child.second, depth + 1);
    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> M;

        insert_name();
    }

    print_tree();
}

void insert_name(Node& node, int idx) {
    if(idx == M) return;

    string name;
    cin >> name;

    if(node.child.find(name) == node.child.end()) {
        node.child[name] = Node();
    }

    insert_name(node.child[name], idx + 1);
}
