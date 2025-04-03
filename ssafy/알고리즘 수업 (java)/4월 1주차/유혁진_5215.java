import java.util.*;
import java.io.*;

class Solution {
	static int N, L;
	static int[][] hamburger; // [0] 점수, [1] 칼로리
	static int[][] dp; // [선택한 재료][현재 칼로리] 해당 맛의 최대 점수

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;


		int T = Integer.parseInt(br.readLine());
		for (int tc = 1; tc <= T; tc++) {
			st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			L = Integer.parseInt(st.nextToken());
			hamburger = new int[N + 1][2];
			dp = new int[N + 1][L + 1];
			
			for(int i = 1; i <= N; i++) {
				st = new StringTokenizer(br.readLine());
				hamburger[i][0] = Integer.parseInt(st.nextToken());
				hamburger[i][1] = Integer.parseInt(st.nextToken());
			}
			
			for(int type = 1; type <= N; type++) {
				for(int cal = 1; cal <= L; cal++) {
					if (cal < hamburger[type][1]) continue;
					dp[type][cal] = Math.max(dp[type - 1][cal - hamburger[type][1]] + hamburger[type][0], dp[type - 1][cal]);
				}
			}
			
			System.out.println("#" + tc + " " + dp[N][L]);
		}
	}
}