import java.io.*;
import java.util.*;

public class Solution {
	static int N;
	static int M;
	static int C;
	static int ans;
	static int[][] board;
	static int[][] honey;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		int T = Integer.parseInt(br.readLine());
		for(int tc = 1; tc <= T; tc++) {
			st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			M = Integer.parseInt(st.nextToken());
			C = Integer.parseInt(st.nextToken());
			board = new int[N][N];
			honey = new int[N][N];
			ans = 0;
			for(int i = 0; i < N; i++) {
				st = new StringTokenizer(br.readLine());
				for(int j = 0; j < N; j++) {
					board[i][j] = Integer.parseInt(st.nextToken());
				}
			}
			
			for(int i = 0; i < N; i++) {
				for(int j = 0; j <= N - M; j++) {
					honey[i][j] = func(i, j);
				}
			}
			
			for(int i = 0; i < N; i++) {
				for(int j = 0; j <= N - M; j++) {
					for(int r = 0; r < N; r++) {
						if (i == r) {
							for(int c = j + M; c <= N - M; c++) {
								ans = Math.max(ans, honey[i][j] + honey[r][c]);
							}
						}
						else {
							for(int c = 0; c <= N - M; c++) {
								ans = Math.max(ans, honey[i][j] + honey[r][c]);
							}
						}
						
					}
				}
			}

			System.out.println("#" + tc + " " + ans);
		}
	}
	
	public static int func(int r, int c) {
		int max_pow_sum = 0;
		for(int i = ((1 << M) - 1); i >= 1; i--) {
			int sum = 0;
			int pow_sum = 0;
			for(int j = 0; j < M; j++) {
				if ((i & (1 << j)) > 0) {
					sum += board[r][c + j];
					pow_sum += Math.pow(board[r][c + j], 2);
				}
			}
			if (sum > C) continue;
			if (max_pow_sum < pow_sum) {
				max_pow_sum = pow_sum;
			}
		}
		return max_pow_sum;
	}
}
