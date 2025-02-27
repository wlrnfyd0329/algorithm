import java.io.*;
import java.util.*;

public class Solution {
	static int T;
	static int N;
	
	static int[][] room;
	static int[] dx = {0, -1, 0, 1};
	static int[] dy = {1, 0, -1, 0};
	static ArrayList<Integer>[] roomInfo;
	
	static int roomNumber;
	static int roomCnt;
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		int T = Integer.parseInt(br.readLine());
		
		for(int tc = 1; tc <= T; tc++) {
			N = Integer.parseInt(br.readLine());
			room = new int[N][N];
			roomInfo = new ArrayList[N * N + 1];
			roomNumber = 2000;
			roomCnt = 0;

			for(int i = 0; i < N; i++) {
				st = new StringTokenizer(br.readLine());
				for(int j = 0; j < N; j++) {
					room[i][j] = Integer.parseInt(st.nextToken());
					roomInfo[room[i][j]] = new ArrayList<Integer>();
				}
			}
			
			for(int i = 0; i < N; i++) {
				for(int j = 0; j < N; j++) {
					for(int dir = 0; dir < 4; dir++) {
						int nx = i + dx[dir];
						int ny = j + dy[dir];
						if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
						if (room[nx][ny] == room[i][j] + 1) {
							roomInfo[room[i][j]].add(room[nx][ny]);
						}
					}
				}
			}
			
			for(int i = 0; i < N; i++) {
				for(int j = 0; j < N; j++) {
					search(room[i][j], room[i][j], 1);
				}
			}
			
			System.out.println("#" + tc + " " + roomNumber + " " + roomCnt);
		}
	}
	
	public static void search(int start, int now, int cnt) {
		if (roomInfo[now].isEmpty()) {
			if (roomCnt < cnt) {
				roomNumber = start;
				roomCnt = cnt;
			}
			else if (roomCnt == cnt) {
				roomNumber = Math.min(roomNumber, start);
			}
			return;
		}
		
		for(int num : roomInfo[now]) {
			search(start, num, cnt+1);
		}
	}

}