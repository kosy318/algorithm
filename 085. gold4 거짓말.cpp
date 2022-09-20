#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

int N, P, M, answer;

void know_truth(vector<bool>& knows, vector<set<int>>& parties) {
	vector<bool> visited(N+1);
	vector<bool> truth_party(P);
	queue<int> que;
	for (int i = 1; i <= N; i++) {
		if (knows[i]) {
			que.push(i);
			visited[i] = true;
		}
	}

	while (!que.empty()) {
		int num = que.front();
		que.pop();

		for (int i = 0; i < P; i++) {
			if (!truth_party[i] && parties[i].find(num) != parties[i].end()) {
				truth_party[i] = true;
				answer -= 1;
				
				for (int p : parties[i]) {
					if (visited[p]) continue;
					que.push(p);
					visited[p] = true;
				}
			}
		}
	}
}

int main() {
	cin >> N >> P >> M;
	answer = P;
	
	vector<set<int>> parties(P);
	vector<bool> knows(N+1);

	for (int i = 0; i < M; i++) {
		int temp;
		cin >> temp;
		knows[temp] = true;
	}

	if (knows.size() == 0) { // 아는 사람이 한명도 없으면 모든 파티에서 거짓말 가능
		cout << answer;
		return 0;
	}

	for (int i = 0; i < P; i++) {
		int cnt;
		cin >> cnt;
		for (int j = 0; j < cnt; j++) {
			int temp;
			cin >> temp;
			parties[i].insert(temp);
		}
	}

	// 아는 사람이 속한 파티에서는 거짓말 못함
	// 아는 사람이 속한 파티의 사람들은 진실을 알게됨 -> 재귀
	know_truth(knows, parties);

	cout << answer << endl;
}