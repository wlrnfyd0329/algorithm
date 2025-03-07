import java.io.*;
import java.util.*;

public class Solution {
	static int T;
	static int V;
	static int E;
	static ArrayList<Integer>[] graph;
	static int[] indegree;
	static Queue<Integer> q;
	static ArrayList<Integer> ans;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		T = 10;
		
		for(int tc = 1; tc <= T; tc++) {
			st = new StringTokenizer(br.readLine());
			V = Integer.parseInt(st.nextToken());
			E = Integer.parseInt(st.nextToken());
			graph = new ArrayList[V + 1];
			indegree = new int[V + 1];
			q = new ArrayDeque<Integer>();
			ans = new ArrayList<>();
			
			for(int i = 0; i <= V; i++) {
				graph[i] = new ArrayList<>();
			}
			
			st = new StringTokenizer(br.readLine());
			for(int i = 1; i <= E; i++) {
				int s = Integer.parseInt(st.nextToken());
				int e = Integer.parseInt(st.nextToken());
				graph[s].add(e);
				indegree[e]++;
			}
			
			for(int i = 1; i <= V; i++) {
				if (indegree[i] == 0) {
					q.offer(i);
				}
			}
			
			while(!q.isEmpty()) {
				int cur = q.poll();
				ans.add(cur);
				for(int next : graph[cur]) {
					indegree[next]--;
					if (indegree[next] == 0) {
						q.offer(next);
					}
				}
			}
			
			System.out.print("#" + tc + " ");
			for(int num : ans) {
				System.out.print(num + " ");
			}
			System.out.println();
		}
	}
	
	
}
