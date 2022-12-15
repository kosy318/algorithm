// https://jolly-note.tistory.com/41?category=1025701

#include <string>
#include <vector>
#include <queue>

using namespace std;

bool topology_sort(vector<vector<int>>& di, vector<int>& indegree) {
    queue<int> que;
    que.push(0);

    for (int i = 0; i < di.size(); i++) {
        if (que.empty()) return false; // cycle 발생

        int room = que.front(); que.pop();
        for (auto to : di[room]) {
            if (--indegree[to] == 0) que.push(to);
        }
    }
    return true;
}

bool solution(int n, vector<vector<int>> path, vector<vector<int>> order) {
    vector<vector<int>> undirected(n);
    for (auto p : path) {
        undirected[p[0]].push_back(p[1]);
        undirected[p[1]].push_back(p[0]);
    }

    vector<vector<int>> directed(n);
    vector<int> indegree(n, 0); indegree[0] = 0;
    queue<int> que; que.push(0);
    vector<bool> visit(n, false); visit[0] = true;
    while (!que.empty()) {
        int room = que.front(); que.pop();
        for (auto to : undirected[room]) {
            if (visit[to]) continue;
            que.push(to);
            directed[room].push_back(to);
            visit[to] = true;
            indegree[to]++;
        }
    }

    for (auto o : order) {
        if (o[1] == 0) return false;
        directed[o[0]].push_back(o[1]); // o[0]을 방문한 뒤 o[1]을 감
        indegree[o[1]]++;
    }

    return topology_sort(directed, indegree); // learned
}