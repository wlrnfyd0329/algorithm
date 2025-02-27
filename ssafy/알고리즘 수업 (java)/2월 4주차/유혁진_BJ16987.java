import java.io.*;
import java.util.*;

public class Main {
    public static class Egg {
        int s;
        int w;
        Egg (int s, int w) {
            this.s = s;
            this.w = w;
        }
    }

    static int N;
    static int res = 0;
    static Egg[] eggs;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        N = Integer.parseInt(br.readLine());
        eggs = new Egg[N];

        for(int i = 0; i < N; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            eggs[i] = new Egg(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));
        }

        hit(0);

        System.out.println(res);
    }

    public static void hit(int idx) {
        if (idx == N) {
            int zero = 0;
            for(int i = 0; i < N; i++) {
                if (eggs[i].s <= 0) zero++;
            }
            res = Math.max(res, zero);
            return;
        }

        if (eggs[idx].s <= 0) {
            hit(idx + 1);
            return;
        }

        boolean isAlone = true;
        for(int i = 0; i < N; i++) {
            if (i == idx || eggs[i].s <= 0) continue;
            isAlone = false;
            eggs[i].s -= eggs[idx].w;
            eggs[idx].s -= eggs[i].w;
            hit(idx + 1);
            eggs[i].s += eggs[idx].w;
            eggs[idx].s += eggs[i].w;
        }

        if (isAlone) hit(N);
    }

}