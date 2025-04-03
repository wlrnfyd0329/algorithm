import java.io.*;
import java.util.*;

public class Main {
	static int X, ans;
	static int[] dp;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		//StringTokenizer st = new StringTokenizer(br.readLine());

		X = Integer.parseInt(br.readLine());
		
//		dp1(); // 144ms
//		dp2(); // 124ms
		dp3(); // 120ms
//		dp4(); // 188ms
//		dp5(); // 시간 초과 (중복이 너무 많음)
	}
	
	public static void dp1() {
		dp = new int[4 * X];
		
		for(int i = 1; i <= X; i++) {
			dp[i] = Integer.MAX_VALUE;
		}
		
		dp[1] = 0;
		for(int i = 1; i <= X; i++) {
			dp[i * 3] = Math.min(dp[i * 3],	dp[i] + 1);
			dp[i * 2] = Math.min(dp[i * 2], dp[i] + 1);
			dp[i + 1] = Math.min(dp[i + 1], dp[i] + 1);
		}
		
		System.out.println(dp[X]);
	}
	
	public static void dp2() {
		dp = new int[X+1];
		
		for(int i = 2; i <= X; i++) {
			dp[i] = dp[i - 1] + 1;
			if (i % 2 == 0) dp[i] = Math.min(dp[i], dp[i / 2] + 1);
			if (i % 3 == 0) dp[i] = Math.min(dp[i], dp[i / 3] + 1);
		}
		
		System.out.println(dp[X]);
	}
	
	public static void dp3() {
		ans = Integer.MAX_VALUE;
		dp3_dfs(X, 0);
		System.out.println(ans);
	}
	
	public static void dp3_dfs(int x, int cnt) {
		if (x == 1) {
			ans = Math.min(ans, cnt);
			return;
		}
		
		if (cnt >= ans) return;
		
		if (x % 3 == 0) dp3_dfs(x / 3, cnt + 1);
		if (x % 2 == 0) dp3_dfs(x / 2, cnt + 1);
		dp3_dfs(x - 1, cnt + 1);
	}
	
	public static void dp4() {
		dp = new int[X+1];
		dp4_dfs(X);		
		System.out.println(dp[X]);
	}
	
	public static int dp4_dfs(int x) {
		if (x == 1) return 0;
		if (dp[x] != 0) return dp[x];
		
		if (x % 6 == 0) {
			dp[x] = Math.min(dp4_dfs(x - 1), Math.min(dp4_dfs(x / 3), dp4_dfs(x / 2))) + 1;
		}
		else if (x % 3 == 0) {
			dp[x] = Math.min(dp4_dfs(x / 3), dp4_dfs(x - 1)) + 1;
		}
		else if (x % 2 == 0) {
			dp[x] = Math.min(dp4_dfs(x / 2), dp4_dfs(x - 1)) + 1;
		}
		else {
			dp[x] = dp4_dfs(x - 1) + 1;
		}
		return dp[x];
	}
	
	public static void dp5() {	
		System.out.println(dp5_dfs(X));
	}
	
	public static int dp5_dfs(int x) { 
		if (x == 1) return 0;
		
		int div3 = Integer.MAX_VALUE;
		int div2 = Integer.MAX_VALUE;
		int minus1 = Integer.MAX_VALUE;
		
		if (x % 3 == 0) div3 = dp5_dfs(x / 3) + 1;
		if (x % 2 == 0) div2 = dp5_dfs(x / 2) + 1;
		minus1 = dp5_dfs(x - 1) + 1;
		
		return Math.min(Math.min(div3, div2), minus1);
	}
}
