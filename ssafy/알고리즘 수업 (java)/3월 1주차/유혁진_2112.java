import java.io.*;
import java.util.*;

public class Solution {
	static int T;
	static int D;
	static int W;
	static int K;
	static int[][] film;
	static int[][] new_film;
	static boolean[] comb;
	static int ans;
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		int T = Integer.parseInt(br.readLine());
		
		for(int tc = 1; tc <= T; tc++) {
			st = new StringTokenizer(br.readLine());
			D = Integer.parseInt(st.nextToken());
			W = Integer.parseInt(st.nextToken());
			K = Integer.parseInt(st.nextToken());
			film = new int[D][W];
			new_film = new int[D][W];
			comb = new boolean[D];
			
			for(int i = 0; i < D; i++) {
				st = new StringTokenizer(br.readLine());
				for(int j = 0; j < W; j++) {
					film[i][j] = Integer.parseInt(st.nextToken());
				}
			}
		
			System.out.println("#" + tc);
		}
	}
	
	public static void combination(int n, int cnt, int max_cnt) {
		if (cnt == max_cnt) return;
		
		for(int i = n; i < D; i++) {
			comb[i] = true;
			combination(i + 1, cnt + 1, max_cnt);
			comb[i] = false;
		}
	}
	
	public static void ink() {
		
	}
	
	public static boolean test() {
		for(int j = 0; j < W; j++) {
			int cnt = 1;
			for(int i = 1; i < D; i++) {
				if (new_film[i][j] == new_film[i - 1][j]) {
					cnt++;
				}
				else {
					cnt = 1;
				}
				if (cnt == K) break;
			}
			if (cnt < K) return false;
		}
		
		return true;
	}

}
