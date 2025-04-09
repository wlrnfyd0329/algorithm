import java.util.*;
import java.io.*;

class Main {
	static int N, M;
	static int x, y;
	static int[][] board;
	static int[][][] vis;
	
	static int[] dx = {0, 1, 0, -1};
	static int[] dy = {1, 0, -1, 0};
	
	public static class Point {
		int x;
		int y;
		int turn;
		int key;
		
		public Point(int x, int y, int turn, int key) {
			this.x = x;
			this.y = y;
			this.turn = turn;
			this.key = key;
		}
	}

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());;

		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		board = new int[N][M];
		vis = new int[1 << 6][N][M];
		
		for(int i = 0; i < N; i++) {
			String s = br.readLine();
			for(int j = 0; j < M; j++) {
				char c = s.charAt(j);
				if (c == '.') {
					board[i][j] = 0;
				}
				if (c == '#') {
					board[i][j] = -(1 << 6);
				}
				if (c == '0') {
					board[i][j] = 0;
					x = i;
					y = j;
				}
				if (c == '1') {
					board[i][j] = (1 << 6);
				}
				if (c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f') {
					board[i][j] = (1 << (c - 'a'));
				}
				if (c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F') {
					
					board[i][j] = -(1 << (c - 'A'));
				}
			}
		}
		
		Queue<Point> q = new ArrayDeque<>();
		q.offer(new Point(x, y, 0, 0));
		vis[0][x][y] = 1;
		
		while(!q.isEmpty()) {
			Point cur = q.poll();
			
			for(int dir = 0; dir < 4; dir++) {
				int nx = cur.x + dx[dir];
				int ny = cur.y + dy[dir];
				if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
				if (board[nx][ny] == -(1 << 6) || vis[cur.key][nx][ny] == 1) continue;
				if (board[nx][ny] < 0) {
					if ((cur.key & -board[nx][ny]) > 0) {
						vis[cur.key][nx][ny] = 1;
						q.offer(new Point(nx, ny, cur.turn + 1, cur.key));
					}
				}
				else {
					if (board[nx][ny] == (1 << 6)) {
						System.out.println(cur.turn + 1);
						return;
					}
					else {
						vis[cur.key | board[nx][ny]][nx][ny] = 1;
						q.offer(new Point(nx, ny, cur.turn + 1, cur.key | board[nx][ny]));
					}
				}
			}
		}
		
		System.out.println(-1);
	}
	
}