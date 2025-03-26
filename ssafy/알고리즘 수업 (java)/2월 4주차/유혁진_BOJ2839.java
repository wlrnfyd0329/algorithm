import java.io.*;
import java.util.*;

public class Main {
	static int N;
	static int[] height;
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		int[][] arr = new int[N + 1][2];
		
		for(int i = 0; i <= N; i++) {
			arr[i][0] = 2000;
			arr[i][1] = 1000;
		}
		
		for(int three = 0; three <= N / 3; three++) {
			for(int five = 0; five <= N / 5; five++) {
				int num = 3 * three + 5 * five;
				if (num <= N) {
					if (three + five < arr[num][0] + arr[num][1]) {
						arr[num][0] = three;
						arr[num][1] = five;
					}
				}
			}
		}
			
		if (arr[N][0] + arr[N][1] == 3000) {
			System.out.println(-1);
		}
		else {
			System.out.println(arr[N][0] + arr[N][1]);
		}
	}

}