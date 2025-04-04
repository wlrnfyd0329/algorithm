import java.util.*;
import java.io.*;

class Solution {
	static int N, M, ans;
	static ArrayList<ArrayList<Integer>> fgraph, bgraph;
	static boolean[] visit;
	static int[] cnt;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;


		int T = Integer.parseInt(br.readLine());
		for (int tc = 1; tc <= T; tc++) {
			N = Integer.parseInt(br.readLine());
			M = Integer.parseInt(br.readLine());
			ans = 0;	
			cnt = new int[N + 1];
			fgraph = new ArrayList<>();
			bgraph = new ArrayList<>();
			
			for(int i = 0; i <= N; i++) {
				fgraph.add(new ArrayList<>());
				bgraph.add(new ArrayList<>());
			}

			for(int i = 1; i <= M; i++) {
				st = new StringTokenizer(br.readLine());
				int a = Integer.parseInt(st.nextToken());
				int b = Integer.parseInt(st.nextToken());
				fgraph.get(a).add(b);
				bgraph.get(b).add(a);
			}
			
			for(int i = 1; i <= N; i++) {
				visit = new boolean[N + 1];
				visit[i] = true;
				cnt[i] = 1;
				fbfs(i);
				bbfs(i);
				if (cnt[i] == N) ans++;
			}
			
			System.out.println("#" + tc + " " + ans);	
		}
	}
	
	public static void fbfs(int num) {
		Queue<Integer> q = new ArrayDeque<>();
		q.offer(num);
		
		while(!q.isEmpty()) {
			int cur = q.poll();
			for(int nxt : fgraph.get(cur)) {
				if (visit[nxt]) continue;
				visit[nxt] = true;
				q.offer(nxt);
				cnt[num]++;
			}
		}
	}

	public static void bbfs(int num) {
		Queue<Integer> q = new ArrayDeque<>();
		q.offer(num);
		
		while(!q.isEmpty()) {
			int cur = q.poll();
			for(int nxt : bgraph.get(cur)) {
				if (visit[nxt]) continue;
				visit[nxt] = true;
				q.offer(nxt);
				cnt[num]++;
			}
		}
	}
}