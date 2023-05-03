import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int N = Integer.parseInt(st.nextToken());
        int M = Integer.parseInt(st.nextToken());

        char[][] board = new char[N][M];
        for (int i = 0; i < N; i++) {
            board[i] = br.readLine().toCharArray();
        }

        int answer = 0;
        int[][] dp = new int[N][M];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if(board[i][j] == '1') {
                    int top = 0, leftTop = 0, left = 0; // 왼쪽, 왼쪽 위, 위쪽 정사각형의 최대 크기 0으로 초기화

                    // 각 위치에서 정사각형의 최대 크기를 받아옴
                    if (i - 1 >= 0) top = dp[i - 1][j];
                    if (i - 1 >= 0 && j - 1 >= 0) leftTop = dp[i - 1][j - 1];
                    if (j - 1 >= 0) left = dp[i][j - 1];

                    dp[i][j] = Math.min(top, Math.min(leftTop, left)) + 1; // 왼쪽, 왼쪽 위, 위를 비교해서 가장 작은것에 + 1 한 값이 해당 위치에서 최대 크기의 정사각형 한 변의 길이

                    if(answer < dp[i][j]) answer = dp[i][j];
                }
            }
        }

        System.out.println(answer * answer);
    }

}