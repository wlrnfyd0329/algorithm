import java.io.*;
import java.util.*;

public class 유혁진_4012 {
	static int T;
	static int N;
	static int result;
	static int[][] arr;
	static int[] food1;
	static int[] food2;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		T = Integer.parseInt(br.readLine());
		
		for(int tc = 1; tc <= T; tc++) {
			N = Integer.parseInt(br.readLine());
			arr = new int[N][N];
			food1 = new int[N/2];
			food2 = new int[N/2];
			result = 100_000;
			
			for(int i = 0; i < N; i++) {
				st = new StringTokenizer(br.readLine());
				for(int j = 0; j < N; j++) {
					arr[i][j] = Integer.parseInt(st.nextToken());
				}
			}
			
			chooseFood(0, 0, 0);
			
			System.out.println("#" + tc + " " + result);
		}
	}
	
	public static void chooseFood(int n, int cnt, int res) {
		if (cnt == N / 2) {
			int food1_index = 0;
			int food2_index = 0;
			for(int i = 0; i < N; i++) {
				if ((res & (1 << i)) > 0) {
					food1[food1_index++] = i;
				}
				else {
					food2[food2_index++] = i;
				}
			}
			
			int synergy1 = 0;
			int synergy2 = 0;
			
			for(int i = 0; i < N / 2; i++) {
				for(int j = 0; j < N / 2; j++) {
					synergy1 += arr[food1[i]][food1[j]];
					synergy2 += arr[food2[i]][food2[j]];
				}
			}
			
			result = Math.min(result, Math.abs(synergy2 - synergy1));
			return;
		}
		
		for(int i = n; i < N; i++) {
			chooseFood(i + 1, cnt + 1, res | (1 << i));
		}
	}
}