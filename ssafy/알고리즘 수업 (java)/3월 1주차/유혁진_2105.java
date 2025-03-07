import java.io.*;
import java.util.*;

public class Solution {
	static int T;
	static int N;
	static int[][] board;
	static int[] dx = {1, 1, -1, -1};
	static int[] dy = {-1, 1, 1, -1};
	static int ans;
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		T = Integer.parseInt(br.readLine());
		
		for(int tc = 1; tc <= T; tc++) {
			N = Integer.parseInt(br.readLine());
			ans = 0;
			board = new int[N][N];
			
			for(int i = 0; i < N; i++) {
				st = new StringTokenizer(br.readLine());
				for(int j = 0; j < N; j++) {
					board[i][j] = Integer.parseInt(st.nextToken());
				}
			}
			
			find_dessert();
			
			System.out.println("#" + tc + " " + ans);
		}
	}
	
	public static void find_dessert() {
		int cnt = 0;
		
		for(int right = 1; right < N; right++) {
			for(int left = 1; left < N; left++) {
				for(int i = 0; i < N; i++) {
					for(int j = 0; j < N; j++) {
						HashSet<Integer> hs = new HashSet<Integer>();
						boolean isWrong = false;
						int nx = i;
						int ny = j;
						for(int r = 0; r < left; r++) {
							nx += dx[0];
							ny += dy[0];
							if (nx < 0 || nx >= N || ny < 0 || ny >= N || !hs.add(board[nx][ny])) {
								isWrong = true;
								break;
							}
						}
						if (isWrong) continue;
						for(int r = 0; r < right; r++) {
							nx += dx[1];
							ny += dy[1];
							if (nx < 0 || nx >= N || ny < 0 || ny >= N || !hs.add(board[nx][ny])) {
								isWrong = true;
								break;
							}
						}
						if (isWrong) continue;
						
						for(int r = 0; r < left; r++) {
							nx += dx[2];
							ny += dy[2];
							if (nx < 0 || nx >= N || ny < 0 || ny >= N || !hs.add(board[nx][ny])) {
								isWrong = true;
								break;
							}
						}
						if (isWrong) continue;
						for(int r = 0; r < right; r++) {
							nx += dx[3];
							ny += dy[3];
							if (nx < 0 || nx >= N || ny < 0 || ny >= N || !hs.add(board[nx][ny])) {
								isWrong = true;
								break;
							}
						}
						if (isWrong) continue;
						
						cnt = Math.max(hs.size(), cnt);
					}
				}
			}
		}
	    
		if (cnt == 0) {
			ans = -1;
		}
		else {
			ans = cnt;
		}
	}
}
