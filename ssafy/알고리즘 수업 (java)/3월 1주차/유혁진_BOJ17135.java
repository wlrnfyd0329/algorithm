import java.io.*;
import java.util.*;

public class Main {
	static int N;
	static int M;
	static int D;
	static int[][] board;
	static int[][] temp_board;
	static int[] archer;
	static int[] dx = {0, -1, 0};
	static int[] dy = {-1, 0, 1};
	static int ans;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		D = Integer.parseInt(st.nextToken());
		board = new int[N + 1][M + 1];
		temp_board = new int[N + 1][M + 1];
		archer = new int[3];
		ans = 0;
		
		for(int i = 1; i <= N; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j = 1; j <= M; j++) {
				board[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		combination(1, 0);
		
		System.out.println(ans);
	}
	
	public static void combination(int num, int cnt) {
		if (cnt == 3) {
			attack();
			return;
		}
		
		for(int i = num; i <= M; i++) {
			archer[cnt] = i;
			combination(i + 1, cnt + 1);
		}
	}
	
	public static void attack() {
		int cnt = 0;
		for(int i = 1; i <= N; i++) {
			for(int j = 1; j <= M; j++) {
				temp_board[i][j] = board[i][j];
			}
		}
		
		while(!isDone()) {
			int[][] enemy = new int[3][2];
			for(int i = 0; i < 3; i++) {
				Queue<int[]> q = new ArrayDeque<>();
				int[][] vis = new int[N + 2][M + 1];
				q.offer(new int[] {N + 1, archer[i]});
				while(!q.isEmpty()) {
					int[] cur = q.poll();
					if (vis[cur[0]][cur[1]] == D) break;
					for(int dir = 0; dir < 3; dir++) {
						int nx = cur[0] + dx[dir];
						int ny = cur[1] + dy[dir];
						if (nx <= 0 || nx > N || ny <= 0 || ny > M) continue;
						if (vis[nx][ny] > 0) continue;
						vis[nx][ny] = vis[cur[0]][cur[1]] + 1;
						q.offer(new int[] {nx, ny});
						if (temp_board[nx][ny] != 0) {
							enemy[i][0] = nx;
							enemy[i][1] = ny;
							break;
						}
					}
					
					if (enemy[i][0] != 0) break;
				}
			}
			
			for(int i = 0; i < 3; i++) {
				if (enemy[i][0] == 0) continue;
				if (temp_board[enemy[i][0]][enemy[i][1]] != 0) {
					cnt++;
					temp_board[enemy[i][0]][enemy[i][1]] = 0;
				}
			}
			
			move_enemy();
		}

		ans = Math.max(ans, cnt);
	}
	
	public static boolean isDone() {
		for(int i = 1; i <= N; i++) {
			for(int j = 1; j <= M; j++) {
				if (temp_board[i][j] != 0) return false;
			}
		}
		return true;
	}
	
	public static void move_enemy() {
		for(int i = N; i >= 1; i--) {
			for(int j = 1; j <= M; j++) {
				temp_board[i][j] = temp_board[i-1][j];
			}
		}
	}

}
