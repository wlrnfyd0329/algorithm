// 모든 섬이 연결되지 않을 수도 있다.

import java.util.*;
import java.io.*;

class Main {
	static int N, M, cnt;
	static int[] p;
	static ArrayList<int[]> bridge;
	static int[][] board;
	static int[][] vis;
	
	static int[] dx = {1, 0, -1, 0};
	static int[] dy = {0, 1, 0, -1};
	
	public static int find(int x) {
		if (p[x] < 0) return x;
		return p[x] = find(p[x]);
	}

	public static boolean uni(int u, int v) {
		u = find(u);
		v = find(v);
		if(u == v) return false;
		if (p[u] < p[v]) {
			int temp = u;
			u = v;
			v = temp;
		}
		if (p[u] == p[v]) p[v]--;
		p[u] = v;
		return true;
	}
	
	public static int kruskal() {
		int bridge_cnt = 0;
		int ans = 0;
		p = new int[cnt + 1];
		for(int i = 1; i <= cnt; i++) {
			p[i] = -1;
		}
		Collections.sort(bridge, (o1, o2) -> {
			return Integer.compare(o1[0], o2[0]);
		});
		
		for(int i = 0; i < bridge.size(); i++) {
			int[] cur = bridge.get(i);
			if (!uni(cur[1], cur[2])) continue;
			ans += cur[0];
			if (++bridge_cnt == cnt - 1) break;
		}
		
		return (ans == 0 || bridge_cnt != cnt - 1) ? -1 : ans;
	}
	
	public static void find_island() {
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < M; j++) {
				if (board[i][j] == 0 || vis[i][j] != 0) continue;
				Queue<int[]> q = new ArrayDeque<>();
				q.offer(new int[] {i, j});
				vis[i][j] = ++cnt;
				while(!q.isEmpty()) {
					int[] cur = q.poll();
					
					for(int dir = 0; dir < 4; dir++) {
						int nx = cur[0] + dx[dir];
						int ny = cur[1] + dy[dir];
						if(nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
						if (board[nx][ny] == 0 || vis[nx][ny] != 0) continue;
						vis[nx][ny] = cnt;
						q.offer(new int[] {nx, ny});
					}
				}
			}
		}
	}
	
	public static void find_bridge() {
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < M; j++) {
				if (vis[i][j] == 0) continue;
				for(int dir = 0; dir < 4; dir++) {
					int nx = i;
					int ny = j;
					int len = 0;
					while(true) {
						nx += dx[dir];
						ny += dy[dir];
						if (nx < 0 || nx >= N || ny < 0 || ny >= M) {
							len = -1;
							break;
						}
						if (vis[nx][ny] == 0) len++;
						else if (vis[nx][ny] == vis[i][j]) {
							len = -1;
							break;
						}
						else {
							break;
						};
					}
					if (len >= 2) {
						bridge.add(new int[] {len, vis[i][j], vis[nx][ny]});
					}
				}
			}
		}
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		board = new int[N][M];
		vis = new int[N][M];
		cnt = 0;
		bridge = new ArrayList<>();
		
		for(int i = 0; i < N; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j = 0; j < M; j++) {
				board[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		find_island();
		find_bridge();
		System.out.println(kruskal());
	}
}