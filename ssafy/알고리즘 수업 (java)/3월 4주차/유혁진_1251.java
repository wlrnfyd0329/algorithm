import java.io.*;
import java.util.*;

public class Solution {
	public static class Island {
		double dist;
		int st;
		int en;
		
		public Island(double dist, int st, int en) {
			this.dist = dist;
			this.st = st;
			this.en = en;
		}
	}
	
	static int N;
	static int[][] position;
	static ArrayList<Island> island;
	static double E;
	static int cnt;
	static double ans;
	static int[] p;
	
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		int T = Integer.parseInt(br.readLine());
		for(int tc = 1; tc <= T; tc++) {
			st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			position = new int[N + 1][2];
			island = new ArrayList<>();
			cnt = 0;
			ans = 0;
			p = new int[N + 1];
			
			st = new StringTokenizer(br.readLine());
			for(int i = 1; i <= N; i++) {
				p[i] = -1;
				position[i][0] = Integer.parseInt(st.nextToken());
				
			}
			
			st = new StringTokenizer(br.readLine());
			for(int i = 1; i <= N; i++) {
				position[i][1] = Integer.parseInt(st.nextToken());
				
			}
			E = Double.parseDouble(br.readLine());
			
			for(int i = 1; i <= N; i++) {
				for(int j = i + 1; j <= N; j++) {
					island.add(new Island(Math.pow(position[i][0] - position[j][0], 2) + Math.pow(position[i][1] - position[j][1], 2), i, j));
				}
			}
			
			Collections.sort(island, (a,b) -> Double.compare(a.dist, b.dist));
						
			for(int i = 0; i < island.size(); i++) {
				if (!uni(island.get(i).st, island.get(i).en)) continue;
				cnt++;
				ans += island.get(i).dist;
				if (cnt == N - 1) break;
			}
			
			System.out.println("#" + tc + " " + Math.round(ans * E));
		}
	}
	
	public static int find(int x) {
		if (p[x] < 0) {
			return x;
		}
		return p[x] = find(p[x]);
	}
	
	public static boolean uni(int u, int v) {
		u = find(u);
		v = find(v);
		if (u == v) return false;
		if (p[u] < p[v]) {
			int temp = u;
			u = v;
			v = temp;
		}
		if (p[u] == p[v]) p[v]--;
		p[u] = v;
		return true;
	}
}
