import java.awt.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Main {

    // 50이하 자연수
    static int N; // 세로
    static int M; // 가로

    static class Node implements Comparable<Node>{
        int height; // 높이
        int x, y; // 위치

        public Node(int height, int x, int y) {
            this.height = height;
            this.x = x;
            this.y = y;
        }

        @Override
        public int compareTo(Node o) {
            if(this.height > o.height) return 1;
            else if(this.height < o.height) return -1;
            return 0;
        }

        @Override
        public String toString() {
            return "Node{" +
                    "height=" + height +
                    ", x=" + x +
                    ", y=" + y +
                    '}';
        }
    }

    static int[][] water; // 각 칸에 물이 들어있는 정도
    static int[][] map; // 각 칸의 높이를 나타낸 지도
    static int answer; // 전체 물의 양

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        water = new int[N][M];
        map = new int[N][M];

        // 높이가 작은 순서대로 찾기 위한 queue
        PriorityQueue<Node> que = new PriorityQueue<>();
        for(int i=0; i<N; i++){
            char[] str = br.readLine().toCharArray();
            for (int j = 0; j < M; j++) {
                que.add(new Node(str[j] - '0', i, j));
                map[i][j] = str[j] - '0';
            }
        }

//        // 입력 체크
//        for (int i = 0; i < N; i++) {
//            System.out.println(Arrays.toString(map[i]));
//        }

        // TODO: 수영장에 얼만큼 물이 들어갈 수 있는지
        boolean[][] visited = new boolean[N][M]; // 이미 채운 곳인지 확인
        int curHeight = 0;
        while (!que.isEmpty()) {
            Node cur = que.poll();
            if(visited[cur.x][cur.y]) continue;

            int fill = checkHeight(cur, visited);
            if(fill == 0) continue; // 물이 차지 않는곳
            if(fill < 0) { // 물이 빠지는 곳
                cantFillCheck(cur, visited);

                // 들어간 물 체크
//                for (int i = 0; i < N; i++) {
//                    System.out.println(Arrays.toString(water[i]));
//                }
                continue;
            }
            fillWater(new Point(cur.x, cur.y), visited, fill);

            // 들어간 물 체크
//            for (int i = 0; i < N; i++) {
//                System.out.println(Arrays.toString(water[i]));
//            }
        }

        System.out.println(answer);
    }

    private static void cantFillCheck(Node start, boolean[][] visited) {
        boolean[][] fillVisited = new boolean[N][M];
        Queue<Point> que = new LinkedList<>();
        que.add(new Point(start.x, start.y));

        water[start.x][start.y] = -1;
        fillVisited[start.x][start.y] = true;

        while (!que.isEmpty()) {
            Point cur = que.poll();

            for(int d=0; d<4; d++){
                int nx = cur.x + dx[d];
                int ny = cur.y + dy[d];

                if(nx<0 || ny<0 || nx>=N || ny>=M) continue;
                if(!visited[nx][ny]) continue; // 아직 채울 곳이 아님
                if(fillVisited[nx][ny]) continue; // 이미 채움
                if(map[nx][ny] != start.height) continue; // 높이가 같은 곳만 돎

                water[nx][ny] = -1;

                que.add(new Point(nx, ny));
                fillVisited[nx][ny] = true;
            }
        }
    }

    // point와 연결된 모든 부분에 fill만큼 물을 더함
    private static void fillWater(Point start, boolean[][] visited, int fill) {
        boolean[][] fillVisited = new boolean[N][M]; // 이미 채운 곳인지 확인
        Queue<Point> que = new LinkedList<>();
        que.add(start);

        water[start.x][start.y] += fill;
        answer += fill;

        fillVisited[start.x][start.y] = true;

        while (!que.isEmpty()) {
            Point cur = que.poll();

            for(int d=0; d<4; d++){
                int nx = cur.x + dx[d];
                int ny = cur.y + dy[d];

                if(nx<0 || ny<0 || nx>=N || ny>=M) continue;
                if(!visited[nx][ny]) continue; // 아직 물을 채울 곳이 아님
                if(water[nx][ny] == -1) continue; // 물을 채울 수 없는 곳
                if(fillVisited[nx][ny]) continue; // 이미 물을 채움

                water[nx][ny] += fill;
                answer += fill;

                que.add(new Point(nx, ny));
                fillVisited[nx][ny] = true;
            }
        }
    }

    static int[] dx = {-1, 1, 0, 0};
    static int[] dy = {0, 0, -1, 1};

    private static int checkHeight(Node start, boolean[][] visited) {
//        // start Point 체크
//        System.out.println("start : " + start.toString());
        // 방문했던 높이 낮은 곳도 다시 방문해야하므로 BFS를 돌릴 새 visited가 필요
        boolean[][] checkVisited = new boolean[N][M];

        Queue<Point> que = new LinkedList<>();
        que.add(new Point(start.x, start.y));
        visited[start.x][start.y] = true;

        // start와 같은 높이들을 감싸고 있는 높은 높이 중 최소 높이
        int minHeight = 10;

        while (!que.isEmpty()) {
            Point cur = que.poll();
//            // cur 체크
//            System.out.println("cur : " + cur.toString());

            for (int d = 0; d < 4; d++) {
                int nx = cur.x + dx[d];
                int ny = cur.y + dy[d];

                // 바깥으로 물이 빠짐
                if (nx < 0 || ny < 0 || nx >= N || ny >= M) {
                    minHeight = 0;
                    continue;
                }
                // 방문 체크; start보다 낮거나 같은 높이들 중 물이 빠지는 곳이 있으면 minHeight 갱신
                if(visited[nx][ny] && map[nx][ny] <= start.height) {
                    if(water[nx][ny] == -1) minHeight = 0;
                }
                if(checkVisited[nx][ny]) continue;
                if(map[nx][ny] > start.height){ // 높이가 큰 것이 있으면 비교해서 넣어줌
                    minHeight = Math.min(map[nx][ny], minHeight);
                }else { // 높이가 같거나 작은 경우에만 탐색한다
                    que.add(new Point(nx, ny));
                    visited[nx][ny] = true;
                    checkVisited[nx][ny] = true;
                }
            }
//            System.out.println("minHeight : " + minHeight);
        }

        if(minHeight == 10) return 0; // 높이가 갱신되지 않았다면 채워질 수 있는 물이 없다는 얘기
        else return minHeight - start.height;
    }

}