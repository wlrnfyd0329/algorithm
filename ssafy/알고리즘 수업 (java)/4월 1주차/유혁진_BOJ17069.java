
import java.io.*;
import java.util.*;

public class Main {
	static int N;
	static int[][] board;
	static long[][][] vis;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;

		N = Integer.parseInt(br.readLine());
		board = new int[N+1][N+1];
		vis = new long[3][N+1][N+1]; // 가로, 대각선, 세로
		
		for(int i = 1; i <= N; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j = 1; j <= N; j++) {
				board[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		vis[0][1][2] = 1;
		for(int i = 1; i <= N; i++) {
			for(int j = 1; j <= N; j++) {
				for(int k = 0; k < 3; k++) {
					if (vis[k][i][j] > 0) {
						if (k == 0) {
							go_right(i, j, k);
							go_cross(i, j, k);
						}
						if (k == 1) {
							go_right(i, j, k);
							go_cross(i, j, k);
							go_down(i, j, k);
						}
						if (k == 2) {
							go_cross(i, j, k);
							go_down(i, j, k);
						}
					}
				}
			}
		}

		System.out.println(vis[0][N][N] + vis[1][N][N] + vis[2][N][N]);
	}
	
	public static void go_right(int x, int y, int k) {
		int ny = y + 1;
		if (x <= 0 || x > N || ny <= 0 || ny > N) return;
		if (board[x][ny] == 0) {
			vis[0][x][ny] += vis[k][x][y];
		}
	}
	
	public static void go_cross(int x, int y, int k) {
		int[] dx = {0, 1, 1};
		int[] dy = {1, 0, 1};
		for(int i = 0; i < 3; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx <= 0 || nx > N || ny <= 0 || ny > N) return;
			if (board[nx][ny] == 1) return;
		}
		vis[1][x + dx[2]][y + dy[2]] += vis[k][x][y];
	}
	
	public static void go_down(int x, int y, int k) {
		int nx = x + 1;
		if (nx <= 0 || nx > N || y <= 0 || y > N) return;
		if (board[nx][y] == 0) {
			vis[2][nx][y] += vis[k][x][y];
		}
	}
}
