// 문제의 포인트는 각 cost에 얻을 수 있는 최대 메모리를 구하고
// 필요로 하는 메모리를 넘기는 순간의 cost가 정답이 되는 것이다
// knapsack dp가 항상 끝까지 가야하는 건 아니다

import java.io.*;
import java.util.*;

public class Main {
	static int N, M;
	static int[][] app;
	static int[][] phone;
	static int max_cost;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;

		st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		app = new int[N+1][2]; // [0] 메모리, [1] cost
		
		st = new StringTokenizer(br.readLine());
		for(int i = 1; i <= N; i++) {
			app[i][0] = Integer.parseInt(st.nextToken());
		}
		
		st = new StringTokenizer(br.readLine());
		for(int i = 1; i <= N; i++) {
			app[i][1] = Integer.parseInt(st.nextToken());
			max_cost += app[i][1];
		}
		
		phone = new int[N + 1][max_cost + 1];
		
		for(int i = 1; i <= N; i++) {
			for(int c = 0; c <= max_cost; c++) {
				if (c < app[i][1]) phone[i][c] = phone[i - 1][c];
				else phone[i][c] = Math.max(phone[i - 1][c - app[i][1]] + app[i][0], phone[i - 1][c]);
			}
		}
		
		for(int i = 0; i <= max_cost; i++) {
			if (phone[N][i] >= M) {
				System.out.println(i);
				break;
			}
		}
	}
}
