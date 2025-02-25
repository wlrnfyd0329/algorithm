import java.io.*;
import java.util.*;

public class 유혁진_4008 {
	static int T;
	static int N;
	static int vmax;
	static int vmin;
	static int[] operator;
	static int[] num;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		T = Integer.parseInt(br.readLine());
		
		for(int tc = 1; tc <= T; tc++) {
			N = Integer.parseInt(br.readLine());
			vmax = -200_000_000;
			vmin = 200_000_000;
			operator = new int[4];
			num = new int[N];
			
			st = new StringTokenizer(br.readLine());
			for(int i = 0; i < 4; i++) {
				operator[i] = Integer.parseInt(st.nextToken());
			}

			st = new StringTokenizer(br.readLine());
			for(int i = 0; i < N; i++) {
				num[i] = Integer.parseInt(st.nextToken());
			}
			
			permutation(0, num[0]);
			
			System.out.println("#" + tc + " " + (vmax - vmin));
		}
	}
	
	public static void permutation(int depth, int cal) {
		if (depth == N - 1) {
			vmax = Math.max(vmax, cal);
			vmin = Math.min(vmin, cal);
			return;
		}
		
		for(int i = 0; i < 4; i++) {
			if (operator[i] == 0) continue;
			switch (i) {
				case 0:
					operator[i]--;
					permutation(depth + 1, cal + num[depth + 1]);
					operator[i]++;
					break;
				case 1:
					operator[i]--;
					permutation(depth + 1, cal - num[depth + 1]);
					operator[i]++;
					break;
				case 2:
					operator[i]--;
					permutation(depth + 1, cal * num[depth + 1]);
					operator[i]++;
					break;
				case 3:
					operator[i]--;
					permutation(depth + 1, cal / num[depth + 1]);
					operator[i]++;
					break;
			}
		}
	}
}