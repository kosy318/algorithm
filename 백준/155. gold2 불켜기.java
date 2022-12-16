import java.awt.Point;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Main {

    static int N;

    // 스위치 동작
    static HashMap<Point, ArrayList<Point>> switches = new HashMap<>();

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        // 헛간 크기
        N = Integer.parseInt(st.nextToken());

        int M = Integer.parseInt(st.nextToken());
        for(int i=0; i<M; i++){
            st = new StringTokenizer(br.readLine());

            // x, y 방에서 a, b 방의 불을 켜고 끌 수 있다.
            int x = Integer.parseInt(st.nextToken());
            int y = Integer.parseInt(st.nextToken());

            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());

            // x, y방이 key로 만들어진적이 없으면 ArrayList를 갱신해준다.
            if(!switches.containsKey(new Point(x-1, y-1))){
                switches.put(new Point(x-1, y-1), new ArrayList<Point>());
            }
            // x, y방에서 불을 켜고 끌 수 있는 방 삽입
            switches.get(new Point(x-1, y-1)).add(new Point(a-1, b-1));
        }

        // TODO: 불이 켜져있는 방의 최대 개수
        System.out.println(switchOn());
    }

    static int[] dx = {-1, 1, 0, 0};
    static int[] dy = {0, 0, -1, 1};

    private static int switchOn() {
        // 갈 수 있는곳 담은 que
        Queue<Point> que = new LinkedList<>();
        // 방문한 곳 체크할 배열
        boolean[][] visited = new boolean[N][N];
        // 불이 켜져있는지 체크할 배열
        boolean[][] on = new boolean[N][N];

        // 0, 0에서 시작
        que.add(new Point(0, 0));
        // 방문 체크
        visited[0][0] = true;
        // 0, 0이 켜져있음
        on[0][0] = true;
        int cnt = 1;

        while(!que.isEmpty()){
            Point cur = que.poll();

            // 현재 위치에 스위치가 있으면
            // 현재 위치의 스위치들 전부 누름
            if(switches.containsKey(cur)) {
                for (Point p : switches.get(cur)) {
                    if(on[p.x][p.y]) continue;
                    on[p.x][p.y] = true;
                    cnt += 1;

                    // 불이 켜진 곳 근처에 visited가 true인 곳이 있는지 확인
                    for (int d = 0; d < 4; d++) {
                        int nx = p.x + dx[d];
                        int ny = p.y + dy[d];

                        // 범위 안에 없으면 넘어감
                        if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;

                        // 방문한 곳이라는 것은 0, 0과 이어져있다는 의미
                        if (visited[nx][ny]) {
                            que.add(p);
                            visited[p.x][p.y] = true;
                            break;
                        }
                    }
                }
            }

            for (int d = 0; d < 4; d++) {
                int nx = cur.x + dx[d];
                int ny = cur.y + dy[d];

                // 범위 안에 없으면 넘어감
                if(nx<0 || ny<0 || nx>=N || ny>=N) continue;
                if(visited[nx][ny]) continue;

                // 방문하지 않았고 불이 켜져있으면
                if(on[nx][ny]) {
                    que.add(new Point(nx, ny));
                    visited[nx][ny] = true;
                }
            }
        }

        return cnt;
    }
    
}
