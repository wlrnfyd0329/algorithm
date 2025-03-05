import java.io.*;
import java.util.*;

public class Main {
	static int N;
	static int M;
	static int R;
	static int[][] arr;
	static int[][] newArr;
	static int arrSize;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		R = Integer.parseInt(st.nextToken());
		arrSize = Math.max(N, M);
		newArr = new int[arrSize][arrSize];
		arr = new int[N][M];
		
		for(int i = 0; i < N; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j = 0; j < M; j++) {
				arr[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		st = new StringTokenizer(br.readLine());
		for(int i = 0; i < R; i++) {
			int cmd = Integer.parseInt(st.nextToken());
			func(cmd);
		}
		
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < M; j++) {
				if (arr[i][j] == 0) break;
				System.out.print(arr[i][j] + " ");
			}
			System.out.println();
		}
	}
	
	public static void func(int cmd) {
		switch (cmd) {
		case 1:
			firstCal();
			break;
		case 2:
			secondCal();
			break;
		case 3:
			thirdCal();
			break;
		case 4:
			fourthCal();
			break;
		case 5:
			fifthCal();
			break;
		case 6:
			sixthCal();
			break;
		}
	}
	
	public static void firstCal() {
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < M; j++) {
				newArr[N - 1 - i][j] = arr[i][j];
			}
		}
		pasteArr();
	}
	
	public static void secondCal() {
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < M; j++) {
				newArr[i][M - 1 - j] = arr[i][j];
			}
		}
		pasteArr();
	}
	
	public static void thirdCal() {
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < M; j++) {
				newArr[j][N - 1 - i] = arr[i][j];
			}
		}
		int tmp = N;
		N = M;
		M = tmp;
        arr = new int[N][M];
		pasteArr();
	}
	
	public static void fourthCal() {
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < M; j++) {
				newArr[M - 1 - j][i] = arr[i][j];
			}
		}
		int tmp = N;
		N = M;
		M = tmp;
        arr = new int[N][M];
		pasteArr();
	}
	
	public static void fifthCal() {
		for(int i = 0; i < N / 2; i++) {
			for(int j = 0; j < M / 2; j++) {
				newArr[i][j + M / 2] = arr[i][j];
			}
		}
		
		for(int i = 0; i < N / 2; i++) {
			for(int j = M / 2; j < M; j++) {
				newArr[i + N / 2][j] = arr[i][j];
			}
		}
		
		for(int i = N / 2; i < N; i++) {
			for(int j = M / 2; j < M; j++) {
				newArr[i][j - M / 2] = arr[i][j];
			}
		}
		
		for(int i = N / 2; i < N; i++) {
			for(int j = 0; j < M / 2; j++) {
				newArr[i - N / 2][j] = arr[i][j];
			}
		}

		pasteArr();
	}
	
	public static void sixthCal() {
		for(int i = 0; i < N / 2; i++) {
			for(int j = 0; j < M / 2; j++) {
				newArr[i + N / 2][j] = arr[i][j];
			}
		}
		
		for(int i = N / 2; i < N; i++) {
			for(int j = 0; j < M / 2; j++) {
				newArr[i][j + M / 2] = arr[i][j];
			}
		}
		
		for(int i = N / 2; i < N; i++) {
			for(int j = M / 2; j < M; j++) {
				newArr[i - N / 2][j] = arr[i][j];
			}
		}
		
		for(int i = 0; i < N / 2; i++) {
			for(int j = M / 2; j < M; j++) {
				newArr[i][j - M / 2] = arr[i][j];
			}
		}
		
		pasteArr();
	}
	
	public static void pasteArr() {
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < M; j++) {
				arr[i][j] = newArr[i][j];
			}
		}
	}
}
