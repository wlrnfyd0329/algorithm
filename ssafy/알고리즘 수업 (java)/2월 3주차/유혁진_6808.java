package com.saffy.algorithm;

import java.io.*;
import java.util.StringTokenizer;

public class 유혁진_6808 {
	static boolean[] card = new boolean[19];
	static int[] my_card = new int[9];
	static int[] me = new int[9];
	static int[] other = new int[9];
	static int win = 0;
	static int lose = 0;
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());
		
		for (int tc = 1; tc <= T; tc++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			win = 0;
			lose = 0;
			for(int i = 1; i < 19; i++) {
				card[i] = false;
			}
			
			for(int i = 0; i < 9; i++) {
				other[i] = Integer.parseInt(st.nextToken());
				card[other[i]] = true;
			}
			
			int idx = 0;
			for(int i = 1; i < 19; i++) {
				if(!card[i]) my_card[idx++] = i;
			}
			
			permutation(0);
			
			System.out.println("#" + tc + " " + lose + " " + win);
		}
	}
	
	public static void permutation(int depth) {
		if (depth == 9) {
			if (game() == 1) win++;
			else if (game() == -1) lose++;
			return;
		}
		
		for(int i = 0; i < 9; i++) {
			if (card[my_card[i]]) continue;
			card[my_card[i]] = true;
			me[depth] = my_card[i];
			permutation(depth + 1);
			card[my_card[i]] = false;
		}
	}
	
	public static int game() {
		int my_score = 0;
		int other_score = 0;
		for(int i = 0; i < 9; i++) {
			if (me[i] > other[i]) {
				my_score += me[i] + other[i];
			}
			else {
				other_score += me[i] + other[i];
			}
		}
		
		if (my_score > other_score) return 1;
		else if (my_score < other_score) return -1;
		else return 0;
	}
}
