import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Main {

    static int N;
    // dp[i][j] := i길이를 가진 bitmasking(j)의 숫자를 쓴 경우의 수
    static int[][][] dp;
    static int TARGET = (1 << 10) - 1;

    static int dfs(int length, int visited, int last) {
        if (length == N) {
            if(visited == TARGET){
                return 1;
            }
            return 0;
        }

        if(dp[length][last][visited] != -1) return dp[length][last][visited];

        dp[length][last][visited] = 0;
        if(last - 1 >= 0)
            dp[length][last][visited] = (dp[length][last][visited] + dfs(length + 1, visited | (1 << (last - 1)), last - 1)) % 1000000000;
        if(last + 1 < 10)
            dp[length][last][visited] = (dp[length][last][visited] + dfs(length + 1, visited | (1 << (last + 1)), last + 1)) % 1000000000;

        return dp[length][last][visited];
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        N = Integer.parseInt(br.readLine());
        dp = new int[N + 1][10][1 << 11];

        for (int i = 0; i <= N; i++) {
            for (int j = 0; j < 10; j++) {
                Arrays.fill(dp[i][j], -1);
            }
        }

        int answer = 0;
        for (int i = 1; i < 10; i++) {
            answer = (answer + dfs(1, 1 << i, i)) % 1000000000;
        }

        System.out.println(answer);
    }
}