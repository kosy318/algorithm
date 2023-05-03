import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
    static int[] knownWeight = new int[31];
    static int N;
    // 주어지는 추의 개수는 30개 최대 500의 무게 -> 전부 한쪽에 올려도 최대 15000
    static boolean[][] dp = new boolean[15001][15001]; // dp[i][j] := i-1번까지 사용해서 j무게를 만들 수 있는지?

    static void setDp(int idx, int weight) {
        if(idx > N) return; // 추의 개수를 넘음
        if(dp[idx][weight]) return; // 이미 만들 수 있음

        dp[idx][weight] = true; // 여기까지 들어왔다는 것은 만들 수 있는 무게라는 의미

        setDp(idx + 1, weight); // idx번째 무게를 추가하지 않음
        setDp(idx + 1, weight + knownWeight[idx]); // idx번째 무게를 추가함
        setDp(idx + 1, Math.abs(weight - knownWeight[idx])); // idx번째 무게를 반대쪽에 추가함
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        N = Integer.parseInt(br.readLine());

        StringTokenizer st = new StringTokenizer(br.readLine());
        for (int i = 0; i < N; i++) {
            knownWeight[i] = Integer.parseInt(st.nextToken());
        }

        setDp(0, 0);

        int M = Integer.parseInt(br.readLine());
        st = new StringTokenizer(br.readLine());
        StringBuilder answer = new StringBuilder();
        for (int i = 0; i < M; i++) {
            int weight = Integer.parseInt(st.nextToken());
            if(weight > 15000) answer.append("N ");
            else answer.append((dp[N][weight]) ? "Y " : "N ");
        }

        System.out.println(answer);
    }
}