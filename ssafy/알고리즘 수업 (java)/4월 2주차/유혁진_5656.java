import java.util.*;
import java.io.*;

class Solution {
	static int T, N, W, H, ans;
	static int[][][] board;
	
	static int[] dx = {1, 0, -1, 0};
	static int[] dy = {0, 1, 0, -1};

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;

		int T = Integer.parseInt(br.readLine());
		for (int tc = 1; tc <= T; tc++) {
			st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			W = Integer.parseInt(st.nextToken());
			H = Integer.parseInt(st.nextToken());
			board = new int[N + 1][H][W];
			ans = Integer.MAX_VALUE;
			
			for(int i = 0; i < H; i++) {
				st = new StringTokenizer(br.readLine());
				for(int j = 0; j < W; j++) {
					board[0][i][j] = Integer.parseInt(st.nextToken());
				}
			}
			
			func(0);
			
			System.out.println("#" + tc + " " + ans);	
		}
	}
	
	public static void func(int n) { // O(W^N) : 12^4 * 735 = 20736 * 735 = 15,240,960
		if (n == N) {
			ans = Math.min(ans, getScore(n));
			return;
		}
		
		for(int i = 0; i < W; i++) {
			copy(n + 1); // O(H * W) : 180
			hit(i, n + 1); // O(H * W) : 375
			func(n + 1); // O(H * W) : 180
		}
	}
	
	public static void copy(int n) { // O(H * W) : 15 * 12 = 180
		for(int i = 0; i < H; i++) {
			for(int j = 0; j < W; j++) {
				board[n][i][j] = board[n - 1][i][j];
			}
		}
	}
	
	public static void hit(int c, int n) {  // O(H * W) : 15 * 12 * 2 + 15 = 375
		Queue<int[]> q = new ArrayDeque<>();
		int[][] vis = new int[H][W];
		for(int i = 0; i < H; i++) { // O(H) : 15;
			if (board[n][i][c] > 0) {
				q.offer(new int[] {i, c});
				vis[i][c] = 1;
				break;
			}
		}
		
		while(!q.isEmpty()) { // O(H * W) : 15 * 12 = 180
			int[] cur = q.poll();
			int num = board[n][cur[0]][cur[1]];
			board[n][cur[0]][cur[1]] = 0;
			if (num == 1) continue;
			for(int dir = 0; dir < 4; dir++) {
				int nx = cur[0];
				int ny = cur[1];
				for(int i = 1; i < num; i++) {
					nx += dx[dir];
					ny += dy[dir];
					if (nx < 0 || nx >= H || ny < 0 || ny >= W) break;
					if (board[n][nx][ny] > 0 || vis[nx][ny] == 0) {
						q.offer(new int[] {nx, ny});
						vis[nx][ny] = 1;
					}
				}
			}
		}
		
		for(int j = 0; j < W; j++) {  // O(H * W) : 15 * 12 = 180
			int idx = H - 1;
			for(int i = H - 1; i >= 0; i--) {
				if (board[n][i][j] > 0) {
					int num = board[n][i][j];
					board[n][i][j] = 0;
					board[n][idx--][j] = num;
				}
			}
		}
	}
	
	public static int getScore(int n) { // O(H * W) : 15 * 12 = 180
		int cnt = 0;
		
		for(int i = 0; i < H; i++) {
			for(int j = 0; j < W; j++) {
				if (board[n][i][j] != 0) cnt++;
			}
		}
		
		return cnt;
	}
}