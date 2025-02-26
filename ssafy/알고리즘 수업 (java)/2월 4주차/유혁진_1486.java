import java.io.*;
import java.util.*;

public class 유혁진_1486 {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		int T = Integer.parseInt(br.readLine());
		
		for(int tc = 1; tc <= T; tc++) {
			st = new StringTokenizer(br.readLine());
			int N = Integer.parseInt(st.nextToken());
			int B = Integer.parseInt(st.nextToken());
			int[] height = new int[N];
			int minDiff = 200_000;

			st = new StringTokenizer(br.readLine());
			for(int i = 0; i < N; i++) {
				height[i] = Integer.parseInt(st.nextToken());
			}
			
			for(int i = 0; i < (1 << N); i++) {
				int calHeight = 0;
				for(int j = 0; j < N; j++) {
					if ((i & (1 << j)) > 0) {
						calHeight += height[j];
					}
				}
				
				if (B <= calHeight) {
					minDiff = Math.min(minDiff, calHeight - B);
				}
			}
			
			System.out.println("#" + tc + " " + minDiff);
		}
	}

}