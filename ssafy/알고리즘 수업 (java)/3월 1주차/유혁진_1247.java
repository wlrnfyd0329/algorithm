import java.io.*;
import java.util.*;

public class Solution {
	static int T;
	static int N;
	static int[] x;
	static int[] y;
	static int[][] dp;
	static int ans;
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		T = Integer.parseInt(br.readLine());
		
		for(int tc = 1; tc <= T; tc++) {
			N = Integer.parseInt(br.readLine());
			ans = 0;
			dp = new int[1 << (N + 1)][N + 1];
			
			st = new StringTokenizer(br.readLine());
			for(int i = 0; i < N; i++) {
				x[i] = Integer.parseInt(st.nextToken());
				y[i] = Integer.parseInt(st.nextToken());
			}
			
			dfs(0, 1);
			
			System.out.println("#" + tc + " " + dp[(1 << (N + 1)) - 1]);
		}
	}
	
	public static int dfs(int city, int check) {
		if (check == (1 << (N + 1)) - 1) {
			return dist(x[2 + city], y[2 + city], x[1], y[1]);
		}
		
		for(int i = 0; i < N + 1; i++) {
			int next = (1 << i);
			if ((check | next) == check) continue;
			dp[i][check|next] = Math.min(dp[i][check|next], dp[city][check] + dist(x[2 + city], y[2 + city], x[2 + i], y[2 + i]));
			dp[1<<i][cnt] = dist(x[0], y[0], x[2 + i], y[2 + i]);
		}
	}
	
	public static int dist(int x1, int y1, int x2, int y2) {
		return Math.abs(x1 - x2) + Math.abs(y1 - y2);
	}
}
