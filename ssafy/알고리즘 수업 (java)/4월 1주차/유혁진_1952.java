import java.util.*;
import java.io.*;

class Solution {
	static int[] ticket;
	static int[] plan;
	static int[] price; // 해당 월까지의 최소 가격

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;


		int T = Integer.parseInt(br.readLine());
		for (int tc = 1; tc <= T; tc++) {
			ticket = new int[4];
			plan = new int[13];
			price = new int[13];
			
			st = new StringTokenizer(br.readLine());
			for(int i = 0; i < 4; i++) {
				ticket[i] = Integer.parseInt(st.nextToken());
			}
			
			st = new StringTokenizer(br.readLine());
			for(int i = 1; i <= 12; i++) {
				plan[i] = Integer.parseInt(st.nextToken());
			}

			price[1] = Math.min(plan[1] * ticket[0], ticket[1]);
			price[2] = Math.min(plan[2] * ticket[0], ticket[1]) + price[1];
			price[3] = Math.min(Math.min(plan[3] * ticket[0], ticket[1]) + price[2], ticket[2]);
			for(int i = 4; i <= 12; i++) {
				price[i] = Math.min(ticket[2] + price[i - 3], Math.min(plan[i] * ticket[0], ticket[1]) + price[i - 1]);
			}
			
			price[12] = Math.min(price[12], ticket[3]);
			System.out.println("#" + tc + " " + price[12]);
		}
	}
}