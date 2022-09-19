#include <iostream>
#include <vector>

using namespace std;

int N, cnt = 0;
vector<int> list;
vector<bool> answer;

bool dfs(int start, int next, int depth) {
	// ���� ������ ���� �� �����Ƿ� depth�� ����ġ�⸦ ���ش�.
	if (depth > N - cnt) return false;
	// start���� �����ؼ� �ᱹ start�� ���ƿ;� ���̴�.
	if (next == start) {
		answer[start] = true;
		cnt += 1;
		return true;
	}

	// �̹� ���Ե� ���� �ٸ� �����̶�� �ǹ��̹Ƿ� ������� �ʴ´�.
	if (!answer[next]) {
		if (dfs(start, list[next], depth+1)) { // start���� start�� �����ߴٸ� true�̴�.
			answer[next] = true; // ���İ��� ��� ������ answer�� �����Ѵ�.
			cnt += 1;
			return true; // �� ��嵵 �����ϱ� ���� true�� �����Ѵ�.
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

	// i��°���� �����ؼ� list[i] -> list[list[i]] �� ���� i�� ���ƿ��� �� ������ ��ġ�ϰ� �ȴ�.
	// �̷��� ���յ��� ���� ���̴�.
	for (int i = 1; i <= N; i++) {
		if (answer[i]) continue;
		dfs(i, list[i], 0);
	}

	cout << cnt << "\n";
	for (int i = 1; i <= N; i++) {
		if(answer[i]) cout << i << "\n";
	}
}