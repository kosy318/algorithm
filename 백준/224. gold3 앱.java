import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {

    static int[] memory = new int[101];
    static int[] cost = new int[101];
    // 비용 최대 10000
    static long[][] dp = new long[101][10001]; // dp[i][j] := i번째 app까지 고려했을때, j만큼 비용으로 얻을 수 있는 최대 메모리

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int N = Integer.parseInt(st.nextToken());
        int needs = Integer.parseInt(st.nextToken());

        st = new StringTokenizer(br.readLine());
        for (int i = 1; i <= N; i++) {
            memory[i] = Integer.parseInt(st.nextToken());
        }

        int total = 0;
        st = new StringTokenizer(br.readLine());
        for (int i = 1; i <= N; i++) {
            cost[i] = Integer.parseInt(st.nextToken());
            total += cost[i];
        }

        int answer = Integer.MAX_VALUE;

        for (int i = 1; i <= N; i++) {
            for (int j = 0; j <= total; j++) {
                if(j-cost[i] >= 0) dp[i][j] = Math.max(dp[i - 1][j], dp[i - 1][j - cost[i]] + memory[i]);
                else dp[i][j] = dp[i-1][j];

                if(dp[i][j] >= needs){
                    answer = Math.min(answer, j);
                }
            }
        }

        System.out.println(answer);
    }
}