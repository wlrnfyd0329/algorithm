import java.util.*;
import java.io.*;

class Main {
	static int N, M, K;
	static long[] tree;
	
	public static void update(int node, int start, int end, int index, long value) {
		if (start == end) {
			tree[node] = value;
			return;
		}
		int mid = (start + end) >> 1;
		if (index <= mid) {
			update(node * 2, start, mid, index, value);
		}
		else {
			update(node * 2 + 1, mid + 1, end, index, value);
		}
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}
	
	public static long query(int node, int start, int end, int left, int right) {
		if (right < start || end < left) return 0;
		if (left <= start && end <= right) return tree[node];
		int mid = (start + end) >> 1;
		return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());
		tree = new long[N * 4];
		
		for(int i = 1; i <= N; i++) {
			update(1, 1, N, i, Long.parseLong(br.readLine()));
		}
		
		for(int i = 0; i < M + K; i++) {
			st = new StringTokenizer(br.readLine());
			if (Integer.parseInt(st.nextToken()) == 1) {
				update(1, 1, N, Integer.parseInt(st.nextToken()), Long.parseLong(st.nextToken()));
			}
			else {
				System.out.println(query(1, 1, N, Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken())));
			}
		}
		
	}
	
}