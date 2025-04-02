import java.util.*;
import java.io.*;

class Solution {
	static int N, M, cnt, ans;
	static int[][] board;
	static int[] value;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		value = new int[45];
		for(int i = 1; i < 45; i++) {
			value[i] = i * i + (i - 1) * (i - 1);
		}

		int T = Integer.parseInt(br.readLine());
		for (int tc = 1; tc <= T; tc++) {
			st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			M = Integer.parseInt(st.nextToken());
			board = new int[N][N];
			ans = 0;
			cnt = 0;

			for (int i = 0; i < N; i++) {
				st = new StringTokenizer(br.readLine());
				for (int j = 0; j < N; j++) {
					board[i][j] = Integer.parseInt(st.nextToken());
					if (board[i][j] == 1) cnt++;
				}
			}

			
			for(int i = 0; i < N; i++) {
				for(int j = 0; j < N; j++) {
					ans = Math.max(ans, bfs(i, j));
				}
			}
			
			System.out.println("#" + tc + " " + ans);
		}
	}
	
	public static int bfs(int x, int y) {
		int[] home = new int[45];
		Queue<int[]> q = new ArrayDeque<>();
		int[][] vis = new int[N][N];
		int[] dx = {1, 0, -1, 0};
		int[] dy = {0, 1, 0, -1};
		
		vis[x][y] = 1;
		q.offer(new int[] {x, y});
		if (board[x][y] == 1) home[1]++;
		
		while(!q.isEmpty()) {
			int[] cur = q.poll();
			for(int dir = 0; dir < 4; dir++) {
				int nx = cur[0] + dx[dir];
				int ny = cur[1] + dy[dir];
				if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
				if (vis[nx][ny] > 0) continue;
				vis[nx][ny] = vis[cur[0]][cur[1]] + 1;
				q.offer(new int[] {nx, ny});
				if (board[nx][ny] == 1) home[vis[nx][ny]]++;
			}
		}
		
		int house = 0, res = 0;
		for(int i = 1; i < 45; i++) {
			house += home[i];
			if (house * M >= value[i]) res = Math.max(res, house);
			if (house >= cnt) break;
		}
		return res;
	}
}