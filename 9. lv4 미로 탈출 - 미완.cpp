// ¹Ì¿Ï

#include <string>
#include <vector>
#include <climits>
#include <queue>
#include <map>

using namespace std;

struct Node{
    int room;
    int cost;
    map<int, map<int, int>> connect;
    Node(int room, int cost, map<int, map<int, int>> connect) :
    room{room}, cost{cost}, connect{connect}{}
};

struct cmp{
    bool operator()(Node* n1, Node* n2){
        if(n1->cost > n2->cost)
            return true;
        return false;
    }
};

int solution(int n, int start, int end, vector<vector<int>> roads, vector<int> traps) {
    vector<bool> trap(n+1, false);
    for(int t: traps) trap[t] = true;

    vector<vector<int>> roads_map(n+1, vector<int>(n+1, 0));
    map<int, map<int, int>> connected;
    int min = INT_MAX;

    for(auto r: roads){
        if(min > r[2]) min = r[2];
        connected[r[0]][r[1]] = -1;
        if(trap[r[0]] || trap[r[1]]) {
            connected[r[1]][r[0]] = 0;
            connected[r[0]][r[1]] = 0;
        }
        if(roads_map[r[0]][r[1]] == 0 || roads_map[r[0]][r[1]] > r[2]){
            roads_map[r[0]][r[1]] = r[2];
        }
    }

    int answer = INT_MAX;

    priority_queue<Node*, vector<Node*>, cmp> que;
    que.push(new Node(start, 0, connected));


    while(!que.empty()){
        Node* now = que.top();
        if(answer <= now->cost + min) break;
        que.pop();
        map<int, map<int, int>> connect(now->connect);

        for(auto c : now->connect[now->room]){
            int from = now->room;
            int to = c.first;
            if(c.second == 1){
                int temp = from;
                from = to;
                to = temp;
            }
            if(roads_map[from][to] != 0 && answer > now->cost + roads_map[from][to]){
                int add = roads_map[from][to];
                if((c.second != 1 && to == end) || (c.second == 1 && from == end)) {
                    answer = now->cost + add;
                    continue;
                }

                if(c.second != 1 && trap[to]){
                    for(auto& r : connect[to]){
                        r.second = 1 - r.second;
                        connect[r.first][to] = 1- connect[r.first][to];
                    }
                }else if(c.second == 1 && trap[from]){
                    for(auto& r : connect[from]){
                        r.second = 1 - r.second;
                        connect[r.first][from] = 1- connect[r.first][from];
                    }
                }

                if(c.second != 1)que.push(new Node(to, now->cost + add, connect));
                else if(c.second == 1) que.push(new Node(from, now->cost + add, connect));

                if((c.second != 1 && trap[to])||(c.second == 1 && trap[from])) connect = now->connect;
            }
        }
    }
    return answer;
}
