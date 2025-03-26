import java.io.*;
import java.util.*;

public class Solution {
	static int N;
	static int M;
	static int[] p;
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		int T = Integer.parseInt(br.readLine());
		for(int tc = 1; tc <= T; tc++) {
			st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			M = Integer.parseInt(st.nextToken());
			p = new int[N+1];
			for(int i = 1; i <= N; i++) {
				p[i] = -1;
			}
			for(int i = 0; i < M; i++) {
				st = new StringTokenizer(br.readLine());
				int u = Integer.parseInt(st.nextToken());
				int v = Integer.parseInt(st.nextToken());
				uni(u, v);
			}			
			
			System.out.println("#" + tc + " " + N);
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
		N--;
		return true;
	}

}
