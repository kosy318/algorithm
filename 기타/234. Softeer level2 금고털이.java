import java.util.*;
import java.io.*;


public class Main {

    static class Jewel implements Comparable<Jewel>{
        int weight;
        int cost;

        Jewel(int w, int c){
            this.weight = w;
            this.cost = c;
        }

        /////////////// 틀린 부분 : 1, -1만 리턴해서 런타임 에러남..
        @Override
        public int compareTo(Jewel j){ // cost 기준 내림차순
            if(this.cost < j.cost)
                return 1;
            else if(this.cost == j.cost)
                return 0;
            else return -1;
        }
    }

    static List<Jewel> jewels = new ArrayList<>();

    public static void main(String args[]) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int W = Integer.parseInt(st.nextToken()); // W := 배낭의 무게
        int N = Integer.parseInt(st.nextToken()); // N := 귀금속의 종류

        for(int i=0; i<N; i++){
            st = new StringTokenizer(br.readLine());
            int w = Integer.parseInt(st.nextToken()), c = Integer.parseInt(st.nextToken());

            jewels.add(new Jewel(w, c));
        }

        Collections.sort(jewels);

        int answer = 0;
        for(Jewel jewel : jewels){
            if(W >= jewel.weight) {
                answer += jewel.cost * jewel.weight;
                W -= jewel.weight;
            } else {
                answer += jewel.cost * W;
                break;
            }

            if(W == 0) break;
        }

        System.out.println(answer);
    }

}