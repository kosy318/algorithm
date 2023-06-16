import java.io.*;

public class Main {

    static String inp;
    static String answer = "-1";
    static int[] cnt = {0, 0, 0}; // a, b, c의 개수
    // dp[a][b][c][i][j] := a, b, c의 개수를 가지고, 이전 글자가 i, 그 이전 글자가 j인 경우를 확인 했는지 여부
    static boolean[][][][][] visited = new boolean[50][50][50][3][3];

    public static void main(String args[]) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        inp = br.readLine();

        for (int i=0; i<inp.length(); i++) {
            if(inp.charAt(i) == 'A') cnt[0] += 1;
            else if(inp.charAt(i) == 'B') cnt[1] += 1;
            else cnt[2] += 1;
        }

        dfs(cnt[0], cnt[1], cnt[2], 0, 0, "");

        System.out.println(answer);
    }

    public static void dfs(int a, int b, int c, int p1, int p2, String mem) {
        if(!answer.equals("-1")) return; // 답을 찾았음

        // test
//        System.out.println(a + " " + b + " " + c + " " + p1 + " " + p2 + " " + mem);

        if (a + b + c == 0) { // a, b, c 다 사용 완료
            answer = mem;
            return;
        }

        if (visited[a][b][c][p1][p2]) { // 이미 계산한 값, 여기서 answer가 완성 됐으면 이미 return 돼서 출력 됐음.
            return;
        }
        // 방문 체크
        visited[a][b][c][p1][p2] = true;

        if (c > 0 && p1 != 2 && p2 != 2) { // c를 넣을 수 있으면
            dfs(a, b, c - 1, 2, p1, mem + 'C');
        }

        if (b > 0 && p1 != 1) { // b를 넣을 수 있으면
            dfs(a, b - 1, c, 1, p1, mem + 'B');
        }

        if (a > 0) { // a를 넣을 수 있으면
            dfs(a - 1, b, c, 0, p1, mem + 'A');
        }
    }
}