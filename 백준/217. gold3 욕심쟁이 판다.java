import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {

    static int N = 0;
    static int[][] forest = new int[500][500];
    static int[][] dp = new int[500][500];

    static int[] dx = {-1, 1, 0, 0};
    static int[] dy = {0, 0, -1, 1};
    static int dfs(int i, int j, int cnt) {
        int max = 0;
        for (int d = 0; d < 4; d++) {
            int nx = i + dx[d];
            int ny = j + dy[d];

            if(nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
            if(forest[nx][ny] <= forest[i][j]) continue; // 이미 방문했거나 대나무가 더 적으면 안감

            int ret = (dp[nx][ny] == 0)? dfs(nx, ny, cnt + 1) : dp[nx][ny];
            if(ret > max) max = ret;
        }

        return dp[i][j] = max + 1;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        N = Integer.parseInt(br.readLine());

        StringTokenizer st;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(br.readLine());
            for (int j = 0; j < N; j++) {
                forest[i][j] = Integer.parseInt(st.nextToken());
            }
        }

        int answer = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int ret = dfs(i, j, 1);
                if(ret > answer) answer = ret;
            }
        }

        System.out.println(answer);
    }
}
