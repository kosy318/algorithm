import java.util.*;
import java.io.*;
import java.awt.Point;


public class Main {

    static class Color{
        List<Point> points = new ArrayList<>();
    }

    static int N; // N := 점의 개수
    static int K; // K := 색의 개수
    static Color[] colorList = new Color[21];
    static int answer = Integer.MAX_VALUE;

    public static void main(String args[]) throws Exception {
        /////// 틀린 부분 : 배열 초기화
        for(int i=1; i<=20; i++){
            colorList[i] = new Color();
        }

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());

        for(int i=0; i<N; i++){
            st = new StringTokenizer(br.readLine());

            int x = Integer.parseInt(st.nextToken());
            int y = Integer.parseInt(st.nextToken());
            int k = Integer.parseInt(st.nextToken());

            colorList[k].points.add(new Point(x, y));
        }

        for(Point point : colorList[1].points){
            dfs(point.x, point.y, point.x, point.y, 1, 0);
        }

        System.out.println(answer);
    }

    public static void dfs(int minX, int minY, int maxX, int maxY, int color, int area){ // color까지 계산한 값 : area
        if(color == K){
            if(area < answer) answer = area;
            return;
        }

        for(Point point : colorList[color + 1].points){
            ////////// 틀린 부분 : minX, ... maxY를 그대로 사용하면 안됨. 값이 바뀌면 다음 좌표에 영향이 감감
            int x1 = minX, y1 = minY, x2 = maxX, y2 = maxY;
            x1 = (minX > point.x)? point.x : minX;
            y1 = (minY > point.y)? point.y : minY;
            x2 = (maxX < point.x)? point.x : maxX;
            y2 = (maxY < point.y)? point.y : maxY;

            area = (x2 - x1)*(y2 - y1);
            if(area < answer){
                dfs(x1, y1, x2, y2, color + 1, area);
            }
        }
    }

}