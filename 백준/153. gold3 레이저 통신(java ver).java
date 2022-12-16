import java.awt.Point;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class Main {

    static int N, M;
    static char[][] map; // 지도
    static int[][] memo; // 현재 최소 거울 개수

    // 최단 거리를 구하는 문제 -> BFS
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        M = Integer.parseInt(st.nextToken()); // 가로
        N = Integer.parseInt(st.nextToken()); // 세로

        map = new char[N][M]; // 지도 크기 지정
        memo = new int[N][M]; // 현재 최소 거울 개수 크기 지정
        ArrayList<Point> targets = new ArrayList<>(); // 통신해야하는 두 점
        for(int i=0; i<N; i++){
            // 띄어쓰기 없음 주의
            map[i] = br.readLine().toCharArray();
            for(int j=0; j<M; j++){
                // 통신해야하는 점이면 targets에 저장
                if(map[i][j] == 'C'){
                    targets.add(new Point(i, j));
                }
                memo[i][j] = Integer.MAX_VALUE;
            }
        }

        // TODO: 'c'로 표시된 칸끼리 통신하기 위해 설치해야하는 거울(/, \)의 개수의 최소값
        // 즉 꺾이는 횟수의 최소값
        System.out.println(bfs(targets.get(0), targets.get(1)));
    }

    // 0:상, 1:하, 2:좌, 3:우
    static int[] dx = {-1, 1, 0, 0};
    static int[] dy = {0, 0, -1, 1};

    static class Node implements Comparable<Node>{
        int x, y;
        int dir;
        int mirror;

        public Node(int x, int y, int dir, int mirror) {
            this.x = x;
            this.y = y;
            this.dir = dir;
            this.mirror = mirror;
        }

        @Override
        public int compareTo(Node n) { // mirror 기준으로 오름차순정렬
            if(this.mirror < n.mirror) return -1;
            else if(this.mirror > n.mirror) return 1;
            return 0;
        }
    }

    private static int bfs(Point start, Point end) {
        PriorityQueue<Node> que = new PriorityQueue<Node>();
        // 처음엔 사방으로 가도 mirror가 추가되지 않기 때문에 전부 추가해준다.
        for(int d=0; d<4; d++){
            que.add(new Node(start.x, start.y, d, 0));
        }
        // 시작 지점의 최소 값은 0이므로 갱신
        memo[start.x][start.y] = 0;

        while(!que.isEmpty()){
            // que에 들어있는 것 중 mirror가 가장 작은것 하나 뽑아냄
            Node cur = que.poll();

            // mirror 값이 현재 거울 값과 같거나 작다면 return
            if(cur.x==end.x && cur.y==end.y) return cur.mirror;
            
            for(int d=0; d<4; d++){
                int nx = cur.x + dx[d];
                int ny = cur.y + dy[d];
                
                // 범위를 벗어나면 지나감
                if(nx<0 || ny<0 || nx>=N || ny>=M) continue;
                // 벽이면 지나감
                if(map[nx][ny] == '*') continue;

                int nMirror = cur.mirror; // 다음 거울 개수
                if(cur.dir != d){ // 방향을 바꿨다면 거울을 추가해줘야한다.
                    nMirror += 1;
                }

                // 해당 위치의 다음 거울 개수가 현재까지 구한 거울 개수보다 크면 가져오는 의미가 없음
                if(memo[nx][ny] < nMirror) continue;
                
                // 구한 값과 현재 진행한 방향을 좌표와 함꼐 넣어줌
                que.add(new Node(nx, ny, d, nMirror));

                // 전 값과 비교해서 최소값으로 갱신
                memo[nx][ny] = Math.min(memo[nx][ny], nMirror);
            }
        }
        
        return -1; // 접근하지 못하는 경우; 문제에는 없음
    }

}
