import java.io.*;
import java.util.*;

public class Solution {
	static int N;
	static int[][] board;
	static int[][][] map;
	static ArrayList<int []> cores;
	static int core_cnt;
	static int max_cnt;
	static int line_cnt;
	static int min_line;
	
	static int[] dx = {0, 1, 0, -1};
	static int[] dy = {1, 0, -1, 0};
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		int T = Integer.parseInt(br.readLine());
		for(int tc = 1; tc <= T; tc++) {
			N = Integer.parseInt(br.readLine());
			board = new int[N][N];
			core_cnt = 0;
			max_cnt = 0;
			line_cnt = 0;
			min_line = Integer.MAX_VALUE;
			cores = new ArrayList<>();
			for(int i = 0; i < N; i++) {
				st = new StringTokenizer(br.readLine());
				for(int j = 0; j < N; j++) {
					board[i][j] = Integer.parseInt(st.nextToken());
					if (board[i][j] == 1 && !(i == 0 || i == N - 1 || j == 0 || j == N - 1)) {
						cores.add(new int[] {i, j});
					}
					
				}
			}
			
			backtracking(0, 0);
			
			System.out.println("#" + tc + " " + min_line);
		}
	}
	
	public static boolean write(int num, int dir) {
		int nx = cores.get(num)[0];
		int ny = cores.get(num)[1];
		
		while(true) {
			nx += dx[dir];
			ny += dy[dir];
			if (nx < 0 || nx >= N || ny < 0 || ny >= N) return true;
			if (board[nx][ny] == 1 || (board[nx][ny] != 0 && board[nx][ny] != num + 2)) return false;
			line_cnt++;
			board[nx][ny] = num + 2;
		}
	}
	
	public static void erase(int num, int dir) {
		int nx = cores.get(num)[0];
		int ny = cores.get(num)[1];
		
		while(true) {
			nx += dx[dir];
			ny += dy[dir];
			if (nx < 0 || nx >= N || ny < 0 || ny >= N) return;
			if (board[nx][ny] == 1 || board[nx][ny] != num + 2) return;
			line_cnt--;
			board[nx][ny] = 0;
		}
	}
	
	public static void backtracking(int num, int cnt) {
		if (cnt == cores.size()) {
			if (max_cnt < core_cnt) {
				max_cnt = core_cnt;
				min_line = line_cnt;
			}
			else if (max_cnt == core_cnt) {
				if (min_line > line_cnt) {
					min_line = line_cnt;
				}
			}
			return;
		}
		
		for(int dir = 0; dir < 4; dir++) {
			if (dir == 4) {
				backtracking(num + 1, cnt + 1);
				continue;
			}
			if (write(num, dir)) {
				core_cnt++;
				backtracking(num + 1, cnt + 1);
				core_cnt--;
			}
			erase(num, dir);
		}
	}
}
