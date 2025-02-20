import java.util.*;
import java.io.*;

public class 유혁진_5215 {
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine());
        for(int tc = 1; tc <= T; tc++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken());
            int l = Integer.parseInt(st.nextToken());
            int[][] arr = new int[l+1][n+1];
            int[][] hamburger = new int[n+1][2];
            for(int i = 1; i <= n; i++) {
                st = new StringTokenizer(br.readLine());
                hamburger[i][0] = Integer.parseInt(st.nextToken()); // 점수
                hamburger[i][1] = Integer.parseInt(st.nextToken()); // 칼로리
            }

            for(int i = 1; i <= l; i++) { // 칼로리
                for(int j = 1; j <= n; j++) { // 햄버거 종류
                    if (i >= hamburger[j][1]) {
                        arr[i][j] = Math.max(arr[i][j-1], arr[i - hamburger[j][1]][j-1] + hamburger[j][0]);
                    }
                    else {
                        arr[i][j] = arr[i][j-1];
                    }
                }
            }
             
            System.out.println("#" + tc + " " + arr[l][n]);
        }
    }
}