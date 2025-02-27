import java.io.*;
import java.util.*;

public class Solution {
	static int T;
	
	static int[] charge;
	static int[] useCost;
	static int[] total;
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		int T = Integer.parseInt(br.readLine());
		
		for(int tc = 1; tc <= T; tc++) {
			charge = new int[4];
			useCost = new int[13];
			total = new int[13];
			
			st = new StringTokenizer(br.readLine());
			for(int i = 0; i < 4; i++) {
				charge[i] = Integer.parseInt(st.nextToken());
			}
			
			st = new StringTokenizer(br.readLine());
			for(int i = 1; i <= 12; i++) {
				useCost[i] = Math.min(charge[0] * Integer.parseInt(st.nextToken()), charge[1]);
			}
			
			for(int i = 1; i <= 12; i++) {
				if (i == 1 || i == 2) total[i] = total[i-1] + useCost[i];
				else {
					total[i] = Math.min(total[i - 1] + useCost[i], total[i - 3] + charge[2]);
				}
			}
 
			
			System.out.println("#" + tc + " " + Math.min(total[12], charge[3]));
		}
	}
}