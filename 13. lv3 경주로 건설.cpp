// https://jolly-note.tistory.com/38

#include <string>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Node{
    int x, y;
    int cost;
    int dir;

    Node(int x=0, int y=0, int cost=0, int dir=4) : x{x}, y{y}, cost{cost}, dir{dir}{}
};

int solution(vector<vector<int>> board) {
    vector<int> x_dir = {-1, 1, 0, 0};
    vector<int> y_dir = {0, 0, -1, 1};
    vector<vector<int>> possible_dir = {{0, 2, 3}, {1, 2, 3}, {0, 1, 2}, {0, 1, 3}, {1, 3}};
    int N = board.size();
    vector<vector<vector<int>>> dp(N, vector<vector<int>>(N, vector<int>(4, 0)));

    queue<Node*> que;
    que.push(new Node());
    while(!que.empty()){
        Node* bf = que.front();
        que.pop();

        for(int dir : possible_dir[bf->dir]){
            Node* cur = new Node(bf->x + x_dir[dir], bf->y + y_dir[dir], bf->cost, dir);
            if(cur->x >= 0 && cur->x < N && cur->y >= 0 && cur->y < N
              && board[cur->x][cur->y] == 0){
                cur->cost += (dir == bf->dir || bf->cost == 0)? 100 : 600;

                if(dp[cur->x][cur->y][dir] == 0 || cur->cost < dp[cur->x][cur->y][dir])
                    dp[cur->x][cur->y][dir] = cur->cost;
                else continue;

                if(cur->x == N-1 && cur->y == N-1) continue;
                else que.push(cur);
            }
        }
    }
    int answer = INT_MAX;
    for(auto ele : dp[N-1][N-1])
        if(answer > ele && ele != 0) answer = ele;
    return answer;
}
