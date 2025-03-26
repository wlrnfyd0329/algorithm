import java.io.*;
import java.util.*;

public class Main {

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		int N = Integer.parseInt(st.nextToken());
		int r = Integer.parseInt(st.nextToken());
		int c = Integer.parseInt(st.nextToken());
		
		System.out.println(func(N, r, c));
	}
	
	public static int func(int n, int r, int c) {
		if (n == 1) {
			if (r >= 1 && c >= 1) {
				return 3;
			}
			else if (r >= 1) {
				return 2;
			}
			else if (c >= 1) {
				return 1;
			}
			else {
				return 0;
			}
		}
		int line = (int) Math.pow(2, n - 1);
		if (r >= line && c >= line) {
			return 3 * (int) Math.pow(2, 2 * (n - 1)) + func(n - 1, r - line, c - line);
		}
		else if (r >= line) {
			return 2 * (int) Math.pow(2, 2 * (n - 1)) + func(n - 1, r - line, c);
		}
		else if (c >= line) {
			return 1 * (int) Math.pow(2, 2 * (n - 1)) + func(n - 1, r, c - line);
		}
		else {
			return 0 * (int) Math.pow(2, 2 * (n - 1)) + func(n - 1, r, c);
		}
	}

}
