import java.util.*;
import java.io.*;

public class 유혁진_2001 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine());
        for(int tc = 1; tc <= T; tc++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken());
            int m = Integer.parseInt(st.nextToken());
            int cnt = 0;
            int[][] arr = new int[n][n];
            for(int i = 0; i < n; i++) {
                st = new StringTokenizer(br.readLine());
                for(int j = 0; j < n; j++) {
                    arr[i][j] = Integer.parseInt(st.nextToken());
                }
            }

            for(int r = 0; r <= n - m; r++) {
                for(int c = 0; c <= n - m; c++) {
                    int temp = 0;
                    for(int i = 0; i < m; i++) {
                        for(int j = 0; j < m; j++) {
                            temp += arr[r+i][c+j];
                        }
                    }
                    cnt = Math.max(cnt, temp);
                }
            }
            
            System.out.println("#" + tc + " " + cnt);
        }
    }
}