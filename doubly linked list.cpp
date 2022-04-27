// doubly linked list
// https://jolly-note.tistory.com/32?category=993245
#include <bits/stdc++.h>

using namespace std;

struct Node{
    Node(int data=0, Node* prev=NULL, Node* next=NULL) :
        data{data}, prev{prev}, next{next}{}

    int data;
    Node* prev;
    Node* next;
};


void print_linked_list(Node* linked_list){
    while(linked_list != NULL){
        cout<<linked_list->data;
        if(linked_list->next !=NULL) cout<<"-";
        linked_list = linked_list->next;
    }
    cout<<endl;
}

int main() {
    Node* linked_list = new Node();
    Node* start_list = linked_list;
    srand(time(NULL));

    for(int i=0; i<10; i++){
        int x = rand()%100;
        cout<<x<<" ";
        linked_list->next = new Node(x, linked_list);
        linked_list = linked_list->next;
    }
    cout<<endl;

    print_linked_list(start_list);

    return 0;
}
