#include <iostream>
#include <climits>
#include <map>
#include <vector>

using namespace std;

vector<pair<int, int>> cities[501]; // cities[i] : i번째 도시에 연결된 다른 도시와 거리

long long* calc(int N) {
	long long* dist = new long long[N + 1];

	// 출발 노드 설정
	dist[1] = 0;

	// 최단 거리 테이블 초기화
	for (int i = 2; i <= N; i++)
		dist[i] = INT_MAX;

	// 전체 v - 1번의 라운드(round)를 반복
	for (int i = 1; i <= N; i++) {
		// j번째 city에 해당하는
		for (int j = 1; j <= N; j++) {
			// 모든 간선 E개를 하나씩 확인
			for (auto next : cities[j]) {
				// 각 간선을 거쳐 다른 노드로 가는 비용을 계산(dist[i] + next.second)
				if (dist[j] != INT_MAX && dist[next.first] > dist[j] + next.second) {
					// 비용이 더 적게 나오면 계산한 값으로 최단 거리 테이블 갱신
					dist[next.first] = dist[j] + next.second;

					// 무한히 오래 전으로 되돌릴 수 있다면 첫째 줄에 -1을 출력
					// 즉 싸이클이 생기면 안됨
					// N-1까지 돌고 N번째에서 값이 갱신되면 음수 싸이클
					if (i == N) return NULL;
				}
			}
		}
	}

	return dist;
}

int main() {
	int N; // N개의 도시
	int M; // M개의 버스
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int A, B, C; // A: 시작도시, B: 도착도시, C: 버스를 타고 이동하는 데 걸리는 시간
		cin >> A >> B >> C;

		cities[A].push_back({ B, C });
	}

	/// TODO:: 1번 도시에서 출발해서 나머지 도시로 가는 가장 빠른 시간을 구하는 프로그램
	long long* dist = calc(N);

	if (dist == NULL)
		cout << "-1";
	else
		for (int i = 2; i <= N; i++)
			cout << ((dist[i] != INT_MAX) ? dist[i] : -1) << "\n";
}