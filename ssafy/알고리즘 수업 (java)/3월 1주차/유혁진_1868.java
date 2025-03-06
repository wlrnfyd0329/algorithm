import java.io.*;
import java.util.*;

public class Solution {
	static int T;
	static int N;
	static int[][] board;
	static boolean[][] vis;
	static int[] dx = {1, 1, 1, 0, 0, -1, -1, -1};
	static int[] dy = {-1, 0, 1, -1, 1, -1, 0, 1};
	static Queue<int []> q;
	static int ans;
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		T = Integer.parseInt(br.readLine());
		
		for(int tc = 1; tc <= T; tc++) {
			N = Integer.parseInt(br.readLine());
			ans = 0;
			board = new int[N][N];
			vis = new boolean[N][N];
			q = new LinkedList<>();
			
			for(int i = 0; i < N; i++) {
				String s = br.readLine();
				for(int j = 0; j < N; j++) {
					if (s.charAt(j) == '.') {
						ans++;
						board[i][j] = 0;
					}
					else {
						board[i][j] = -1;
					}
				}
			}
			
			check_mine();
			decide_result();
			
			System.out.println("#" + tc + " " + ans);
		}
	}
	
	public static void check_mine() {
	    for(int i = 0; i < N; i++) {
	        for(int j = 0; j < N; j++) {
	            if (board[i][j] == -1) continue;
	            int cnt = 0;
	            for(int k = 0; k < 8; k++) {
	                int nx = i + dx[k];
	                int ny = j + dy[k];
	                if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
	                if (board[nx][ny] == -1) cnt++;
	            }
	            board[i][j] = cnt;
	            if (cnt == 0) q.offer(new int[] {i, j});
	        }
	    }
	}
	
	public static void decide_result() {
	    while(!q.isEmpty()) {
	        int[] cur = q.poll();
	        if (vis[cur[0]][cur[1]]) continue;
	        Queue<int []> tq = new LinkedList<>();
	        tq.offer(new int [] {cur[0], cur[1]});
	        vis[cur[0]][cur[1]] = true;
	        while(!tq.isEmpty()) {
	            int[] tcur = tq.poll();
	            for(int k = 0; k < 8; k++) {
	                int nx = tcur[0] + dx[k];
	                int ny = tcur[1] + dy[k];
	                if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
	                if (vis[nx][ny] || board[nx][ny] == -1) continue;
	                if (board[nx][ny] == 0) {
	                    tq.offer(new int[] {nx, ny});
	                } 
	                vis[nx][ny] = true;
	                ans--;
	            }
	        }
	    }
	}
}
