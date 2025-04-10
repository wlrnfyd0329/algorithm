import java.util.*;
import java.io.*;

class Main {
	static int R, C;
	static int[][] board;
	static int[][] vis;
	
	static int[] dx = {0, 1, 0, -1};
	static int[] dy = {1, 0, -1, 0};
	
	public static class Point {
		int x;
		int y;
		boolean isWater;
		
		public Point(int x, int y, boolean isWater) {
			this.x = x;
			this.y = y;
			this.isWater = isWater;
		}
	}

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());

		R = Integer.parseInt(st.nextToken());
		C = Integer.parseInt(st.nextToken());
		board = new int[R][C];
		vis = new int[R][C];
		Point start = new Point(0, 0, false);
		Queue<Point> q = new ArrayDeque<>();
		
		for(int i = 0; i < R; i++) {
			String s = br.readLine();
			for(int j = 0; j < C; j++) {
				char c = s.charAt(j);
				if (c == '.') {
					board[i][j] = 0;
				}
				if (c == 'X') {
					board[i][j] = -2;
				}
				if (c == 'D') {
					board[i][j] = 1;
				}
				if (c == 'S') {
					vis[i][j] = 1;
					start.x = i;
					start.y = j;
				}
				if (c == '*') {
					board[i][j] = -1;
					q.offer(new Point(i, j, true));
				}
			}
		}
		
		q.offer(start);
		
		while(!q.isEmpty()) {
			Point cur = q.poll();
			
			for(int dir = 0; dir < 4; dir++) {
				int nx = cur.x + dx[dir];
				int ny = cur.y + dy[dir];
				if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
				if (board[nx][ny] == -2) continue;
				if (cur.isWater == true) {
					if (board[nx][ny] == 1 || board[nx][ny] == -1) continue;
					board[nx][ny] = -1;
					q.offer(new Point(nx, ny, cur.isWater));
				}
				else {
					if (vis[nx][ny] > 0 || board[nx][ny] < 0) continue;
					if (board[nx][ny] == 1) {
						System.out.println(vis[cur.x][cur.y]);
						return;
					}
					vis[nx][ny] = vis[cur.x][cur.y] + 1;
					q.offer(new Point(nx, ny, cur.isWater));
				}
			}
		}
		
		System.out.println("KAKTUS");
	}
	
}