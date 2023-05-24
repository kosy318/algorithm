#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    int num[N];

    for(int i=0; i<N; i++){
        cin >> num[i];
    }

    // left_dp[i] := i��° ���ڸ� ������ �������� ������ ���ڵ��� �� �� �ִ�(�������� ���� x)
    // right_dp[i] := i��° ���ڸ� ������ ���������� ������ ���ڵ��� �� �� �ִ�(������ ����x)
    int left_dp[N], right_dp[N];

    // ���� ù��° ���� �ʱ�ȭ
    left_dp[0] = num[0];
    right_dp[N - 1] = num[N - 1];
    int max_value = max(left_dp[0], right_dp[N - 1]);

    // dp �ʱ�ȭ
    // ������ �����ϴ� �Ϳ� ���� ���ڸ� ���� ���� �� ū��, �ƴϸ� �׳� ���� ���� �ϳ��� �� ū�� ���ؼ� �Է�
    for (int i = 1; i < N; i++) {
        left_dp[i] = max(left_dp[i - 1] + num[i], num[i]);
        right_dp[N - 1 - i] = max(right_dp[N - 1 - (i - 1)] + num[N - 1 - i], num[N - 1 - i]);

        // �ϳ��� �������� �ʾ��� �� �ִ� ��
        max_value = max(max_value, max(left_dp[i], right_dp[N - 1 - i]));
    }

    // �ϳ��� �����ϰ� �ִ밪
    // ���ӵ� ���� �� �߰��� �����ϱ� ������ 1���� N-2�� �������ָ� �ȴ�.
    for (int i = 1; i < N - 1; i++) {
        // ������ ���� ���� ������ �������� ���ӵ� ������ �ִ��� +
        // ������ ���� ������ ������ ���������� ���ӵ� ������ �ִ���
        max_value = max(max_value, left_dp[i - 1] + right_dp[i + 1]);
    }

    cout << max_value;
}