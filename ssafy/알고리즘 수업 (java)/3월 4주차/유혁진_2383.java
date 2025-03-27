import java.io.*;
import java.util.*;

public class Solution {
	static int N;
	static int[][] board;
	static ArrayList<int[]> stair;
	static PriorityQueue<Integer> stair1;
	static PriorityQueue<Integer> stair2;
	static ArrayList<int[]> human;
	static int time;
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		int T = Integer.parseInt(br.readLine());
		for(int tc = 1; tc <= T; tc++) {
			N = Integer.parseInt(br.readLine());
			board = new int[N + 1][N + 1];
			stair = new ArrayList<>();
			stair1 = new PriorityQueue<>();
			stair2 = new PriorityQueue<>();
			human = new ArrayList<>();
			time = Integer.MAX_VALUE;
			for(int i = 0; i < N; i++) {
				st = new StringTokenizer(br.readLine());
				for(int j = 0; j < N; j++) {
					board[i][j] = Integer.parseInt(st.nextToken());
					if (board[i][j] == 1) {
						human.add(new int[] {i, j});
					}
					if (board[i][j] > 1) {
						stair.add(new int[] {i, j});
					}
				}
			}
			
			for(int i = 0; i < (1<<human.size()); i++) {
				for(int j = 0; j < human.size(); j++) {
					if ((i & (1 << j)) == 0) stair1.offer(Math.abs(human.get(j)[0] - stair.get(0)[0]) + Math.abs(human.get(j)[1] - stair.get(0)[1]));
					else stair2.offer(Math.abs(human.get(j)[0] - stair.get(1)[0]) + Math.abs(human.get(j)[1] - stair.get(1)[1]));
				}
				time = Math.min(time, func());
			}
			
			System.out.println("#" + tc + " " + time);
		}
	}
	
	public static int func() {
		Queue<Integer> q = new ArrayDeque<>();
		int stair1_len = board[stair.get(0)[0]][stair.get(0)[1]];
		int stair1_time = 0;
		while(!stair1.isEmpty()) {
			if (q.size() < 3) {
				q.offer(stair1.poll() + stair1_len + 1);
			}
			else {
				if (q.peek() <= stair1.peek()) {
					q.poll();
					q.offer(stair1.poll() + stair1_len + 1);
				}
				else {
					stair1.poll();
					q.offer(q.poll() + stair1_len);
				}
			}
		}
		while(!q.isEmpty()) {
			stair1_time = Math.max(stair1_time, q.poll());
		}
		int stair2_len = board[stair.get(1)[0]][stair.get(1)[1]];
		int stair2_time = 0;
		while(!stair2.isEmpty()) {
			if (q.size() < 3) {
				q.offer(stair2.poll() + stair2_len + 1);
			}
			else {
				if (q.peek() <= stair2.peek()) {
					q.poll();
					q.offer(stair2.poll() + stair2_len + 1);
				}
				else {
					stair2.poll();
					q.offer(q.poll() + stair2_len);
				}
			}
		}
		while(!q.isEmpty()) {
			stair2_time = Math.max(stair2_time, q.poll());
		}
		return Math.max(stair1_time, stair2_time);
	}
	
}
