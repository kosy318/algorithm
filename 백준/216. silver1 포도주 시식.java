import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int N = Integer.parseInt(br.readLine());

        int[] amount = new int[10001];
        for (int i = 1; i <= N; i++) {
            amount[i] = Integer.parseInt(br.readLine());
        }

        // dp[i][0]: i번째 포도주 안마심            = max(dp[i-1][0], dp[i-1][1], dp[i-1][2])
        // dp[i][1]: i번째 포도주 1잔 마심          = dp[i-1][0] + amount[i]
        // dp[i][2]: i번째까지 포도주 연속 2잔 마심   = dp[i-1][1] + amount[i]
        int[][] dp = new int[10001][3];
        for(int i=1; i<=N; i++){
            dp[i][0] = Math.max(Math.max(dp[i-1][0], dp[i-1][1]), dp[i-1][2]);
            dp[i][1] = dp[i-1][0] + amount[i];
            if(dp[i-1][1] != 0) dp[i][2] = dp[i-1][1] + amount[i];
        }

        // 답 max(dp[N][0], dp[N][1], dp[N][2])
        System.out.println(Math.max(Math.max(dp[N][0], dp[N][1]), dp[N][2]));
    }
}
