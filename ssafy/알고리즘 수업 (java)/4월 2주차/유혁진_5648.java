// 승구 코드...

import java.io.*;
import java.util.*;

public class Solution {
	
	static class C implements Comparable<C>{
		int x, y;
		double time;
		C(int x, int y, double time){
			this.x = x;
			this.y = y;
			this.time = time;
		}
		
		@Override
		public int compareTo(C o) {
			if(this.time < o.time)
				return -1;
			else return 1;
		}
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		StringTokenizer st = new StringTokenizer(br.readLine());
		int T = Integer.valueOf(st.nextToken());
		int[] dx = {0, 0, -1, 1};
		int[] dy = {1, -1, 0, 0};

		for (int test = 1; test <= T; test++) {
			st = new StringTokenizer(br.readLine());
			int n = Integer.valueOf(st.nextToken());
			
			int[] x = new int[n];
			int[] y = new int[n];
			int[] dir = new int[n];
			int[] pow = new int [n];
			boolean[] killed = new boolean[n];
			
			
			for(int i = 0; i < n; i++) {
				st = new StringTokenizer(br.readLine());
				x[i] = Integer.valueOf(st.nextToken());
				y[i] = Integer.valueOf(st.nextToken());
				dir[i] = Integer.valueOf(st.nextToken());
				pow[i] = Integer.valueOf(st.nextToken());
			}
			
			PriorityQueue<C> pq = new PriorityQueue<>();
			for(int i = 0; i < n; i++) {
				for(int j = i + 1; j < n; j++) {
					if(x[i] == x[j]) {
						if(y[i] < y[j] && dir[i] == 0 && dir[j] == 1)
							pq.add(new C(i, j, ((double)y[j] - y[i] ) / 2));
						else if(y[j] < y[i] && dir[j] == 0 && dir[i] == 1)
							pq.add(new C(i, j, ((double)y[i] - y[j] ) / 2));
					}else if(y[i] == y[j]) {
						if(x[i] < x[j] && dir[i] == 3 && dir[j] == 2)
							pq.add(new C(i, j, ((double)x[j] - x[i] ) / 2));
						else if(x[j] < x[i] && dir[j] == 3 && dir[i] == 2)
							pq.add(new C(i, j, ((double)x[i] - x[j] ) / 2));
					}else {
						if(((dir[i] ^ dir[j]) & 2) == 2) {
							if(Math.abs(x[i] - x[j]) != Math.abs(y[i] - y[j]))
								continue;
							
							if((x[j] - x[i]) * dx[dir[i]] + (y[j] - y[i]) * dy[dir[i]] > 0) {
								if((x[i] - x[j]) * dx[dir[j]] + (y[i] - y[j]) * dy[dir[j]] > 0) {
									pq.add(new C(i, j, Math.abs(x[i] - x[j])));
								}
							}
						}
					}
				}
			}
			
			int res = 0;
			while(!pq.isEmpty()) {
				double t = pq.peek().time;
				Set<Integer> set = new HashSet<>();
				while(!pq.isEmpty() && pq.peek().time == t) {
					C now = pq.poll();
					if(killed[now.x] || killed[now.y]) continue;
					set.add(now.x);
					set.add(now.y);
				}
				
				for(int tmp : set) {
					killed[tmp] = true;
					res+= pow[tmp];
				}
			}
			
			
			
			bw.write("#" + test + " " + res + "\n");
		}

		br.close();
		bw.flush();
		bw.close();
	}
}
