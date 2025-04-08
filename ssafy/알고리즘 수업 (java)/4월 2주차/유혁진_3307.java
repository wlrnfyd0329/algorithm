import java.util.*;
import java.io.*;

class Solution {
	static int T, N;
	static ArrayList<Integer> lis;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;


		int T = Integer.parseInt(br.readLine());
		for (int tc = 1; tc <= T; tc++) {
			N = Integer.parseInt(br.readLine());
			lis = new ArrayList<>();
			st = new StringTokenizer(br.readLine());
			
			for(int i = 0; i < N; i++) {
				int num = Integer.parseInt(st.nextToken());
				int idx = lower_bound(num);
				if (idx == lis.size()) {
					lis.add(num);
				}
				else {
					lis.set(idx, num);
				}
			}
			
			System.out.println("#" + tc + " " + lis.size());	
		}
	}
	
	public static int lower_bound(int target) {
		int lf = 0, rg = lis.size() - 1;
		while(lf <= rg) {
			int mid = (lf + rg) >> 1;
			if (lis.get(mid) < target) {
				lf = mid + 1;
			}
			else {
				rg = mid - 1;
			}
		}
		
		return lf;
	}
}