import java.io.*;
import java.util.*;

public class 유혁진_BJ2023 {
	static int N;
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.parseInt(br.readLine());
		
		amazingPrime(0, 0);
	}
	
	public static void amazingPrime(int cnt, int number) {
		if (cnt == N) {
			System.out.println(number);
			return;
		}
		
		int num = number * 10;
		for(int i = 0; i < 10; i++) {
			int n = num + i;
			if(isPrime(n)) {
				amazingPrime(cnt + 1, n);
			}
		}
	}
	
	public static boolean isPrime(int n) {
		if (n < 2) return false;
		int sqrtN = (int) Math.sqrt(n);
		for (int i = 2; i <= sqrtN ; i++)
			if (n % i == 0) return false;
		return true;
	}
}