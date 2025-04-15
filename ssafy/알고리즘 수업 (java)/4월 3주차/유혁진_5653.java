import java.util.*;
import java.io.*;

class Solution {
	static int T, N, M, K;
	static PriorityQueue<Cell> cell;
	static Queue<Cell> q;
	static int[][] board;
	
	static int[] dx = {0, 0, -1, 1};
	static int[] dy = {1, -1, 0, 0};

	public static class Cell implements Comparable<Cell> {
		int x;
		int y;
		int pwr;
		int wait;
		int status; // 1 비활성, 2 활성, 3 죽음
		
		public Cell(int x, int y, int pwr) {
			this.x = x;
			this.y = y;
			this.pwr = pwr;
			this.wait = 0;
			this.status = 1;
		}
		
		@Override
		public int compareTo(Cell o) {
			return Integer.compare(o.pwr, pwr);
		}
		
		public void breeding() {
			if (status == 3) return;
			if (status == 2) {
				for(int dir = 0; dir < 4; dir++) {
					int nx = x + dx[dir];
					int ny = y + dy[dir];
					if (board[nx][ny] != 0) continue;
					board[nx][ny] = pwr;
					q.offer(new Cell(nx, ny, pwr));
				}
			}
			if (++wait == pwr) {
				wait = 0;
				if (++status == 3) return;
			}
			q.offer(this);
		}
	}

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;

		int T = Integer.parseInt(br.readLine());
		for (int tc = 1; tc <= T; tc++) {
			st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			M = Integer.parseInt(st.nextToken());
			K = Integer.parseInt(st.nextToken());
			cell = new PriorityQueue<>();
			q = new ArrayDeque<>();
			board = new int[N + 2 * K][M + 2 * K];
			
			for(int i = 0; i < N; i++) {
				st = new StringTokenizer(br.readLine());
				for(int j = 0; j < M; j++) {
					int num = Integer.parseInt(st.nextToken());
					if (num > 0) {
						cell.offer(new Cell(i + K, j + K, num));
						board[i + K][j + K] = num;
					}
				}
			}
			
			System.out.println("#" + tc + " " + simul());	
		}
	}
	
	public static int simul() {
		while(K-- != 0) {
			while(!cell.isEmpty()) {
				Cell cur = cell.poll();
				cur.breeding();
			}
			while(!q.isEmpty()) {
				cell.offer(q.poll());
			}
		}
		
		return cell.size();
	}
	
}