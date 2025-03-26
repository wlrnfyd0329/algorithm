import java.io.*;
import java.util.*;

public class Solution {
	static int ans;
	static int L;
	static int start;
	static ArrayList<HashSet<Integer>> call;
	static boolean[] vis;
	static int[] last_call;
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		int T = 10;
		for(int tc = 1; tc <= T; tc++) {
			st = new StringTokenizer(br.readLine());
			L = Integer.parseInt(st.nextToken());
			start = Integer.parseInt(st.nextToken());
			vis = new boolean[101];
			call = new ArrayList<>();
			for(int i = 0; i <= 100; i++) {
				call.add(new HashSet<>());
			}
			
			st = new StringTokenizer(br.readLine());
			for(int i = 0; i < L / 2; i++) {
				call.get(Integer.parseInt(st.nextToken())).add(Integer.parseInt(st.nextToken()));
			}
			
			Queue<int[]> q = new ArrayDeque<>();
			q.offer(new int[] {start, 1});
			vis[start] = true;
			last_call = new int[] {start, 1};
			while(!q.isEmpty()) {
				int[] cur = q.poll();
				if (last_call[1] < cur[1]) {
					last_call = cur;
				}
				else if (last_call[1] == cur[1]) {
					last_call[0] = Math.max(last_call[0], cur[0]);
				}
				for (int nxt : call.get(cur[0])) {
					if (vis[nxt]) continue;
					q.offer(new int[] {nxt, cur[1] + 1});
					vis[nxt] = true;
				}
			}
			
			System.out.println("#" + tc + " " + last_call[0]);
		}
	}

}
