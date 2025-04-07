import java.util.*;
import java.io.*;

class Solution {
	static int N, K;
	static int[][] thing;
	static int[][] bag;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;


		int T = Integer.parseInt(br.readLine());
		for (int tc = 1; tc <= T; tc++) {
			st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			K = Integer.parseInt(st.nextToken());
			
			thing = new int[N + 1][2];
			bag = new int[N + 1][K + 1];
			
			for(int i = 1; i <= N; i++) {
				st = new StringTokenizer(br.readLine());
				thing[i][0] = Integer.parseInt(st.nextToken());
				thing[i][1] = Integer.parseInt(st.nextToken());
			}
			
			for(int i = 1; i <= N; i++) {
				for(int k = 0; k <= K; k++) {
					if(k < thing[i][0]) bag[i][k] = bag[i-1][k];
					else bag[i][k] = Math.max(bag[i - 1][k - thing[i][0]] + thing[i][1], bag[i-1][k]);
				}
			}
			
			System.out.println("#" + tc + " " + bag[N][K]);	
		}
	}
}