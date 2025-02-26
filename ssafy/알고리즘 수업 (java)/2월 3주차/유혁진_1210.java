package com.saffy.algorithm;

import java.io.*;
import java.util.StringTokenizer;

public class 유혁진_1210 {

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int[] dx = {-1, 0, 0};
		int[] dy = {0, 1, -1};
		
		for(int tc = 1; tc <= 10; tc++) {
			br.readLine();
			int[][] arr = new int[100][100];
			int x = 0, y = 0;
			int dir = 0;
			
			for(int i = 0; i < 100; i++) {
				StringTokenizer st = new StringTokenizer(br.readLine());
				for(int j = 0; j < 100; j++) {
					arr[i][j] = Integer.parseInt(st.nextToken());
					if (arr[i][j] == 2) {
						x = i;
						y = j;
					}
				}
			}
			
			while(x != 0) {
				if (dir == 0) {
					
					if (y != 99 && arr[x][y + dy[1]] == 1) {
						dir = 1;
					}
					else if (y != 0 && arr[x][y + dy[2]] == 1) {
						dir = 2;
					}
				}
				else {
					if (y == 0 || y == 99 || arr[x][y + dy[dir]] != 1) {
						dir = 0;
					}
				}
				x += dx[dir];
				y += dy[dir];
			}
			
			System.out.println("#" + tc + " " + y);
		}
	}	

}
