import java.io.*;
import java.util.*;

public class Main {
	static int N, M, ans;
	static int[][] board;
	static int[][] vis;
	static int[] dx = {1, 0, -1, 0};
	static int[] dy = {0, 1, 0, -1};
	static ArrayList<int[]> cctv;
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		ans = 100;
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		board = new int[N][M];
		vis = new int[N][M];
		cctv = new ArrayList<>();
		
		for(int i = 0; i < N; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j = 0; j < M; j++) {
				board[i][j] = Integer.parseInt(st.nextToken());
				vis[i][j] = board[i][j];
				if (board[i][j] != 0 && board[i][j] != 6) {
					cctv.add(new int[] {i, j});
				}
			}
		}
		
		for(int type = 0; type < (1<<(2*cctv.size())); type++) { // 4의 cctv 개수 만큼 경우의 수가 나옴
			int brute = type;
			for(int i = 0; i < cctv.size(); i++) {
				int dir = brute % 4; // 비트로 바라보면 11/10/00/01 이렇게 cctv가 4개라고 하면 % 4는 뒤에 첫번째 cctv 방향이 나온다.
				brute /= 4; // 다음 cctv 방향을 보기 위해서 11/10/00을 남기기 위해서 나눠준다.
				int x = cctv.get(i)[0];
				int y = cctv.get(i)[1];
				if (board[x][y] == 1) {
					watch(x, y, dir);
				}
				if (board[x][y] == 2) {
					watch(x, y, dir);
					watch(x, y, dir + 2);
				}
				if (board[x][y] == 3) {
					watch(x, y, dir);
					watch(x, y, dir+1);
					
				}
				if (board[x][y] == 4) {
					watch(x, y, dir);
					watch(x, y, dir+1);
					watch(x, y, dir+2);					
				}
				if (board[x][y] == 5) {
					watch(x, y, dir);
					watch(x, y, dir+1);
					watch(x, y, dir+2);
					watch(x, y, dir+3);
				}
			}
			ans = Math.min(ans, check());
		}
		
		System.out.println(ans);
	}
	
	public static int check() {
		int cnt = 0;
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < M; j++) {
				if (vis[i][j] == 0) cnt++;
				vis[i][j] = board[i][j];
			}
		}
		return cnt;
	}
	
	public static void watch(int x, int y, int dir) {
		dir %= 4;
		while(true) {
			x += dx[dir];
			y += dy[dir];
			if (x < 0 || x >= N || y < 0 || y >= M) return;
			if (board[x][y] == 6) return;
			vis[x][y] = 1;
		}
	}
}
