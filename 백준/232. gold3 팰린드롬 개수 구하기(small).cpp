#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string str;
    cin >> str;
    int N = str.length();

    int dp[N][N]; // dp[i][j] := i~j ���� string�� palindrome�� �Ǵ� �κ� ������ ����

    for (int i = 0; i < N; i++) { // �� ���ڶ� �� ������ ��� �ʱ�ȭ
        memset(dp[i], 0, N);

        dp[i][i] = 1; // ���� 1�� ���ڿ��� 1��
        if(i != N - 1){
            if(str[i] == str[i + 1]) {
                dp[i][i + 1] = 3; // aa�� ��� a, a, aa 3������ ����
            }
            else{
                dp[i][i + 1] = 2; // ab�� ��� a, b 2������ ����
            }
        }
    }

    for (int len = 2; len < N; len++) {
        for (int start = 0; start + len < N; start++) {
            if(str[start] == str[start + len]) {
                // �� ���� ���� ���, �� ���� ���� ��쿡 ������ �߰��� ���� �������� �߰��� ��쿡�� palindrome�� �Ǵ� �κ� ������ ���� ���Ѵ�
                // �� ��, �� ���� �߰����� �ʴ� ����� palindrome �κ� ������ 2�� �������µ�,
                // �� �� �ѹ��� �� ���� �߰��� ���� ġ�� ������ ���� ������ ���� ������ �ʴ´�.
                // 1�� �����ִ� ������ �� �� ���ڸ� �������� �װ͵� palindrome�� �Ǵµ� �װ��� �߰��� �� ���̴�.
                dp[start][start + len] = dp[start][start + len - 1] + dp[start + 1][start + len] + 1;
            }
            else {
                // ����� �������� �� ���� ���� �ʱ� ������ �� �� ������ �κ� ������ ���� �� �ϳ��� ������Ѵ�.
                dp[start][start+ len] = dp[start][start + len - 1] + dp[start + 1][start + len] - dp[start + 1][start + len - 1];
            }
        }
    }

    cout << dp[0][N - 1];
}