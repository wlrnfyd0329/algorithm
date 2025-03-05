// 순열로 가능하지만 외판원 순회를 통하면 N이 커질때도 사용할 수 있다.
// 외판원 순회에서 dp 인덱스가 의미하는 것은
// [현재 있는 위치 0 이라면 시작점, 1이라면 1번 집][00001 : N = 4일때, 시작점을 방문 한 것, 00011 이라면 시작점과 1번 집에 방문한 것]
// dp 값이 의미하는 것은 00111이고 시작점이 3이면 시작점, 1, 2번을 방문하고 현재는 2번 집에 있는데,
// 모든 순회(3, 4번집 방문)까지 남은 최소 거리를 의미한다.
// dp[3][11111]이라면 이제 모든 순회를 다했으니 이제 3과 시작점(현 문제에서는 집)까지의 남은 거리인 것이다.
// dp[4][10111]이라면 이제 3과 시작점 순회까지의 남은 최소 거리를 의미하는 것이다.
// dp[0][00001]이라면 이제 모든 순회까지의 남은 최소 거리를 의미하기 때문에 dfs를 이용한 외판원 순회를 마치면
// dp[0][1]이 정해가 될 것이다.
// 외판원 순회 진짜 어렵다...
import java.io.*;
import java.util.*;

public class Solution {
    static int T;
    static int N;
    static int[][] position;
    static int[][] dp;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        T = Integer.parseInt(br.readLine());

        for(int tc = 1; tc <= T; tc++) {
            N = Integer.parseInt(br.readLine());
            position = new int[N + 2][2];
            dp = new int[N + 1][1 << (N + 1)];

            st = new StringTokenizer(br.readLine());
            position[0][0] = Integer.parseInt(st.nextToken());
            position[0][1] = Integer.parseInt(st.nextToken());

            position[N + 1][0] = Integer.parseInt(st.nextToken());
            position[N + 1][1] = Integer.parseInt(st.nextToken());

            for(int i = 1; i <= N; i++) {
                position[i][0] = Integer.parseInt(st.nextToken());
                position[i][1] = Integer.parseInt(st.nextToken());
            }

            System.out.println("#" + tc + " " + dfs(0, 1));
        }
    }

    public static int cal_dist(int x1, int y1, int x2, int y2) {
        return Math.abs(x1 - x2) + Math.abs(y1 - y2);
    }

    public static int dfs(int city, int check) {
        // dp 메모이제이션으로 0이 아니라면 저장된 값이 있다는 것이기에 사용 순회를 하다보면 반드시 경로가 중복될 것임
        if (dp[city][check] != 0) return dp[city][check];
        if (check == (1 << N + 1) - 1) {
            // dp[city][11111]이기 때문에 이제 끝점과의 거리만 계산하면 되는 것이고 메모이제이션하기 위해서 dp에 값을 넘긴다
            return dp[city][check] = cal_dist(position[city][0], position[city][1], position[N + 1][0], position[N + 1][1]);
        }

        // 여기 까지 들어왔다면 최솟값 갱신이 되지 않을 것이기에 최솟값 갱신을 위한 int 최댓값
        // 물론 이러기 싫다면 main에서 최댓값 갱신을 미리 해주면 된다. 그렇게 되면 위에 메모이제이션을 위한 != 0을 != Integer.MAX_VALUE 로 바꿔주면 된다.
        dp[city][check] = Integer.MAX_VALUE;
        for(int i = 1; i < N + 1; i++) {
            int next = (1 << i);
            if ((check | next) == check) continue;
            // 남은 거리의 최소를 알기 위해서 그 앞의 값을 알아야 하기에 dfs를 진행해주면 i까지 방문했을 때의 최소거리가 나온것이기에
            // 해당 i와 city의 거리를 더해주면 city를 방문한 상태에서 남은 최소 거리를 알게 된다.
            dp[city][check] = Math.min(dp[city][check], dfs(i,check|next) + cal_dist(position[city][0], position[city][1], position[i][0], position[i][1]));
        }

        return dp[city][check];
    }

//    아래의 코드는 메모이제이션을 하지 않은 나쁜 코드다.
//    dp 값을 최댓값으로 초기화 하는 작업을 해주지 않기 때문에
//    for(int i = 0; i < N + 1; i++) {
//        for(int j = 0; j < 1 << (N + 1); j++) {
//            dp[i][j] = Integer.MAX_VALUE;
//        }
//    }
//    이 코드를 실행하기 위해서는 main에서 위와 같이
//    dp 값을 모두 Integer.MAX_VALUE로 채워주는 작업도 병행해야 한다.

//    public static int dfs(int city, int check) {
//        if (check == (1 << N + 1) - 1) {
//            return cal_dist(position[city][0], position[city][1], position[N + 1][0], position[N + 1][1]);
//        }
//
//        for(int i = 1; i < N + 1; i++) {
//            int next = (1 << i);
//            if ((check | next) == check) continue;
//            dp[city][check] = Math.min(dp[city][check], dfs(i,check|next) + cal_dist(position[city][0], position[city][1], position[i][0], position[i][1]));
//        }
//
//        return dp[city][check];
//    }
}