import java.io.*;
import java.util.*;

public class 유혁진_3421 {
	static int result;
	static int N;
	static int M;
	static boolean[] hamburger;
	static boolean[][] hate;
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		
		int T = Integer.parseInt(br.readLine());
		for(int tc = 1; tc <= T; tc++) {
			st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			M = Integer.parseInt(st.nextToken());
			result = 0;
			hamburger = new boolean[N+1];
			hate = new boolean[N+1][N+1];
			
			for(int i = 0; i < M; i++) {
				st = new StringTokenizer(br.readLine());
				int a = Integer.parseInt(st.nextToken());
				int b = Integer.parseInt(st.nextToken());
				hate[a][b] = true;
				hate[b][a] = true;
			}
			
			subset(1);
			
			System.out.println("#" + tc + " " + result);
		}
		
	}
	
	public static void subset(int cnt) {
		if (cnt == N + 1) {
			result++;
			return;
		}
		boolean isHate = false;
		
		for(int i = 1; i < cnt; i++) {
			if(hamburger[i] && hate[i][cnt]) {
				isHate = true;
				break;
			}
		}
		
		if (!isHate) {
			hamburger[cnt] = true;
			subset(cnt + 1);
		}
		hamburger[cnt] = false;
		subset(cnt + 1);
	}
}