// 1만큼 차이가 나는 곳을 찾으면 X만큼 직접 가보면서 높이가 같은지 확인하면 됨
// 내 풀이보다 더 직관적이라 생각됨

import java.util.*;
import java.io.*;

class Solution {
	static int T, N, X, ans;
	static int[][] board;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;

		int T = Integer.parseInt(br.readLine());
		for (int tc = 1; tc <= T; tc++) {
			st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			X = Integer.parseInt(st.nextToken());
			board = new int[N][N];
			ans = 0;
			
			for(int i = 0; i < N; i++) {
				st = new StringTokenizer(br.readLine().trim());
				for(int j = 0; j < N; j++) {
					board[i][j] = Integer.parseInt(st.nextToken());
				}
			}
			
			for(int i = 0; i < N; i++) {
				int start = 0, end = 1;
				int cnt = 1, down_cnt = 0;
				boolean isDo = true;
				while(end < N) {
					if (board[i][start] == board[i][end] && down_cnt == 0) {
						cnt++;
						end++;
					}
					else {
						if (board[i][start] + 1 == board[i][end] && down_cnt == 0) {
							if (cnt >= X) {
								cnt = 1;
								start = end++;
							}
							else {
								isDo = false;
								break;
							}
						}
						else if (board[i][start] == board[i][end] + 1) {
							if (++down_cnt >= X) {
								down_cnt = 0;
								cnt = 1;
								start = end;
							}
							end++;
							if (end < N && board[i][start] == board[i][end]) cnt--;
						}
						else {
							isDo = false;
							break;
						}
					}
				}
				
				if(isDo && down_cnt == 0) ans++;
			}
			
			for(int j = 0; j < N; j++) {
				int start = 0, end = 1;
				int cnt = 1, down_cnt = 0;
				boolean isDo = true;
				while(end < N) {
					if (board[start][j] == board[end][j] && down_cnt == 0) {
						cnt++;
						end++;
					}
					else {
						if (board[start][j] + 1 == board[end][j] && down_cnt == 0) {
							if (cnt >= X) {
								cnt = 1;
								start = end++;
							}
							else {
								isDo = false;
								break;
							}
						}
						else if (board[start][j] == board[end][j] + 1) {
							if (++down_cnt >= X) {
								down_cnt = 0;
								cnt = 1;
								start = end;
							}
							end++;
							if (end < N && board[start][j] == board[end][j]) cnt--;
						}
						else {
							isDo = false;
							break;
						}
					}
				}
				
				if(isDo && down_cnt == 0) ans++;
			}
			
			System.out.println("#" + tc + " " + ans);	
		}
	}
	
}