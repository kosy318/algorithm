import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {

    static int N, M; // 세로, 가로
    static int[][] map; // 지도
    static int[][] dp; // i, j위치에서 도착지점까지 갈 수 있는 경우의 수; -1은 아직 방문하지 않았음을 의미

    // 경로의 특징을 저장해야하는 문제 -> DP, DFS
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken()); // 세로크기
        M = Integer.parseInt(st.nextToken()); // 가로크기

        map = new int[N][M]; // 지도
        dp = new int[N][M]; // i, j위치에서 도착지점까지 갈 수 있는 경우의 수; -1은 아직 방문하지 않았음을 의미
        for(int i=0; i<N; i++){
            st = new StringTokenizer(br.readLine());
            for(int j=0; j<M; j++){
                map[i][j] = Integer.parseInt(st.nextToken());
                dp[i][j] = -1;
            }
        }

        // 도착지에서 도착지까지는 1가지 경우
        dp[N-1][M-1] = 1;

        // 입력 체크
//        for(int i=0; i<N; i++)
//            System.out.println(Arrays.toString(map[i]));

        // TODO: 제일 오른쪽 아래칸까지 가는데 높이가 더 낮은 지점으로만 이동이 가능하다. 이동하는 경로의 수?
        dp[0][0] = 0; // 시작하는 위치 방문 표시
        dfs(0, 0); // dp 채우기

        // 채운 dp 체크
//        for(int i=0; i<N; i++)
//            System.out.println(Arrays.toString(dp[i]));

        System.out.println(dp[0][0]);
    }

    static int[] dx = {-1, 1, 0, 0};
    static int[] dy = {0, 0, -1, 1};

    private static int dfs(int x, int y) {
//        System.out.println(toString());
        for(int d=0; d<4; d++){
            int nx = x + dx[d];
            int ny = y + dy[d];

            // 범위를 벗어나면
            if(nx >= N || ny >= M || nx < 0 || ny < 0) continue;

            // 범위 안에 속하고 내리막길이면
            if(map[x][y] > map[nx][ny]) {
                if (dp[nx][ny] >= 0) dp[x][y] += dp[nx][ny]; // 이 곳에서 도착지까지의 경로를 이미 탐색 완료 했음
                else {
                    dp[nx][ny] = 0; // 방문체크
                    // 다음 위치에서 목적지까지 가는 경로의 수들을 현재 위치에서 목적지까지 도달하는 경로의 수에 더해준다.
                    dp[x][y] += dfs(nx, ny);
                }
            }
        }
        return dp[x][y];
    }

}
