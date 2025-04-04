
import java.util.*;
import java.io.*;

class Solution {
	static int N, M, K, A, B, ans;
	static int[] tReception;
	static int[] tRepair;
	static int[][] reception;
	static int[][] repair;
	static PriorityQueue<int[]> arrive_reception;
	static PriorityQueue<int[]> arrive_repair;
	static int[][] record;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;


		int T = Integer.parseInt(br.readLine());
		for (int tc = 1; tc <= T; tc++) {
			st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			M = Integer.parseInt(st.nextToken());
			K = Integer.parseInt(st.nextToken());
			A = Integer.parseInt(st.nextToken());
			B = Integer.parseInt(st.nextToken());
			ans = 0;
			tReception = new int[N+1];
			tRepair = new int[M+1];
			reception = new int[N+1][2];
			repair = new int[M+1][2];
			arrive_reception = new PriorityQueue<>((o1, o2) -> {
				if (o1[0] == o2[0]) return o1[1] > o2[1] ? 1 : -1;
				return o1[0] > o2[0] ? 1 : -1;
			});
			arrive_repair = new PriorityQueue<>((o1, o2) -> {
				if (o1[0] == o2[0]) return o1[1] > o2[1] ? 1 : -1;
				return o1[0] > o2[0] ? 1 : -1;
			});
			record = new int[K+1][2];
			
			st = new StringTokenizer(br.readLine());
			for(int i = 1; i <= N; i++) {
				tReception[i] = Integer.parseInt(st.nextToken());
			}
			
			st = new StringTokenizer(br.readLine());
			for(int i = 1; i <= M; i++) {
				tRepair[i] = Integer.parseInt(st.nextToken());
			}
			
			st = new StringTokenizer(br.readLine());
			for(int i = 1; i <= K; i++) {
				arrive_reception.offer(new int[] {Integer.parseInt(st.nextToken()), i});
			}
			
			visit_reception();
			visit_repair();
			check();
			
			if (ans == 0) System.out.println("#" + tc + " -1");
			else System.out.println("#" + tc + " " + ans);	
		}
	}
	
	public static void visit_reception() {
		int idx = 0, min_time;
		while(!arrive_reception.isEmpty()) {
			int[] cur = arrive_reception.peek();
			min_time = Integer.MAX_VALUE;
			
			int status = 0;
			
			for(int i = 1; i <= N; i++) {
				if (reception[i][1] == 0) {
					status = 1;
					reception[i][0] = cur[0] + tReception[i];
					reception[i][1] = cur[1];
					record[cur[1]][0] = i;
					arrive_reception.poll();
					break;
				}
				if (cur[0] >= reception[i][0]) {
					status = 2;
					arrive_repair.offer(new int[] {reception[i][0], i, reception[i][1]});
					reception[i][0] = cur[0] + tReception[i];
					reception[i][1] = cur[1];
					record[cur[1]][0] = i;
					arrive_reception.poll();
					break;
				}
				if (min_time > reception[i][0]) {
					min_time = reception[i][0];
					idx = i;
				}
			}
			
			if (status == 0) {
				arrive_repair.offer(new int[] {reception[idx][0], idx, reception[idx][1]});
				reception[idx][0] = min_time + tReception[idx];
				reception[idx][1] = cur[1];
				record[cur[1]][0] = idx;
				arrive_reception.poll();
			}
			
			if (status == 2) {
				for(int i = 1; i <= N; i++) {
					if (reception[i][1] != 0 && reception[i][0] <= cur[0]) {
						arrive_repair.offer(new int[] {reception[i][0], i, reception[i][1]});
						reception[i][1] = 0;
					}
				}
			}
		}
		
		for(int i = 1; i <= N; i++) {
			if (reception[i][1] != 0) {
				arrive_repair.offer(new int[] {reception[i][0], i, reception[i][1]});
				reception[i][1] = 0;
			}
		}
	}
	
	public static void visit_repair() {
		int idx = 0, min_time;
		while(!arrive_repair.isEmpty()) {
			int[] cur = arrive_repair.peek();
			min_time = Integer.MAX_VALUE;
			
			int status = 0;
			
			for(int i = 1; i <= M; i++) {
				if (repair[i][1] == 0) {
					status = 1;
					repair[i][0] = cur[0] + tRepair[i];
					repair[i][1] = cur[2];
					record[cur[2]][1] = i;
					arrive_repair.poll();
					break;
				}
				if (cur[0] >= repair[i][0]) {
					status = 2;
					repair[i][0] = cur[0] + tRepair[i];
					repair[i][1] = cur[2];
					record[cur[2]][1] = i;
					arrive_repair.poll();
					break;
				}
				if (min_time > repair[i][0]) {
					min_time = repair[i][0];
					idx = i;
				}
			}
			
			if (status == 0) {
				repair[idx][0] = min_time + tRepair[idx];
				repair[idx][1] = cur[2];
				record[cur[2]][1] = idx;
				arrive_repair.poll();
			}
			
			if (status == 2) {
				for(int i = 1; i <= M; i++) {
					if (repair[i][1] != 0 && repair[i][0] <= cur[0]) {
						repair[i][1] = 0;
					}
				}
			}
		}
	}
	
	public static void check() {
		for(int i = 1; i <= K; i++) {
			if (record[i][0] == A && record[i][1] == B) ans += i;
		}
	}
}