import java.io.*;
import java.util.*;

public class Solution {
	static int T;
	static int N;
	static int[][] cheese;
	static int[] dx = {1, 0, 0, -1};
	static int[] dy = {0, -1, 1, 0};
	static int ans;
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		T = Integer.parseInt(br.readLine());
		
		for(int tc = 1; tc <= T; tc++) {
			N = Integer.parseInt(br.readLine());
			ans = 1;
			cheese = new int[N][N];
			
			for(int i = 0; i < N; i++) {
				st = new StringTokenizer(br.readLine());
				for(int j = 0; j < N; j++) {
					cheese[i][j] = Integer.parseInt(st.nextToken());
				}
			}
			
			for(int i = 1; i <= 100; i++) {
				eat_cheese(i);
			}
			
			System.out.println("#" + tc + " " + ans);
		}
	}
	
	public static void eat_cheese(int num) {
	    Queue<int[]> q = new LinkedList<>();
	    boolean[][] vis = new boolean[N][N];
	    int cnt = 0;
	    
	    for(int i = 0; i < N; i++) {
	    	for(int j = 0; j < N; j++) {
	    		if (vis[i][j] || cheese[i][j] <= num) continue;
	    		vis[i][j] = true;
	    		q.offer(new int[] {i, j});
	    		while(!q.isEmpty()) {
	    			int[] cur = q.poll();
	    			for(int dir = 0; dir < 4; dir++) {
	    				int nx = cur[0] + dx[dir];
	    				int ny = cur[1] + dy[dir];
	    				if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
	    				if (vis[nx][ny] || cheese[nx][ny] <= num) continue;
	    				vis[nx][ny] = true;
	    				q.offer(new int[] {nx, ny});
	    			}
	    		}
	    		cnt++;
	    	}
	    }
	    
	    ans = Math.max(ans, cnt);
	}
}
