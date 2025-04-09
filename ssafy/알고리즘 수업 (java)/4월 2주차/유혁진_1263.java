import java.util.*;
import java.io.*;

class Solution {
	static int T, N, ans;
	static int[][] graph;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;

		int T = Integer.parseInt(br.readLine());
		for (int tc = 1; tc <= T; tc++) {
			st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			graph = new int[N][N];
			ans = Integer.MAX_VALUE;
			
			for(int i = 0; i < N; i++) {
				for(int j = 0; j < N; j++) {
					graph[i][j] = Integer.parseInt(st.nextToken());
				}
			}
			
			for(int k = 0; k < N; k++) {
				for(int i = 0; i < N; i++) {
					for(int j = 0; j < N; j++) {
						int start = graph[i][k];
						int end = graph[k][j];
						if (start == 0 || end == 0) continue;
						if (graph[i][j] == 0) graph[i][j] = start + end;
						else if (graph[i][j] > start + end) {
							graph[i][j] = start + end;
						}
					}
				}
			}
			
			for(int i = 0; i < N; i++) {
				int sum = 0;
				for(int j = 0; j < N; j++) {
					if (i == j) continue;
					sum += graph[i][j];
				}
				ans = Math.min(ans, sum);
			}
			
			System.out.println("#" + tc + " " + ans);	
		}
	}
	
}