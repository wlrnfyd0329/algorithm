import java.io.*;
import java.util.*;

public class Solution {
	static int T;
	static int N;
	static int M;
	static int K;
	static int[][] board;
	static int[] dx = {-1, 1, 0, 0};
	static int[] dy = {0, 0, -1, 1};
	static int ans;
	
	static class Micro {
		int x;
		int y;
		int cnt;
		int dir;
		boolean isAlive = true;
		
		Micro(int x, int y, int cnt, int dir) {
			this.x = x;
			this.y = y;
			this.cnt = cnt;
			this.dir = dir;
		}
	}
	static Micro[] micro;
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		T = Integer.parseInt(br.readLine());
		
		for(int tc = 1; tc <= T; tc++) {
			st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			M = Integer.parseInt(st.nextToken());
			K = Integer.parseInt(st.nextToken());
			ans = 0;
			board = new int[N][N];
			micro = new Micro[K + 1];
			
			for(int i = 1; i <= K; i++) {
				st = new StringTokenizer(br.readLine());
				int x = Integer.parseInt(st.nextToken());
				int y = Integer.parseInt(st.nextToken());
				int cnt = Integer.parseInt(st.nextToken());
				int dir = Integer.parseInt(st.nextToken());
				micro[i] = new Micro(x, y, cnt, dir - 1);
				board[x][y] = i;
			}
			
			for(int i = 0; i < M; i++) {

				move_micro();
			}
			
			for(int i = 1; i <= K; i++) {
				if (!micro[i].isAlive) continue;
				ans += micro[i].cnt;
			}
			
			System.out.println("#" + tc + " " + ans);
		}
	}
	
	public static void move_micro() {
		for(int i = 1; i <= K; i++) {
			if (!micro[i].isAlive) continue;
			board[micro[i].x][micro[i].y] = 0; 
			micro[i].x += dx[micro[i].dir];
			micro[i].y += dy[micro[i].dir];
			if (micro[i].x == 0 || micro[i].x == N - 1 || micro[i].y == 0 || micro[i].y == N - 1) {
				micro[i].cnt /= 2;
				if (micro[i].cnt == 0) {
					micro[i].isAlive = false;
				}
				if (micro[i].dir == 0) {
					micro[i].dir = 1;
				}
				else if (micro[i].dir == 1) {
					micro[i].dir = 0;
				}
				else if (micro[i].dir == 2) {
					micro[i].dir = 3;
				}
				else if (micro[i].dir == 3) {
					micro[i].dir = 2;
				}
			}
		}
		
		int[][] temp_board = new int[N][N];
		for(int i = 1; i <= K; i++) {
			if (!micro[i].isAlive) continue;
			if (board[micro[i].x][micro[i].y] != 0) {
				if (temp_board[micro[i].x][micro[i].y] > micro[i].cnt) {
					micro[board[micro[i].x][micro[i].y]].cnt += micro[i].cnt;
					micro[i].isAlive = false;
				}
				else {
					temp_board[micro[i].x][micro[i].y] = micro[i].cnt;
					micro[i].cnt += micro[board[micro[i].x][micro[i].y]].cnt;
					micro[board[micro[i].x][micro[i].y]].isAlive = false;
					board[micro[i].x][micro[i].y] = i;
				}
			}
			else {
				temp_board[micro[i].x][micro[i].y] = micro[i].cnt;
				board[micro[i].x][micro[i].y] = i;
			}
		}
	}
}
