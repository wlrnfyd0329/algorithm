import java.io.*;
import java.util.*;

public class 유혁진_4796 {
	static int N;
	static int[] height;
	public static void main(String[] args) throws IOException {
		Scanner sc = new Scanner(System.in);
		int T = sc.nextInt();
		
		for(int tc = 1; tc <= T; tc++) {
			N = sc.nextInt();
			int[] height = new int[N];
			int res = 0;
			int up_cnt = 0;
			int down_cnt = 0;
			boolean find = false;

			height[0] = sc.nextInt();
			for(int i = 1; i < N; i++) {
				height[i] = sc.nextInt();
				if (height[i-1] < height[i]) {
					if (find) {
						res += up_cnt * down_cnt;
						find = false;
						up_cnt = 1;
						down_cnt = 0;
					}
					else {
						up_cnt++;
					}
				}
				else {
					down_cnt++;
					if(!find) {
						find = true;
					}
				}
			}
			
			res += up_cnt * down_cnt;
			
			System.out.println("#" + tc + " " + res);
		}
		sc.close();
	}

}