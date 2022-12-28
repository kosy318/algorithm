import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {

    static int N, M; // 가로 세로
    static int K; // K칸까지 이동 가능

    static char[][] board; // 문자판
    static String target;

    // DP[i][j][k]: i, j위치의 문자가 target의 k번째 문자일때 만들 수 있는 문자의 수
    static int[][][] DP;

    // 경로의 특징을 저장하는 문제 -> DFS
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());

        board = new char[N][M];

        for (int i = 0; i < N; i++) {
            board[i] = br.readLine().toCharArray();
        }

        target = br.readLine();

        // DP 초기화
        DP = new int[N][M][target.length()];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                Arrays.fill(DP[i][j], -1);
            }
        }

        // TODO: 주어진 단어를 만들 수 있는 경로가 총 몇개인지
        int route = 0; // 경로의 수
        // 주어진 단어의 첫번째 문자 찾기
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (board[i][j] == target.charAt(0)) {
                    route += dfs(i, j, 0);
                }
            }
        }

        System.out.println(route);
    }

    // 상하좌우 두칸씩 이동 가능
    static int[] dx = {-1, 1, 0, 0};
    static int[] dy = {0, 0, -1, 1};

    // x, y위치가 target의 idx번째를 나타낼때, 다음 문자 찾음
    private static int dfs(int x, int y, int idx) {
        if(idx == target.length() - 1) return 1; // 마지막 문자에 도달
        int route = 0;

        // 최대 K칸까지 이동 가능
        for (int k = 1; k <= K; k++) {
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d]*k;
                int ny = y + dy[d]*k;

                if(nx<0 || ny<0 || nx>=N || ny>=M) continue;
                // 다음 구할 문자와 이동할 곳의 문자가 일치할때
                if(target.charAt(idx+1) == board[nx][ny]){
                    // 이미 이동할 곳에서 idx+1번째의 경우 경로의 수를 구한적이 있다면 리턴
                    if(DP[nx][ny][idx+1] != -1) route += DP[nx][ny][idx+1];
                    else route += dfs(nx, ny, idx + 1);
                }
            }
        }

        return DP[x][y][idx] = route;
    }

}