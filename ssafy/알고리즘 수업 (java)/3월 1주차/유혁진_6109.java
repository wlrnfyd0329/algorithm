import java.io.*;
import java.util.*;

public class Solution {
	static int T;
	static int N;
	static String S;
	static int[][] arr;
	static int[] dx = {-1, 1, 0, 0};
	static int[] dy = {0, 0, 1, -1};
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		int T = Integer.parseInt(br.readLine());
		
		for(int tc = 1; tc <= T; tc++) {
			System.out.println("#" + tc);
			st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			S = st.nextToken();
			arr = new int[N][N];
			
			for(int i = 0; i < N; i++) {
				st = new StringTokenizer(br.readLine());
				for(int j = 0; j < N; j++) {
					arr[i][j] = Integer.parseInt(st.nextToken());
				}
			}
			
			move(S);
			
			for(int i = 0; i < N; i++) {
				for(int j = 0; j < N; j++) {
					System.out.print(arr[i][j] + " ");
				}
				System.out.println();
			}
		}
	}
	
	public static void move(String S) {
		boolean[][] merge = new boolean[N][N];
		if (S.equals("up")) {
			for(int j = 0; j < N; j++) {
				for(int i = 0; i < N; i++) {
					if (arr[i][j] == 0) continue;
					int nx = i + dx[0];
					int ny = j + dy[0];
					int num = arr[i][j];
					arr[i][j] = 0;
					while(true) {
						if (nx < 0 || nx >= N || ny < 0 || ny >= N) {
							nx -= dx[0];
							ny -= dy[0];
							arr[nx][ny] = num;
							break;
						}
						if (arr[nx][ny] != 0) {
							if (arr[nx][ny] == num && !merge[nx][ny]) {
								arr[nx][ny] += num;
								merge[nx][ny] = true;
							}
							else {
								nx -= dx[0];
								ny -= dy[0];
								arr[nx][ny] = num;
							}
							
							break;
						}
						nx += dx[0];
						ny += dy[0];
					}
				}
			}
		}
		
		if (S.equals("down")) {
			for(int j = 0; j < N; j++) {
				for(int i = N - 1; i >= 0; i--) {
					if (arr[i][j] == 0) continue;
					int nx = i + dx[1];
					int ny = j + dy[1];
					int num = arr[i][j];
					arr[i][j] = 0;
					while(true) {
						if (nx < 0 || nx >= N || ny < 0 || ny >= N) {
							nx -= dx[1];
							ny -= dy[1];
							arr[nx][ny] = num;
							break;
						}
						if (arr[nx][ny] != 0) {
							if (arr[nx][ny] == num && !merge[nx][ny]) {
								arr[nx][ny] += num;
								merge[nx][ny] = true;
							}
							else {
								nx -= dx[1];
								ny -= dy[1];
								arr[nx][ny] = num;
							}
							
							break;
						}
						nx += dx[1];
						ny += dy[1];
					}
				}
			}
		}
		
		if (S.equals("right")) {
			for(int i = 0; i < N; i++) {
				for(int j = N - 1; j >= 0; j--) {
					if (arr[i][j] == 0) continue;
					int nx = i + dx[2];
					int ny = j + dy[2];
					int num = arr[i][j];
					arr[i][j] = 0;
					while(true) {
						if (nx < 0 || nx >= N || ny < 0 || ny >= N) {
							nx -= dx[2];
							ny -= dy[2];
							arr[nx][ny] = num;
							break;
						}
						if (arr[nx][ny] != 0) {
							if (arr[nx][ny] == num && !merge[nx][ny]) {
								arr[nx][ny] += num;
								merge[nx][ny] = true;
							}
							else {
								nx -= dx[2];
								ny -= dy[2];
								arr[nx][ny] = num;
							}
							
							break;
						}
						nx += dx[2];
						ny += dy[2];
					}
				}
			}
		}
		
		if (S.equals("left")) {
			for(int i = 0; i < N; i++) {
				for(int j = 0; j < N; j++) {
					if (arr[i][j] == 0) continue;
					int nx = i + dx[3];
					int ny = j + dy[3];
					int num = arr[i][j];
					arr[i][j] = 0;
					while(true) {
						if (nx < 0 || nx >= N || ny < 0 || ny >= N) {
							nx -= dx[3];
							ny -= dy[3];
							arr[nx][ny] = num;
							break;
						}
						if (arr[nx][ny] != 0) {
							if (arr[nx][ny] == num && !merge[nx][ny]) {
								arr[nx][ny] += num;
								merge[nx][ny] = true;
							}
							else {
								nx -= dx[3];
								ny -= dy[3];
								arr[nx][ny] = num;
							}
							
							break;
						}
						nx += dx[3];
						ny += dy[3];
					}
				}
			}
		}
	}

}
