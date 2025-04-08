import java.util.*;
import java.io.*;

class Solution {
	static int T, N, max_ans, ans;
	static int[][] board;
	static HashMap<Integer, ArrayList<int[]>> holls;
	static int now_x;
	static int now_y;
	static int now_dir;
	
	static int[] dx = {-1, 0, 1, 0}; // 상 좌 하 우
	static int[] dy = {0, -1, 0, 1};

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;

		int T = Integer.parseInt(br.readLine().trim());
		for (int tc = 1; tc <= T; tc++) {
			N = Integer.parseInt(br.readLine().trim());
			max_ans = 0;
			board = new int[N][N];
			holls = new HashMap<>();
			
			for(int i = 0; i < N; i++) {
				st = new StringTokenizer(br.readLine().trim());
				for(int j = 0; j < N; j++) {
					board[i][j] = Integer.parseInt(st.nextToken());
					if (board[i][j] >= 6) {
						if (holls.containsKey(board[i][j])) {
							holls.get(board[i][j]).add(new int[] {i, j});
						}
						else {
							holls.put(board[i][j], new ArrayList<>());
							holls.get(board[i][j]).add(new int[] {i, j});
						}
					}
				}
			}
			
			for(int i = 0; i < N; i++) {
				for(int j = 0; j < N; j++) {
					if (board[i][j] != 0) continue;
					for(int k = 0; k < 4; k++) {
						now_x = i;
						now_y = j;
						now_dir = k;
						ans = 0;
						simulation();
						max_ans = Math.max(max_ans, ans);
					}
				}
			}
			
			System.out.println("#" + tc + " " + max_ans);	
		}
	}
	
	public static void simulation() {
		int nx = now_x;
		int ny = now_y;
		while(true) {
			nx += dx[now_dir];
			ny += dy[now_dir];
			if (nx < 0 || nx >= N || ny < 0 || ny >= N) {
				now_dir ^= 2;
				ans++;
				continue;
			}
			if ((nx == now_x && ny == now_y) || board[nx][ny] == -1) break; 
			if (board[nx][ny] == 1) block1();
			else if (board[nx][ny] == 2) block2();
			else if (board[nx][ny] == 3) block3();
			else if (board[nx][ny] == 4) block4();
			else if (board[nx][ny] == 5) block5();
			else if (board[nx][ny] >= 6) {
				int[] cur = holl(nx, ny);
				nx = cur[0];
				ny = cur[1];
			}
		}
	}
	
	public static void block1() {
		ans++;
		if (now_dir == 1 || now_dir == 2) {
			now_dir ^= 1;
		}
		else {
			now_dir ^= 2;
		}
	}
	
	public static void block2() {
		ans++;
		if (now_dir == 0 || now_dir == 1) {
			now_dir ^= 3;
		}
		else {
			now_dir ^= 2;
		}
	}

	public static void block3() {
		ans++;
		if (now_dir == 0 || now_dir == 3) {
			now_dir ^= 1;
		}
		else {
			now_dir ^= 2;
		}
	}

	public static void block4() {
		ans++;
		if (now_dir == 2 || now_dir == 3) {
			now_dir ^= 3;
		}
		else {
			now_dir ^= 2;
		}
	}

	public static void block5() {
		ans++;
		now_dir ^= 2;
	}
	
	public static int[] holl(int x, int y) {
		for(int i = 0; i < 2; i++) {
			int[] cur = holls.get(board[x][y]).get(i);
			if (cur[0] != x || cur[1] != y) {
				return cur;
			}
		}
		return null;
	}
}