import java.io.*;
import java.util.*;

public class Main {
	static int K, W, H;
	static int[][] board;
	static int[][][] vis;
	
	static int[] dx = {1, 0, -1, 0};
	static int[] dy = {0, 1, 0, -1};
	static int[] ddx = {-2, -2, -1, -1, 1, 1, 2, 2};
	static int[] ddy = {-1, 1, -2, 2, -2, 2, -1, 1};
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		K = Integer.parseInt(br.readLine());
		StringTokenizer st = new StringTokenizer(br.readLine());
		W = Integer.parseInt(st.nextToken());
		H = Integer.parseInt(st.nextToken());
		board = new int[H][W];
		vis = new int[K + 1][H][W];
		Queue<int[]> q = new ArrayDeque<>();
		
		for(int i = 0; i < H; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j = 0; j < W; j++) {
				board[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		vis[0][0][0] = 1;
		q.offer(new int[] {0, 0, 0});
		while(!q.isEmpty()) {
			int[] cur = q.poll();
			
			if (cur[1] == H - 1 && cur[2] == W - 1) {
				System.out.println(vis[cur[0]][cur[1]][cur[2]] - 1);
				return;
			}
			
			for(int dir = 0; dir < 4; dir++) {
				int nx = cur[1] + dx[dir];
				int ny = cur[2] + dy[dir];
				if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
				if (board[nx][ny] == 1 || vis[cur[0]][nx][ny] > 0) continue;
				vis[cur[0]][nx][ny] = vis[cur[0]][cur[1]][cur[2]] + 1;
				q.offer(new int[] {cur[0], nx, ny});
			}
			
			if (cur[0] >= K) continue;
			for(int dir = 0; dir < 8; dir++) {
				int nx = cur[1] + ddx[dir];
				int ny = cur[2] + ddy[dir];
				if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
				if (board[nx][ny] == 1 || vis[cur[0] + 1][nx][ny] > 0) continue;
				vis[cur[0] + 1][nx][ny] = vis[cur[0]][cur[1]][cur[2]] + 1;
				q.offer(new int[] {cur[0] + 1, nx, ny});
			}
		}
		
		System.out.println(-1);
	}

}
