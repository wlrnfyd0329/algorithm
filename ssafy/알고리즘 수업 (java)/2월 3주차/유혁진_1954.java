package com.saffy.algorithm;

import java.util.Scanner;

public class 유혁진_1954 {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int[] dx = {0, 1, 0, -1};
		int[] dy = {1, 0, -1, 0};
		
		int T = sc.nextInt();
		
		for(int tc = 1; tc <= T; tc++) {
			int N = sc.nextInt();
			int[][] arr = new int[N][N];
			int x = 0, y = 0, dir = 0;
			for (int i = 1; i <= N * N; i++) {
				arr[x][y] = i;
				int nx = x + dx[dir];
				int ny = y + dy[dir];
				if (nx < 0 || nx >= N || ny < 0 || ny >= N || arr[nx][ny] != 0) {
					dir = (dir + 1) % 4;
				}
				x += dx[dir];
				y += dy[dir];
			}
			
			
			System.out.println("#" + tc);
			for(int i = 0; i < N; i++) {
				for(int j = 0; j < N; j++) {
					System.out.print(arr[i][j] + " ");
				}
				System.out.println();
			}
		}
		
		sc.close();

	}

}
