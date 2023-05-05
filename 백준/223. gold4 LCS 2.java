import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Main {

    static int[][] dp = new int [1001][1001]; // dp[i][j] := i번째, j번째까지 고려했을 때 LCS 값
    // i-1 번째 string까지 j-1번째까지 고려했을 때 LCS 값은 변함이 없으므로 그대로 가져오고
    // 이후 i번째를 고려해줌?
    // dp[i][j] = dp[i-1][j-1] + (str[i] == str[j])? 1 : 0;

    static String[][] lcs = new String[1001][1001];

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String str1 = br.readLine();
        String str2 = br.readLine();

        Arrays.fill(lcs[0], "");
        for (int i = 1; i <= str1.length(); i++) {
            Arrays.fill(lcs[i], "");
            for (int j = 1; j <= str2.length(); j++) {
                if(str1.charAt(i-1) != str2.charAt(j-1)){
                    if (dp[i - 1][j] > dp[i][j - 1]) {
                        dp[i][j] = dp[i-1][j];
                        lcs[i][j] = lcs[i-1][j];
                    }else{
                        dp[i][j] = dp[i][j-1];
                        lcs[i][j] = lcs[i][j-1];
                    }
                }
                else{
                    if (dp[i - 1][j - 1] + 1 > dp[i][j - 1]) {
                        dp[i][j] = dp[i-1][j-1] + 1;
                        lcs[i][j] = lcs[i - 1][j - 1] + str1.charAt(i-1);
                    }
                    else{
                        dp[i][j] = dp[i][j-1];
                        lcs[i][j] = lcs[i][j-1];
                    }
                }
            }
        }

        int x = str1.length();
        int y = str2.length();

        System.out.println(dp[x][y]);
        System.out.println(lcs[x][y]);
    }
}