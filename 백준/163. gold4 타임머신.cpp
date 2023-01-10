#include <iostream>
#include <climits>
#include <map>
#include <vector>

using namespace std;

vector<pair<int, int>> cities[501]; // cities[i] : i��° ���ÿ� ����� �ٸ� ���ÿ� �Ÿ�

long long* calc(int N) {
	long long* dist = new long long[N + 1];

	// ��� ��� ����
	dist[1] = 0;

	// �ִ� �Ÿ� ���̺� �ʱ�ȭ
	for (int i = 2; i <= N; i++)
		dist[i] = INT_MAX;

	// ��ü v - 1���� ����(round)�� �ݺ�
	for (int i = 1; i <= N; i++) {
		// j��° city�� �ش��ϴ�
		for (int j = 1; j <= N; j++) {
			// ��� ���� E���� �ϳ��� Ȯ��
			for (auto next : cities[j]) {
				// �� ������ ���� �ٸ� ���� ���� ����� ���(dist[i] + next.second)
				if (dist[j] != INT_MAX && dist[next.first] > dist[j] + next.second) {
					// ����� �� ���� ������ ����� ������ �ִ� �Ÿ� ���̺� ����
					dist[next.first] = dist[j] + next.second;

					// ������ ���� ������ �ǵ��� �� �ִٸ� ù° �ٿ� -1�� ���
					// �� ����Ŭ�� ����� �ȵ�
					// N-1���� ���� N��°���� ���� ���ŵǸ� ���� ����Ŭ
					if (i == N) return NULL;
				}
			}
		}
	}

	return dist;
}

int main() {
	int N; // N���� ����
	int M; // M���� ����
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int A, B, C; // A: ���۵���, B: ��������, C: ������ Ÿ�� �̵��ϴ� �� �ɸ��� �ð�
		cin >> A >> B >> C;

		cities[A].push_back({ B, C });
	}

	/// TODO:: 1�� ���ÿ��� ����ؼ� ������ ���÷� ���� ���� ���� �ð��� ���ϴ� ���α׷�
	long long* dist = calc(N);

	if (dist == NULL)
		cout << "-1";
	else
		for (int i = 2; i <= N; i++)
			cout << ((dist[i] != INT_MAX) ? dist[i] : -1) << "\n";
}