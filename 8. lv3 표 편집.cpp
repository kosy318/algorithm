// https://jolly-note.tistory.com/31?category=1025701

#include <vector>
#include <stack>
#include <string>

using namespace std;

struct Node {
    Node(int data=0, Node* prev=NULL, Node* next=NULL) :
        data{data}, prev{prev}, next{next}{}

    int data;
    Node* prev;
    Node* next;
};

string solution(int n, int k, vector<string> cmd) {
    Node* table = new Node();
    // 0번째 node가 지워졌을 경우, 문제가 발생하므로 주의!!
    Node* start_table = table;
    Node* cur = table;

    for(int i=1; i<n; i++){
        table->next = new Node(i, table, NULL);
        table = table->next;
    }

    for(int i=0; i<k; i++)
        cur = cur->next;

    stack<Node*> deleted;
    for(string c: cmd){
        switch(c[0]){
            case 'U':
                for(int i=0; i<stoi(c.substr(2)); i++)
                    cur = cur->prev;
                break;
            case 'D':
                for(int i=0; i<stoi(c.substr(2)); i++)
                    cur = cur->next;
                break;
            case 'C':
                deleted.push(cur);
                if(cur->prev != NULL) (cur->prev)->next = cur->next;
                else start_table = start_table->next;
                if(cur->next != NULL) {
                    (cur->next)->prev = cur->prev;
                    cur = cur->next;
                } else cur = cur->prev;
                break;
            case 'Z':
                if(deleted.top()->prev != NULL) (deleted.top()->prev)->next = deleted.top();
                else start_table = deleted.top();
                if(deleted.top()->next != NULL) (deleted.top()->next)->prev = deleted.top();
                deleted.pop();
                break;
        }
    }

    string answer(n, 'X');
    while(start_table != NULL){
        answer[start_table->data] = 'O';
        start_table = start_table->next;
    }

    return answer;
}
