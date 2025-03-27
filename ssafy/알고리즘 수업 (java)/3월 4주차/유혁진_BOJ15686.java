import java.util.*;
import java.io.*;

public class Main {
	static int N;
	static int M;
	static int choose;
	static int ans;
	static ArrayList<int[]> home;
	static ArrayList<int[]> chicken;
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		choose = 0;
		ans = Integer.MAX_VALUE;
		home = new ArrayList<>();
		chicken = new ArrayList<>();
		for(int i = 0; i < N; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j = 0; j < N; j++) {
				int num = Integer.parseInt(st.nextToken());
				if (num == 1) home.add(new int[] {i, j});
				if (num == 2) chicken.add(new int[] {i, j});
			}
		}
		
		combination(0, 0);
		
		System.out.println(ans);
	}
	
	public static void combination(int now, int cnt) {
		if (cnt == M) {
			int total = 0;
			for(int i = 0; i < home.size(); i++) {
				int dist = Integer.MAX_VALUE;
				for(int j = 0; j < chicken.size(); j++) {
					if ((choose & (1<<j)) > 0) dist = Math.min(dist, Math.abs(home.get(i)[0] - chicken.get(j)[0]) + Math.abs(home.get(i)[1] - chicken.get(j)[1]));
				}
				total += dist;
			}
			ans = Math.min(ans, total);
		}
		
		for(int i = now; i < chicken.size(); i++) {
			choose |= (1 << i);
			combination(i + 1, cnt + 1);
			choose ^= (1 << i);
		}
	}
}
