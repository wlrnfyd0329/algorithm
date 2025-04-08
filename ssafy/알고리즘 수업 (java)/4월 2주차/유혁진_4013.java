import java.util.*;
import java.io.*;

class Solution {
	static int T, K, ans;
	static ArrayList<ArrayDeque<Integer>> magnetic;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;

		int T = Integer.parseInt(br.readLine());
		for (int tc = 1; tc <= T; tc++) {
			K = Integer.parseInt(br.readLine());
			ans = 0;
			magnetic = new ArrayList<>();
			
			for(int i = 0; i < 4; i++) {
				magnetic.add(new ArrayDeque<>());
				st = new StringTokenizer(br.readLine());
				for(int j = 0; j < 8; j++) {
					magnetic.get(i).offerLast(Integer.parseInt(st.nextToken()));
				}
			}
			
			for(int i = 0; i < K; i++) {
				st = new StringTokenizer(br.readLine());
				int id = Integer.parseInt(st.nextToken()) - 1;
				int dir = Integer.parseInt(st.nextToken());
				int tdir = dir;
				ArrayList<int[]> rot = new ArrayList<>();
				rot.add(new int[] {id, dir});
				for(int j = id; j >= 1; j--) {
					tdir = -tdir;
					Object[] a1 = magnetic.get(j).toArray();
					Object[] a2 = magnetic.get(j - 1).toArray();
					if (a1[6] != a2[2]) {
						rot.add(new int[] {j - 1, tdir});
					}
					else break;
				}
				tdir = dir;
				for(int j = id; j < 3; j++) {
					tdir = -tdir;
					Object[] a1 = magnetic.get(j).toArray();
					Object[] a2 = magnetic.get(j + 1).toArray();
					if (a1[2] != a2[6]) {
						rot.add(new int[] {j + 1, tdir});
					}
					else break;
				}
				
				for(int j = 0; j < rot.size(); j++) {
					if (rot.get(j)[1] == 1) {
						rotate(rot.get(j)[0]);
					}
					else {
						reverseRotate(rot.get(j)[0]);
					}
				}
			}
			
			getScore();
			
			System.out.println("#" + tc + " " + ans);	
		}
	}
	
	public static void rotate(int id) {
		magnetic.get(id).offerFirst(magnetic.get(id).pollLast());
	}
	
	public static void reverseRotate(int id) {
		magnetic.get(id).offerLast(magnetic.get(id).pollFirst());
	}
	
	public static void getScore() {
		for(int i = 0; i < 4; i++) {
			ans += magnetic.get(i).getFirst() * (1 << i);
		}
	}
}