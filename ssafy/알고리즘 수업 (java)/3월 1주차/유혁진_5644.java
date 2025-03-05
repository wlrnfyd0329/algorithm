import java.io.*;
import java.util.*;

public class Solution {
	static int T;
	static int M;
	static int A;
	static int[] userA;
	static int[] userB;
	static int[] positionA;
	static int[] positionB;
	static int[][] map;	
	static int[] power;
	static int userPower;
	static int[] dx = {0, 0, 1, 0, -1};
	static int[] dy = {0, -1, 0, 1, 0};
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		T = Integer.parseInt(br.readLine());
		
		for(int tc = 1; tc <= T; tc++) {
			st = new StringTokenizer(br.readLine());
			map = new int[11][11];
			M = Integer.parseInt(st.nextToken());
			A = Integer.parseInt(st.nextToken());
			userA = new int[M];
			userB = new int[M];
			positionA = new int[] {1, 1};
			positionB = new int[] {10, 10};
			power = new int[A];
			userPower = 0;
			
			st = new StringTokenizer(br.readLine());
			for(int i = 0; i < M; i++) {
				userA[i] = Integer.parseInt(st.nextToken());
			}
			
			st = new StringTokenizer(br.readLine());
			for(int i = 0; i < M; i++) {
				userB[i] = Integer.parseInt(st.nextToken());
			}
			
			for(int i = 0; i < A; i++) {
				st = new StringTokenizer(br.readLine());
				int x = Integer.parseInt(st.nextToken());
				int y = Integer.parseInt(st.nextToken());
				int c = Integer.parseInt(st.nextToken());
				power[i] = Integer.parseInt(st.nextToken());
				int[][] vis = new int[11][11];
				Queue<int[]> q = new LinkedList<>();
				vis[x][y] = 1;
				map[x][y] |= 1 << i;
				q.offer(new int[] {x, y});
				while(!q.isEmpty()) {
					int[] cur = q.poll();
					if (vis[cur[0]][cur[1]] == c + 1) continue;
					for(int dir = 1; dir <= 4; dir++) {
						int nx = cur[0] + dx[dir];
						int ny = cur[1] + dy[dir];
						if (nx <= 0 || nx > 10 || ny <= 0 || ny > 10) continue;
						if (vis[nx][ny] > 0) continue;
						vis[nx][ny] = vis[cur[0]][cur[1]] + 1;
						map[nx][ny] |= 1 << i;
						q.offer(new int[] {nx, ny});
					}
				}
			}
			
			move(positionA[0], positionA[1], positionB[0], positionB[1]);
			for(int i = 0; i < M; i++) {
				positionA[0] += dx[userA[i]];
				positionA[1] += dy[userA[i]];
				positionB[0] += dx[userB[i]];
				positionB[1] += dy[userB[i]];
				move(positionA[0], positionA[1], positionB[0], positionB[1]);
			}
		
			System.out.println("#" + tc + " " + userPower);
		}
	}
	
	public static void move(int xA, int yA, int xB, int yB) {
		int idx = -1;
		int maxPower = 0;
		for(int i = 0; i < A; i++) {
			if (((map[xA][yA] | map[xB][yB]) & (1 << i)) > 0) {
				if (maxPower < power[i]) {
					maxPower = power[i];
					idx = i;
				}
			}
		}
		
		if (idx == -1) {
			return;
		}
		
		userPower += power[idx];
		maxPower = 0;
		if (((map[xA][yA] & map[xB][yB]) & (1 << idx)) > 0) {
			for(int i = 0; i < A; i++) {
				if ((((map[xA][yA] | map[xB][yB]) ^ (1 << idx)) & (1 << i)) > 0) {
					if (maxPower < power[i]) {
						maxPower = power[i];
					}
				}
			}
		}
		else {
			if ((map[xA][yA] & (1 << idx)) > 0) {
				for(int i = 0; i < A; i++) {
					if (((map[xB][yB]) & (1 << i)) > 0) {
						if (maxPower < power[i]) {
							maxPower = power[i];
						}
					}
				}
			}
			else {
				for(int i = 0; i < A; i++) {
					if (((map[xA][yA]) & (1 << i)) > 0) {
						if (maxPower < power[i]) {
							maxPower = power[i];
						}
					}
				}
			}
		}
		userPower += maxPower;
	}
}
