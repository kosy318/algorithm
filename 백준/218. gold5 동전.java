import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine()); // testcase 개수
        for (int t = 1; t <= T; t++) {
            int N = Integer.parseInt(br.readLine()); // N가지 동전

            StringTokenizer st = new StringTokenizer(br.readLine());
            List<Integer> coins = new ArrayList<>();
            int[] dp = new int[10001]; // dp[i] := i원을 만들 수 있는 경우의 수
            for (int i = 0; i < N; i++) {
                coins.add(Integer.parseInt(st.nextToken()));
            }

            int total = Integer.parseInt(br.readLine());
            dp[0] = 1;
            for (int coin : coins) { // coin을 나중에 돌면 뒤죽박죽이 된다 한 종류씩 채워주기!!!
                for (int i = 1; i <= total; i++) {
                    if(i-coin >= 0) dp[i] += dp[i - coin];
                }
            }

            System.out.println(dp[total]);
        }
    }

}