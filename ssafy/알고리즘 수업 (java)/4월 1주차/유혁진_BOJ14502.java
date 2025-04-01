import java.io.*;
import java.util.*;

public class Main {
	static int N, M, safe, ans;
	static int[][] board;
	static int[] select;
	static ArrayList<int[]> blank;
	static ArrayList<int[]> virus;
	
	static int[] dx = {1, 0, -1, 0};
	static int[] dy = {0, 1, 0, -1};
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		safe = 0;
		ans = 0;
		select = new int[3];
		board = new int[N][M];
		virus = new ArrayList<>();
		blank = new ArrayList<>();
		
		for(int i = 0; i < N; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j = 0; j < M; j++) {
				board[i][j] = Integer.parseInt(st.nextToken());
				if (board[i][j] == 2) virus.add(new int[] {i, j});
				if (board[i][j] == 0) {
					blank.add(new int[] {i, j});
					safe++;
				}
			}
		}

		combination(0, 0);
		
		System.out.println(ans);
	}
	
	public static void combination(int num, int cnt) {
		if (cnt == 3) {
			for(int i = 0; i < 3; i++) {
				board[blank.get(select[i])[0]][blank.get(select[i])[1]] = 1;
			}
			
			ans = Math.max(ans, bfs());
			
			for(int i = 0; i < 3; i++) {
				board[blank.get(select[i])[0]][blank.get(select[i])[1]] = 0;
			}
			return;
		}
		
		for(int i = num; i < blank.size(); i++) {
			select[cnt] = i;
			combination(i + 1, cnt + 1);
		}
	}
	
	public static int bfs() {
		int res = safe - 3;
		Queue<int[]> q = new ArrayDeque<>();
		int[][] vis = new int[N][M];
		for(int i = 0; i < virus.size(); i++) {
			if (vis[virus.get(i)[0]][virus.get(i)[1]] == 1) continue;
			vis[virus.get(i)[0]][virus.get(i)[1]] = 1;
			q.offer(virus.get(i));	
			while(!q.isEmpty()) {
				int[] cur = q.poll();
				for(int dir = 0; dir < 4; dir++) {
					int nx = cur[0] + dx[dir];
					int ny = cur[1] + dy[dir];
					if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
					if (board[nx][ny] == 1 || vis[nx][ny] == 1) continue;
					vis[nx][ny] = 1;
					q.offer(new int[] {nx, ny});
					if (board[nx][ny] == 0) res--;
				}
			}
		}
		
		return res;
	}
	
}
