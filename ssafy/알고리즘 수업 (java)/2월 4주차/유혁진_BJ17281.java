import java.io.*;
import java.util.*;

public class 유혁진_BJ17281 {
    static int N;
    static int maxScore = 0;
    static int[][] arr;
    static int[] playerOrder;
    static int[] order;
    static boolean[] visit;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        N = Integer.parseInt(br.readLine());
        arr = new int[N][9];
        playerOrder = new int[9];
        order = new int[9];
        visit = new boolean[9];

        for(int i = 0; i < N; i++) {
            st = new StringTokenizer(br.readLine());
            for(int j = 0; j < 9; j++) {
                arr[i][j] = Integer.parseInt(st.nextToken());
            }
        }

        permutation(1);

        System.out.println(maxScore);
    }

    public static void permutation(int depth) {
        if (depth == 9) {
            for(int i = 0; i < 3; i++) {
                playerOrder[i] = order[i + 1];
            }
            playerOrder[3] = 0;
            for(int i = 4; i < 9; i++) {
                playerOrder[i] = order[i];
            }
            maxScore = Math.max(maxScore, playBall());
            return;
        }

        for(int i = 1; i < 9; i++) {
            if (visit[i]) continue;
            visit[i] = true;
            order[depth] = i;
            permutation(depth + 1);
            visit[i] = false;
        }
    }

    public static int playBall() {
        int outCount = 0;
        int score = 0;
        int player = 0;
        int base = 0;

        for(int game = 0; game < N; game++) {
            while(outCount != 3) {
                int hit = arr[game][playerOrder[player]];
                player = (player + 1) % 9;
                if (hit == 0) {
                    outCount++;
                }
                else if (hit == 4) {
                    for(int i = 0; i <= 2; i++) {
                        if ((base & (1 << i)) > 0) {
                            score++;
                        }
                    }
                    score++;
                    base <<= 3;
                }
                else {
                    for(int i = 3 - hit; i <= 2; i++) {
                        if ((base & (1 << i)) > 0) {
                            score++;
                        }
                    }
                    base <<= hit;
                    base |= 1 << (hit - 1);
                }
            }
            outCount = 0;
            base = 0;
        }
        return score;
    }
}