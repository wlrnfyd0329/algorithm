import java.util.*;
import java.io.*;

class Solution {
	static int N, M, R, C, L, ans;
	static int[][] board;
	static int[][] vis;
	static Queue<int[]> q;
	static int[] dx = {-1, 1, 0, 0}; // 상 하 좌 우
	static int[] dy = {0, 0, -1, 1};
	static int[][] type = {
			{0, 4, 2, 2, 2, 2, 2, 2},
			{0, 1, 2, 3},
			{0, 1},
			{2, 3},
			{0, 3},
			{1, 3},
			{1, 2},
			{0, 2},
	};

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;

		int T = Integer.parseInt(br.readLine());
		for (int tc = 1; tc <= T; tc++) {
			st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			M = Integer.parseInt(st.nextToken());
			R = Integer.parseInt(st.nextToken());
			C = Integer.parseInt(st.nextToken());
			L = Integer.parseInt(st.nextToken());
			ans = 1;
			board = new int[N][M];
			vis = new int[N][M];
			q = new ArrayDeque<>();

			for (int i = 0; i < N; i++) {
				st = new StringTokenizer(br.readLine());
				for (int j = 0; j < M; j++) {
					board[i][j] = Integer.parseInt(st.nextToken());
				}
			}

			q.offer(new int[] {R, C});
			vis[R][C] = 1;
			
			while(!q.isEmpty()) {
				int[] cur = q.poll();
				if (vis[cur[0]][cur[1]] == L) break;
				for(int i = 0; i < type[0][board[cur[0]][cur[1]]]; i++) {
					int nx = cur[0] + dx[type[board[cur[0]][cur[1]]][i]];
					int ny = cur[1] + dy[type[board[cur[0]][cur[1]]][i]];
					if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
					if (vis[nx][ny] > 0 || board[nx][ny] == 0) continue;
					for(int j = 0; j < type[0][board[nx][ny]]; j++) {
						if ((type[board[cur[0]][cur[1]]][i] ^ 1) == type[board[nx][ny]][j]) {
							vis[nx][ny] = vis[cur[0]][cur[1]] + 1;
							ans++;
							q.offer(new int[] {nx, ny});
						}
					}
				}
			}
			
			System.out.println("#" + tc + " " + ans);
		}
	}
}