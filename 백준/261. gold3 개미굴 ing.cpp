#include <iostream>
#include <string>
#include <set>

using namespace std;

struct Node{
    string name;
    set<Node> child;

    Node() = default;
    Node(string &name) : name(name) {}

    bool operator < (const Node& n1) const {
        return name < n1.name;
    }

    bool operator==(const Node &rhs) const {
        return name == rhs.name;
    }

    bool operator!=(const Node &rhs) const {
        return !(rhs == *this);
    }
} head;

void print_tree(const Node& node = head, int depth = 0) {
    for(const Node& child: node.child){
        for(int i=0; i<depth; i++) cout << "--";
        cout << child.name << "\n";

        print_tree(child);
    }
}

int N;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 0; i < N; i++) {
        int M;
        cin >> M;

        Node cur = head;
        for (int j = 0; j < M; j++) {
            string name;
            cin >> name;

            if(cur.child.find(Node(name)) == cur.child.end()){
                cout << name << " inserted\n";
                cur.child.insert(Node(name));
            }
            cur = *cur.child.find(Node(name));
        }
    }

    cout << head.child.size() << endl;
    print_tree();
}
