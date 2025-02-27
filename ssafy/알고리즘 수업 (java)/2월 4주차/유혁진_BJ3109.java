import java.io.*;
import java.util.*;

public class Main {
	static int res = 0;
	static int R;
	static int C;
	static int[][] map;
	static int[][] vis;
	static int[] dx = {-1, 0, 1};
	static int[] dy = {1, 1, 1};
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		R = Integer.parseInt(st.nextToken());
		C = Integer.parseInt(st.nextToken());
		map = new int[R][C];
		vis = new int[R][C];
		
		for(int i = 0; i < R; i++) {
			String s = br.readLine();
			for(int j = 0; j < C; j++) {
				if (s.charAt(j) == '.') {
					map[i][j] = 0;
				}
				else {
					map[i][j] = -1;
				}
			}
		}
		
		for(int i = 0; i < R; i++) {
			pipe(i, 0);
		}
		
		System.out.println(res);
	}
	
	public static boolean pipe(int x, int y) {
		if (y == C - 1) {
			res++;
			return true;
		}
		
		for(int i = 0; i < 3; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx < 0 || nx >= R) continue;
			if (map[nx][ny] == -1 || vis[nx][ny] > 0) continue;
			vis[nx][ny] = 1;
			if (pipe(nx, ny)) {
				return true;
			}
		}
		
		return false;
	}

}