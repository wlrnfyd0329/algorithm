import java.io.*;
import java.util.*;

public class 유혁진_1225 {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		
		for(int tc = 1; tc <= 10; tc++) {
			br.readLine();
			st = new StringTokenizer(br.readLine());
			Deque<Integer> dq = new ArrayDeque<>();
			for(int i = 0; i < 8; i++) {
				dq.add(Integer.parseInt(st.nextToken()));
			}
			
			int cycle = 0;
			while(true) {
				int std = dq.pollFirst();
				std -= cycle + 1;
				if (std <= 0) {
					dq.offerLast(0);
					break;
				}
				else {
					dq.offerLast(std);
				}
				cycle = (cycle + 1) % 5;
			}
			
			System.out.print("#" + tc + " ");
			for(Integer i : dq) {
				System.out.print(i + " ");
			}
			System.out.println();
		}
	}
}