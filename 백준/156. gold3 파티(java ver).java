import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class Main {

    static class Node implements Comparable<Node> {
        int vertex;
        int time;

        public Node(int vertex, int time) {
            this.vertex = vertex;
            this.time = time;
        }

        @Override
        public int compareTo(Node o) { // time 기준 오름차순 정렬
            if(this.time > o.time) return 1;
            else if(this.time < o.time) return -1;
            return 0;
        }
    }

    static class Edge{
        ArrayList<Node> list;

        public Edge() {
            this.list = new ArrayList<>();
        }
    }

    static int N; // 마을 개수
    static int X; // 파티를 벌이는 마을
    static Edge[] adjList; // adjList[i]: i번째에서 갈 수 있는 모든 정점과 시간

    // 한 정점에서 다른 정점까지 걸리는 시간 -> Dijkstra
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken()); // 마을 개수
        int M = Integer.parseInt(st.nextToken()); // 단방향 도로 개수
        X = Integer.parseInt(st.nextToken()); // 도착 마을 번호

        adjList = new Edge[N+1]; // T크기 지정
        for(int i=1; i<=N; i++){
            adjList[i] = new Edge();
        }

        for(int i=0; i<M; i++){
            st = new StringTokenizer(br.readLine());
            int start = Integer.parseInt(st.nextToken());
            int end = Integer.parseInt(st.nextToken());
            int t = Integer.parseInt(st.nextToken());

            adjList[start].list.add(new Node(end, t));
        }

        // TODO: N명의 학생들 중 오고 가는데 가장 많은 시간을 소비하는 학생의 소요 시간
        int[] time = new int[N + 1]; // time[i]: i~X 왕복 소요시간; i는 1부터 N
        time[X] = 0; // 파티가 벌어지는 장소에서 걸리는 시간은 무조건 0이다.
        for(int i=1; i<=N; i++){
            if(i == X) continue; // time[X]==0

            time[i] += dijkstra(i, X); // i에서 X로 가는 데 걸리는 최소 시간
            time[i] += dijkstra(X, i); // X에서 i로 가는 데 걸리는 최소 시간
        }

        Arrays.sort(time); // 오름차순 정렬
        System.out.println(time[N]);
    }

    // start에서 end까지 가는 데 걸리는 최소 시간
    private static int dijkstra(int start, int end) {
        int[] time = new int[N+1]; // time[i]: 출발지에서 i까지 가는데 소요되는 최소비용
        boolean[] visited = new boolean[N+1]; // 처리 완료한 정점 여ㅐ부
        PriorityQueue<Node> que = new PriorityQueue<>(); // 방문해야하는 정점 중 출발지에서 가장 가까운 정점을 찾기위함

        Arrays.fill(time, Integer.MAX_VALUE);
        time[start] = 0; // 출발지점 처리

        que.add(new Node(start, 0));

        while(!que.isEmpty()){
            // 미방문 정점 중 출발지에서 비용이 최소인 정점 선택
            Node cur = que.poll();

            if (visited[cur.vertex]) continue;
            visited[cur.vertex] = true;

            // 구하고 싶은 vertex면 끝내면 됨
            if(cur.vertex == end) return time[end];

            for (Node adj : adjList[cur.vertex].list) {
                // 시작점에서 선택된 정점(cur)을 경유지로
                // 선택된 정점의 주변 정점(adj)들로 가는 비용을 따져보고
                // 기존 최적해(time[adj.vertex])보다 유리하면 갱신
                // start -> cur -> adj
                if(!visited[adj.vertex] && time[adj.vertex] > cur.time + adj.time){
                    time[adj.vertex] = cur.time + adj.time;
                    que.add(new Node(adj.vertex, time[adj.vertex]));
                }
            }
        }

        return time[end];
    }

}