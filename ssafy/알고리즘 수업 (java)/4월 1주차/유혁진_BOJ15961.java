import java.io.*;
import java.util.*;

public class Main {
	static int N, d, k, c;
	static int[] belt;
	static int[] eat;
	static int ans;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());

		N = Integer.parseInt(st.nextToken());
		d = Integer.parseInt(st.nextToken());
		k = Integer.parseInt(st.nextToken());
		c = Integer.parseInt(st.nextToken());
		belt = new int[2 *  N];
		eat = new int[d + 1];
		ans = 0;

		for(int i = 0; i < N; i++) {
			belt[i] = Integer.parseInt(br.readLine());
		}
		for(int i = 0; i < k; i++) {
			belt[N + i] = belt[i];
		}
		
		func();
		
		System.out.println(ans);
	}
	
	public static void func() {
		int st = 0, en = 1, distinct = 1;
		eat[belt[st]] = 1;
		while(en != N + k) {
			if (eat[belt[en]] == 0) {
				distinct++;
			}
			eat[belt[en++]]++;
			
			if (en - st > k) {
				if (eat[belt[st]] == 1) {
					distinct--;
				}
				eat[belt[st++]]--;
			}
			
			if (eat[c] == 0) {
				ans = Math.max(ans, distinct + 1);
			}
			else {
				ans = Math.max(ans, distinct);
			}
		}
	}
}
