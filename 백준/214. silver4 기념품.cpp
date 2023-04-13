#include <iostream>
#include <list>
#include <cmath>

using namespace std;

struct Node{
    Node* next;
    Node* prev;
    int num;

    Node(int num, Node* next = nullptr, Node* prev = nullptr):
    num(num), next(next), prev(prev){}

    Node* erase(){
        this->prev->next = this->next;
        this->next->prev = this->prev;

        return this->next;
    }
};

void print(Node* head){
    // cout << head->num << " ";
    Node* cur = head->next;
    while(cur != head){
        // cout << cur->num << " ";
        cur = cur->next;
    }
    // cout << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N; // 사람 인원 수
    cin >> N;

    Node* head = new Node(1);
    Node* cur = head;
    for(int i=2; i<=N; i++){
        cur->next = new Node(i);
        cur->next->prev = cur;
        cur = cur->next;
    }
    head->prev = cur;
    cur->next = head;
    cur = head;

    print(head);
//    print_reverse(cur);

    int turn = 1;
    int size = N;
    while(size > 1){
        int move = (int)((long long)(pow(turn, 3) - 1) % size);

        while(move--){
            cur = cur->next;
        }

        // cout << "erase : " << cur->num << endl;
        cur = cur->erase();

        turn += 1;
        size -= 1;
    }

     cout << cur->num;
}