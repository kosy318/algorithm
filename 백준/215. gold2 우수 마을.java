import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class Main {
    static int[][] dp = new int[10001][2];
    static int[] cost = new int[10001];
    static List<List<Integer>> adjList = new ArrayList<>();
    static int[] cameFrom = new int[10001];
    static int answer;

    static void dfs(int cur) {
        dp[cur][0] = 0;
        dp[cur][1] = cost[cur];

        for (var next : adjList.get(cur)) {
            if(cameFrom[cur] == next) continue;
            cameFrom[next] = cur;
            dfs(next);

            dp[cur][0] += Math.max(dp[next][0], dp[next][1]); // cur이 우수마을이 아니면 next가 우수마을 이거나 아니거나
            dp[cur][1] += dp[next][0]; // cur이 우수마을이면 next는 우수마을이면 안됨

            answer = Math.max(dp[cur][0], dp[cur][1]);
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int N = Integer.parseInt(st.nextToken());
        for (int i = 0; i <= N; i++) {
            adjList.add(new ArrayList<>());
        }

        st = new StringTokenizer(br.readLine());
        for (int i = 1; i <= N; i++) {
            cost[i] = Integer.parseInt(st.nextToken());
        }

        for (int i = 0; i < N - 1; i++) {
            st = new StringTokenizer(br.readLine());
            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());

            adjList.get(a).add(b);
            adjList.get(b).add(a);
        }

        dfs(1);

        System.out.println(answer);
    }
}