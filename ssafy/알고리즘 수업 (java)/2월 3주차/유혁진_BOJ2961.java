import java.io.*;
import java.util.*;

public class Main {
	static boolean[] cook;
	static int[][] info;
	static int N;
	static int result = Integer.MAX_VALUE;
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		
		N = Integer.parseInt(br.readLine());
		cook = new boolean[N];
		info = new int[N][2];
		for(int i = 0; i < N; i++) {
			st = new StringTokenizer(br.readLine());
			int S = Integer.parseInt(st.nextToken());
			int B = Integer.parseInt(st.nextToken());
			info[i][0] = S;
			info[i][1] = B;
		}
		
		subset(0);
		
		System.out.println(result);
		
	}
	
	public static void subset(int cnt) {
		if (cnt == N) {
			boolean isUse = false;
			int S = 1;
			int B = 0;
			for(int i = 0; i < N; i++) {
				if (cook[i]) {
					isUse = true;
					S *= info[i][0];
					B += info[i][1];
				}
			}
			if (isUse) {
				result = Math.min(result, Math.abs(S - B));
			}
			return;
		}
		
		cook[cnt] = true;
		subset(cnt + 1);
		cook[cnt] = false;
		subset(cnt + 1);
	}
}