import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {

    static int N;
    static int[][] board = new int[16][16];
    static int[][] dp = new int[16][1 << 16]; // dp[i][j] := bitmasking(j)들을 들렸다가 i로 왔을 때 최소값
    static final int START = 0;
    static int END;

    private static int dfs(int cur, int visited) { // cur을 마지막으로 visit 했고, 방문한 정보는 visited에 담겨있음
        if (visited == END) { // 전부 방문함
            if (board[cur][START] != 0) { // 시작 위치로 돌아갈 수 있다면 순회 가능한 것
                return board[cur][START];
            }

            return (int) 1e9;
        }

        // 이미 cur을 마지막으로 visited 들을 방문한 정보가 있다면 그대로 리턴
        if(dp[cur][visited] != 0) return dp[cur][visited];

        dp[cur][visited] = (int) 1e9;

        for (int i = 0; i < N; i++) {
            // cur에서 i로 못감
            if(board[cur][i] == 0) continue;

            // i는 이미 방문했음
            /////////////// 틀린 부분 : 1<<i랑 비교해야함..
            if((visited & (1 << i)) == (1 << i)) continue;

            dp[cur][visited] = Math.min(dp[cur][visited], board[cur][i] + dfs(i, visited | (1 << i)));
        }

        return dp[cur][visited];
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        N = Integer.parseInt(br.readLine());
        END = (1 << N) -1;

        for (int i = 0; i < N; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            for (int j = 0; j < N; j++) {
                board[i][j] = Integer.parseInt(st.nextToken());
            }
        }

        System.out.println(dfs(START, 1));
    }

}