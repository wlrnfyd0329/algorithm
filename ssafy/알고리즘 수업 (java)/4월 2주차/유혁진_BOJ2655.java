// 진짜 잘 모르겠다...

import java.io.*;
import java.util.*;

public class Main {
	static int N;
	static Block[] block;
	static int[] height;
	static int[] tower;
	
	public static class Block {
		int num;
		int wide;
		int height;
		int weight;
		
		public Block() {}
		
		public Block(int num, int wide, int height, int weight) {
			this.num = num + 1;
			this.wide = wide;
			this.height = height;
			this.weight = weight;
		}
	}

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;

		N = Integer.parseInt(br.readLine());
		block = new Block[N];	
		for(int i = 0; i < N; i++) {
			st = new StringTokenizer(br.readLine());
			block[i] = new Block(i, Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));
		}
		
		Arrays.sort(block, (o1, o2) -> {
			return Integer.compare(o1.wide, o2.wide);
		});
		
		height = new int[N];
		tower = new int[N];
		Arrays.fill(tower, -1);
		
		int max_height = height[0] = block[0].height;
		int maxIdx = 0;
		for(int i = 1; i < N; i++) {
			for(int j = 0; j <= i - 1; j++) {
				if (block[i].weight > block[j].weight) {
					if (height[i] < height[j]) {
						height[i] = height[j];
						tower[i] = j;
					}
				}
			}
			height[i] += block[i].height;
			if (max_height < height[i]) {
				max_height = height[i];
				maxIdx = i;
			}
		}
		
		int cnt = 0;
        StringBuilder sb = new StringBuilder();
        while (maxIdx >= 0) {
            cnt++;
            sb.insert(0, block[maxIdx].num + "\n");
            maxIdx = tower[maxIdx];
        }
        System.out.println(cnt);
        System.out.print(sb);
	}
}
