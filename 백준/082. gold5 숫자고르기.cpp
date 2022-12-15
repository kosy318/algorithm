#include <iostream>
#include <vector>

using namespace std;

int N, cnt = 0;
vector<int> list;
vector<bool> answer;

bool dfs(int start, int next, int depth) {
	// 무한 루프에 빠질 수 있으므로 depth로 가지치기를 해준다.
	if (depth > N - cnt) return false;
	// start에서 시작해서 결국 start로 돌아와야 답이다.
	if (next == start) {
		answer[start] = true;
		cnt += 1;
		return true;
	}

	// 이미 포함된 것은 다른 집합이라는 의미이므로 사용하지 않는다.
	if (!answer[next]) {
		if (dfs(start, list[next], depth+1)) { // start에서 start로 도달했다면 true이다.
			answer[next] = true; // 거쳐가던 모든 노드들을 answer에 포함한다.
			cnt += 1;
			return true; // 전 노드도 포함하기 위해 true를 리턴한다.
		}
	}

	return false;
}

int main() {
	cin >> N;
	list = vector<int>(N + 1);
	answer = vector<bool>(N + 1);

	for (int i = 1; i <= N; i++) {
		cin >> list[i];
	}

	// i번째에서 시작해서 list[i] -> list[list[i]] 를 거쳐 i로 돌아오면 이 집합은 일치하게 된다.
	// 이러한 집합들의 합이 답이다.
	for (int i = 1; i <= N; i++) {
		if (answer[i]) continue;
		dfs(i, list[i], 0);
	}

	cout << cnt << "\n";
	for (int i = 1; i <= N; i++) {
		if(answer[i]) cout << i << "\n";
	}
}