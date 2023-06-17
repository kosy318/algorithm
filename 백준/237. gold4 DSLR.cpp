#include <iostream>
#include <queue>
#include <string>

using namespace std;

int A, B;

struct Order{
    string order;
    int num;

    Order(string order, int num) : order{order}, num{num}{}
};

////////////// 틀린 부분 : visited 체크를 해서 시간을 줄여야했음
void bfs(vector<bool> visited = vector<bool>(10000, false)){
    queue<Order> que;
    que.emplace("", A);
    visited[A] = true;

    while(!que.empty()){
        Order cur = que.front(); que.pop();

        // D : 숫자를 두배
        int D = (cur.num * 2) % 10000;
        if(D == B){ // A와 B가 일치함
            cout << cur.order + "D" << endl;
            return;
        } else if(!visited[D]){ // 일치하지 않고 시도하지 않은 숫자임
            que.emplace(cur.order + "D", D);
            visited[D] = true;
        }

        // S : 숫자 -1, 0일경우 9999
        int S = cur.num - 1;
        if(S == -1) S = 9999;
        if(S == B){ // A와 B가 일치함
            cout << cur.order + "S" << endl;
            return;
        } else if(!visited[S]){ // 일치하지 않고 시도하지 않은 숫자임
            que.emplace(cur.order + "S", S);
            visited[S] = true;
        }

        // L : 숫자를 왼쪽으로 한칸씩 이동(빈자리는 0으로 채움)
        ///// 틀린 부분 : 편하게 하려고 이렇게 했다가 오류남(invalid_argument) cur.num[1] + cur.num[2] + cur.num[3] + cur.num[0];
        int front = stoi(to_string(cur.num / 1000));
        int L = cur.num;
        L = ((L * 10) + front) % 10000;
        if(L == B){ // A와 B가 일치함
            cout << cur.order + "L" << endl;
            return;
        } else if(!visited[L]){ // 일치하지 않고 시도하지 않은 숫자임
            que.emplace(cur.order + "L", L);
            visited[L] = true;
        }

        // R : 숫자를 오른쪽으로 한칸씩 이동(빈자리는 0으로 채움)
        int back = stoi(to_string(cur.num % 10));
        int R = cur.num;
        R = ((R / 10) + back*1000) % 10000;
        if(R == B){ // A와 B가 일치함
            cout << cur.order + "R" << endl;
            return;
        } else if(!visited[R]){ // 일치하지 않고 시도하지 않은 숫자임
            que.emplace(cur.order + "R", R);
            visited[R] = true;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> A >> B;

        ///////////// 틀린 부분 : 쓸데없이 A, B를 string으로 만들어 저장해서 사용함..
        ///////////// 매번 int로 바꾸는 과정과 string으로 바꾸는 과정이 반복되면서 시간초과..

        bfs();
    }
}