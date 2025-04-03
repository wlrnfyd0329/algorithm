import java.util.*;
import java.io.*;

class Solution {
	static int N, K, ans;
	static int[][] board;
	static boolean[][] vis;
	
	static int[] dx = {1, 0, -1, 0};
	static int[] dy = {0, 1, 0, -1};

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;


		int T = Integer.parseInt(br.readLine());
		for (int tc = 1; tc <= T; tc++) {
			st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			K = Integer.parseInt(st.nextToken());
			ans = 0;
			board = new int[N][N];
			vis = new boolean[N][N];
			int max_value = 0;
			
			for(int i = 0; i < N; i++) {
				st = new StringTokenizer(br.readLine());
				for(int j = 0; j < N; j++) {
					board[i][j] = Integer.parseInt(st.nextToken());
					max_value = Math.max(max_value, board[i][j]);
				}
			}
			
			for(int i = 0; i < N; i++) {
				for(int j = 0; j < N; j++) {
					if (board[i][j] == max_value) {
						vis[i][j] = true;
						dfs(i, j, true, 1);
						vis[i][j] = false;
					}
				}
			}
			
			System.out.println("#" + tc + " " + ans);
		}
	}
	
	public static void dfs(int x, int y, boolean isBroken, int cnt) {
		ans = Math.max(ans, cnt);
		
		for(int dir = 0; dir < 4; dir++) {
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
			if (vis[nx][ny]) continue;
			if (board[nx][ny] < board[x][y]) {
				vis[nx][ny] = true;
				dfs(nx, ny, isBroken, cnt + 1);
				vis[nx][ny] = false;
			}
			else {
				if (isBroken) {
					for(int k = 1; k <= K; k++) {
						if (board[nx][ny] - k < board[x][y]) {
							board[nx][ny] -= k;
							vis[nx][ny] = true;
							dfs(nx, ny, !isBroken, cnt + 1);
							board[nx][ny] += k;
							vis[nx][ny] = false;
						}
					}
				}
			}
		}
	}
}