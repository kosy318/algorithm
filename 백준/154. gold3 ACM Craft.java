import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Main {

    static class Adj{
        ArrayList<Integer> list;

        // Adj가 생성될 때 list도 생성
        public Adj() {
            this.list = new ArrayList<>();
        }
    }
    
    static int N; // 건물의 개수
    static int[] time; // 건물을 짓는데 걸리는 시간; 1부터 시작
    static int[] indegree; // 각 건물의 진입차수
    static int target; // 이기려면 지어야하는 건물 번호
    static Adj[] adjList; // 인접한 리스트

    // 건물 짓는 순서가 주어져있음 -> 위상정렬
    // 건물 순서는 무조건 모든 건물이 건설 가능하도록 주어져있음
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

        int T = Integer.parseInt(br.readLine());
        for(int t=0; t<T; t++) {
            st = new StringTokenizer(br.readLine());

            N = Integer.parseInt(st.nextToken()); // 건물의 개수
            int K = Integer.parseInt(st.nextToken()); // 건설 순서 규칙의 총 개수

            st = new StringTokenizer(br.readLine());
            time = new int[N+1]; // 각 건물을 짓는데 걸리는 시간 1부터 시작
            for(int i=1; i<=N; i++){
                time[i] = Integer.parseInt(st.nextToken());
            }

            // 각 건물의 진입차수
            indegree = new int[N+1];
            // 인접 리스트
            adjList = new Adj[N+1];
            // 인접리스트 초기화
            for(int i=1; i<=N; i++){
                adjList[i] = new Adj();
            }
            // 건물을 짓는 순서 X 다음 Y
            for(int k=0; k<K; k++){
                st = new StringTokenizer(br.readLine());
                int X = Integer.parseInt(st.nextToken());
                int Y = Integer.parseInt(st.nextToken());

                // X에 Y가 연결되있음을 표시
                adjList[X].list.add(Y);

                // Y의 진입차수 1 증가
                indegree[Y] += 1;
            }

            target = Integer.parseInt(br.readLine()); // 이기기위해 건설해야하는 건물 번호

            // TODO: 전부 건설하는데 걸리는 최소 시간
            System.out.println(topologySort());
        }
    }

    private static int topologySort() {
        // 건물을 짓는데 걸리는 총 시간
        int[] buildTime = new int[N+1];
        Queue<Integer> build = new LinkedList<>();

        for (int i = 1; i <= N; i++) {
            if(indegree[i] == 0){
                buildTime[i] = time[i]; // i 빌딩 짓는데 time[i]시간 걸림
                build.add(i); // i빌딩 지었음

                if(i == target) return time[i];
            }
        }

        boolean end = false;
        while (!build.isEmpty()) {
            int building = build.poll();

            // building의 다음 빌딩들
            for (int b : adjList[building].list) {
                // 다음 빌딩을 짓는데 걸리는 총 시간 vs 지금 빌딩을 짓는데 걸리는 총 시간
                // 흐른 시간이라 생각하면 쉬움
                buildTime[b] = Math.max(buildTime[b], buildTime[building]);

                // 인접 노드 진입차수 -1
                indegree[b] -= 1;

                // 진입 차수가 0이 됐으면
                if(indegree[b] == 0){
                    buildTime[b] += time[b]; // b 빌딩 짓는데 time[b]시간 걸림
                    build.add(b); // b 빌딩 지었음

                    if(b == target) { // b가 target building이었다면 다 지었음
                        end = true;
                        break;
                    }
                }
            }
            if(end) break;
        }

        // target building을 짓는데 걸리는 총 시간 리턴
        return buildTime[target];
    }

}
